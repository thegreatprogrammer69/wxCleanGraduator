#include "PropertySourceBase.h"

application::property::PropertySourceBase::PropertySourceBase(application::settings::SettingsService &settings): settings_(settings) {
}

std::vector<domain::property::PropertyValue> application::property::PropertySourceBase::propertyValues() const {
    std::vector<domain::property::PropertyValue> result;
    const auto schema = propertySchema();
    result.reserve(schema.size());

    for (const auto& field : schema)
    {
        const auto& meta = domain::property::propertyMeta(field);

        result.push_back({
            meta.id,
            readValue(field)
        });
    }

    return result;
}

void application::property::PropertySourceBase::setProperty(const domain::property::PropertyValue &value) {
    const auto schema = propertySchema();

    for (const auto& field : schema)
    {
        const auto& meta = domain::property::propertyMeta(field);
        if (meta.id == value.id)
        {
            if (!isCompatible(field, value.value))
            {
                throw std::runtime_error(
                    "PropertySourceBase: incompatible variant type for id: " + value.id
                );
            }

            settings_.set(value.id, value.value);
            settings_.save(); // автосохранение
            return;
        }
    }

    throw std::runtime_error(
        "PropertySourceBase: property id not found in source: " + value.id
    );
}

application::settings::SettingsService & application::property::PropertySourceBase::settings() {
    return settings_;
}

const application::settings::SettingsService & application::property::PropertySourceBase::settings() const {
    return settings_;
}

domain::property::PropertyVariant application::property::PropertySourceBase::readValue(
    const domain::property::PropertyField &field) const {
    return std::visit(
        [this](const auto& f) -> domain::property::PropertyVariant
        {
            using T = std::decay_t<decltype(f)>;

            const auto* stored = settings_.tryGet(f.meta.id);
            if (stored)
            {
                if constexpr (std::is_same_v<T, domain::property::BoolPropertyField>)
                {
                    if (std::holds_alternative<bool>(*stored)) return *stored;
                }
                else if constexpr (
                    std::is_same_v<T, domain::property::IntPropertyField> ||
                    std::is_same_v<T, domain::property::EnumPropertyField>)
                {
                    if (std::holds_alternative<int>(*stored)) return *stored;
                }
                else if constexpr (std::is_same_v<T, domain::property::FloatPropertyField>)
                {
                    if (std::holds_alternative<float>(*stored)) return *stored;
                }
                else if constexpr (std::is_same_v<T, domain::property::StringPropertyField>)
                {
                    if (std::holds_alternative<std::string>(*stored)) return *stored;
                }
            }

            if constexpr (std::is_same_v<T, domain::property::BoolPropertyField>)
            {
                return f.defaultValue;
            }
            else if constexpr (
                std::is_same_v<T, domain::property::IntPropertyField> ||
                std::is_same_v<T, domain::property::EnumPropertyField>)
            {
                return f.defaultValue;
            }
            else if constexpr (std::is_same_v<T, domain::property::FloatPropertyField>)
            {
                return f.defaultValue;
            }
            else if constexpr (std::is_same_v<T, domain::property::StringPropertyField>)
            {
                return f.defaultValue;
            }
        },
        field
    );
}

bool application::property::PropertySourceBase::isCompatible(const domain::property::PropertyField &field,
    const domain::property::PropertyVariant &value) {
    return std::visit(
        [&value](const auto& f) -> bool
        {
            using T = std::decay_t<decltype(f)>;

            if constexpr (std::is_same_v<T, domain::property::BoolPropertyField>)
            {
                return std::holds_alternative<bool>(value);
            }
            else if constexpr (
                std::is_same_v<T, domain::property::IntPropertyField> ||
                std::is_same_v<T, domain::property::EnumPropertyField>)
            {
                return std::holds_alternative<int>(value);
            }
            else if constexpr (std::is_same_v<T, domain::property::FloatPropertyField>)
            {
                return std::holds_alternative<float>(value);
            }
            else if constexpr (std::is_same_v<T, domain::property::StringPropertyField>)
            {
                return std::holds_alternative<std::string>(value);
            }
            else
            {
                return false;
            }
        },
        field
    );
}

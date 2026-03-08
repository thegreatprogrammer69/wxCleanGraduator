#include "PropertyRegistry.h"

#include "PropertyObserverRegistry.h"

void application::property::PropertyRegistry::setObserverRegistry(PropertyObserverRegistry &observers)
{
    observers_ = &observers;
}

void application::property::PropertyRegistry::registerSource(domain::ports::IPropertySource &source) {
    sources_.push_back(&source);

    const auto schema = source.propertySchema();
    for (const auto& field : schema)
    {
        const auto& id = domain::property::propertyMeta(field).id;

        const auto [it, inserted] = propertyOwners_.emplace(id, &source);
        if (!inserted)
        {
            throw std::runtime_error(
                "Duplicate property id: " + id
            );
        }
    }
}

std::vector<domain::property::PropertyField> application::property::PropertyRegistry::schema() const {
    std::vector<domain::property::PropertyField> result;

    for (const auto* source : sources_)
    {
        auto part = source->propertySchema();
        result.insert(result.end(), part.begin(), part.end());
    }

    return result;
}

std::vector<domain::property::PropertyValue> application::property::PropertyRegistry::values() const {
    std::vector<domain::property::PropertyValue> result;

    for (const auto* source : sources_)
    {
        auto part = source->propertyValues();
        result.insert(result.end(), part.begin(), part.end());
    }

    return result;
}

bool application::property::PropertyRegistry::setProperty(const domain::property::PropertyValue &value) {
    const auto it = propertyOwners_.find(value.id);
    if (it == propertyOwners_.end())
        return false;

    it->second->setProperty(value);

    observers_->notify(value);

    return true;
}

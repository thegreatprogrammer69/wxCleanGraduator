#include "WxPropertyGridBuilder.h"

void ui::wx::panels::WxPropertyGridBuilder::build(wxPropertyGridManager &grid,
    application::property::PropertyRegistry &registry) {
    grid.Clear();

    std::unordered_set<std::string> categories;
    const auto schema = registry.schema();
    const auto values = registry.values();

    auto findValue = [&](const std::string& id) -> const domain::property::PropertyValue*
    {
        for (const auto& v : values)
        {
            if (v.id == id)
                return &v;
        }
        return nullptr;
    };

    for (const auto& field : schema)
    {
        const auto& meta = domain::property::propertyMeta(field);

        if (meta.tags.count("prop-grid-invisible") > 0)
            continue;

        if (!meta.category.empty() && categories.count(meta.category) < 1)
        {
            grid.Append(new wxPropertyCategory(meta.category));
            categories.insert(meta.category);
        }

        const auto* value = findValue(meta.id);

        std::visit(
            [&](const auto& f)
            {
                using T = std::decay_t<decltype(f)>;

                if constexpr (std::is_same_v<T, domain::property::BoolPropertyField>)
                {
                    bool current = value
                                       ? std::get<bool>(value->value)
                                       : f.defaultValue;

                    grid.Append(new wxBoolProperty(f.meta.name, f.meta.id, current));
                }
                else if constexpr (std::is_same_v<T, domain::property::IntPropertyField>)
                {
                    int current = value
                                      ? std::get<int>(value->value)
                                      : f.defaultValue;

                    auto* prop = new wxIntProperty(f.meta.name, f.meta.id, current);
                    grid.Append(prop);
                }
                else if constexpr (std::is_same_v<T, domain::property::FloatPropertyField>)
                {
                    float current = value
                                        ? std::get<float>(value->value)
                                        : f.defaultValue;

                    grid.Append(new wxFloatProperty(f.meta.name, f.meta.id, current));
                }
                else if constexpr (std::is_same_v<T, domain::property::StringPropertyField>)
                {
                    std::string current = value
                                              ? std::get<std::string>(value->value)
                                              : f.defaultValue;

                    grid.Append(new wxStringProperty(f.meta.name, f.meta.id, current));
                }
                else if constexpr (std::is_same_v<T, domain::property::EnumPropertyField>)
                {
                    wxArrayString names;
                    wxArrayInt values_arr;

                    for (const auto& option : f.options)
                    {
                        names.Add(option.name);
                        values_arr.Add(option.value);
                    }

                    int current = value
                                      ? std::get<int>(value->value)
                                      : f.defaultValue;

                    grid.Append(new wxEnumProperty(
                        f.meta.name,
                        f.meta.id,
                        names,
                        values_arr,
                        current
                    ));
                }
            },
            field
        );
    }
}

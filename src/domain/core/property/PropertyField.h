#ifndef WXCLEANGRADUATOR_PROPERTYFIELD_H
#define WXCLEANGRADUATOR_PROPERTYFIELD_H

#include <string>
#include <variant>
#include <vector>
#include <cstdint>
#include <set>

namespace domain::property
{

    using PropertyId = std::string;

    struct PropertyMeta
    {
        PropertyId id;
        std::string name;
        std::string category;

        std::set<std::string> tags;
    };


    // ---------- BOOL ----------

    struct BoolPropertyField
    {
        PropertyMeta meta;

        bool defaultValue = false;
    };


    // ---------- INT ----------

    enum class IntFormat
    {
        Decimal,
        Hex
    };

    struct IntPropertyField
    {
        PropertyMeta meta;

        int defaultValue = 0;

        int min = 0;
        int max = 100;

        IntFormat format = IntFormat::Decimal;
    };


    // ---------- FLOAT ----------

    struct FloatPropertyField
    {
        PropertyMeta meta;

        float defaultValue = 0.0f;

        float min = 0.0f;
        float max = 1.0f;
    };


    // ---------- STRING ----------

    struct StringPropertyField
    {
        PropertyMeta meta;

        std::string defaultValue;
    };


    // ---------- ENUM ----------

    struct EnumOption
    {
        int value;
        std::string name;
    };

    struct EnumPropertyField
    {
        PropertyMeta meta;

        int defaultValue = 0;

        std::vector<EnumOption> options;
    };


    // ---------- COLOR ----------

    struct ColorPropertyField
    {
        PropertyMeta meta;
        uint32_t defaultColor;
    };


    // ---------- VARIANT ----------

    using PropertyField = std::variant<
        BoolPropertyField,
        IntPropertyField,
        FloatPropertyField,
        StringPropertyField,
        EnumPropertyField
    >;

    inline const PropertyMeta& propertyMeta(const PropertyField& field)
    {
        return std::visit(
            [](const auto& f) -> const PropertyMeta&
            {
                return f.meta;
            },
            field
        );
    }

}

#endif //WXCLEANGRADUATOR_PROPERTYFIELD_H
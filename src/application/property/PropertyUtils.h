#ifndef WXCLEANGRADUATOR_PROPERTYUTILS_H
#define WXCLEANGRADUATOR_PROPERTYUTILS_H

#include <string>
#include <type_traits>

#include "domain/core/property/PropertyValue.h"

namespace application::property {
    template<typename T>
    [[nodiscard]] inline const T* propertyGetIf(
        const domain::property::PropertyVariant& value
    )
    {
        return std::get_if<T>(&value);
    }

    template<typename T>
    [[nodiscard]] inline T propertyGetOr(
        const domain::property::PropertyVariant& value,
        const T& fallback
    )
    {
        if (const auto* v = std::get_if<T>(&value))
        {
            return *v;
        }
        return fallback;
    }

    inline std::string propertyToString(
        const domain::property::PropertyVariant& value
    )
    {
        return std::visit(
            [](const auto& v) -> std::string
            {
                using T = std::decay_t<decltype(v)>;

                if constexpr (std::is_same_v<T, std::string>)
                {
                    return v;
                }
                else if constexpr (std::is_same_v<T, bool>)
                {
                    return v ? "true" : "false";
                }
                else
                {
                    return std::to_string(v);
                }
            },
            value
        );
    }
}

#endif //WXCLEANGRADUATOR_PROPERTYUTILS_H

#ifndef WXCLEANGRADUATOR_PROPERTYVALUE_H
#define WXCLEANGRADUATOR_PROPERTYVALUE_H
#include <string>
#include <variant>
#include "PropertyId.h"

namespace domain::property
{

    using PropertyVariant = std::variant<
        int,
        float,
        bool,
        std::string
    >;

    struct PropertyValue
    {
        PropertyId id;
        PropertyVariant value;
    };

}

#endif //WXCLEANGRADUATOR_PROPERTYVALUE_H
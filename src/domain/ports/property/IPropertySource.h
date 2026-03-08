#ifndef WXCLEANGRADUATOR_IPROPERTYSOURCE_H
#define WXCLEANGRADUATOR_IPROPERTYSOURCE_H

#include <vector>

#include "domain/core/property/PropertyField.h"
#include "domain/core/property/PropertyValue.h"

namespace domain::ports
{

    struct IPropertySource
    {
        virtual ~IPropertySource() = default;

        // статическая схема
        virtual std::vector<property::PropertyField> propertySchema() const = 0;

        // текущие значения
        virtual std::vector<property::PropertyValue> propertyValues() const = 0;

        // изменение значения
        virtual void setProperty(const property::PropertyValue& value) = 0;
    };

}

#endif //WXCLEANGRADUATOR_IPROPERTYSOURCE_H
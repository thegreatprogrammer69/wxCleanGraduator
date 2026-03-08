#ifndef WXCLEANGRADUATOR_IPROPERTYOBSERVER_H
#define WXCLEANGRADUATOR_IPROPERTYOBSERVER_H
#include "domain/core/property/PropertyValue.h"

namespace domain::ports
{
    struct IPropertyObserver
    {
        virtual ~IPropertyObserver() = default;
        virtual void onPropertyChanged(const property::PropertyValue& value) = 0;
    };
}

#endif //WXCLEANGRADUATOR_IPROPERTYOBSERVER_H
#ifndef WXCLEANGRADUATOR_ISETTINGSSTORAGE_H
#define WXCLEANGRADUATOR_ISETTINGSSTORAGE_H

#include <string>
#include <unordered_map>

#include "domain/core/property/PropertyValue.h"


namespace domain::ports
{

    struct ISettingsStorage
    {
        virtual ~ISettingsStorage() = default;

        virtual std::unordered_map<
            property::PropertyId,
            property::PropertyVariant
        > load() = 0;

        virtual void save(
            const std::unordered_map<
                property::PropertyId,
                property::PropertyVariant
            >& values
        ) = 0;
    };

}

#endif //WXCLEANGRADUATOR_ISETTINGSSTORAGE_H
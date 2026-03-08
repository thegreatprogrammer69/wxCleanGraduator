#ifndef WXCLEANGRADUATOR_PROPERTYREGISTRY_H
#define WXCLEANGRADUATOR_PROPERTYREGISTRY_H

#include <vector>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "domain/ports/property/IPropertySource.h"

namespace application::property
{
    class PropertyObserverRegistry;

    class PropertyRegistry
    {
    public:
        void setObserverRegistry(PropertyObserverRegistry& observers);

        void registerSource(domain::ports::IPropertySource& source);

        std::vector<domain::property::PropertyField> schema() const;

        std::vector<domain::property::PropertyValue> values() const;

        bool setProperty(const domain::property::PropertyValue& value);

    private:
        std::vector<domain::ports::IPropertySource*> sources_{};
        std::unordered_map<std::string, domain::ports::IPropertySource*> propertyOwners_{};
        PropertyObserverRegistry* observers_ = nullptr;
    };

}

#endif //WXCLEANGRADUATOR_PROPERTYREGISTRY_H
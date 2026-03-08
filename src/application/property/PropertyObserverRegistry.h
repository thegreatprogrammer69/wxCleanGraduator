#ifndef WXCLEANGRADUATOR_PROPERTYOBSERVERREGISTRY_H
#define WXCLEANGRADUATOR_PROPERTYOBSERVERREGISTRY_H


#include <string>
#include <unordered_map>
#include <vector>

#include "domain/ports/property/IPropertyObserver.h"

namespace application::property
{

    class PropertyObserverRegistry
    {
    public:
        void subscribe(
            const std::string& propertyId,
            domain::ports::IPropertyObserver* observer
        );

        void notify(const domain::property::PropertyValue& value);

    private:
        std::unordered_map<
            std::string,
            std::vector<domain::ports::IPropertyObserver*>
        > observers_;
    };

}


#endif //WXCLEANGRADUATOR_PROPERTYOBSERVERREGISTRY_H
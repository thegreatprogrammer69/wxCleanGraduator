#include "PropertyObserverRegistry.h"

void application::property::PropertyObserverRegistry::subscribe(const std::string &propertyId,
    domain::ports::IPropertyObserver *observer) {
    observers_[propertyId].push_back(observer);
}

void application::property::PropertyObserverRegistry::notify(const domain::property::PropertyValue &value) {
    const auto it = observers_.find(value.id);
    if (it == observers_.end())
        return;

    for (auto* observer : it->second)
    {
        observer->onPropertyChanged(value);
    }
}

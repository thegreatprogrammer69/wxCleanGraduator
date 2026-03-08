#ifndef WXCLEANGRADUATOR_PROPERTYENGINE_H
#define WXCLEANGRADUATOR_PROPERTYENGINE_H
#include "PropertyObserverRegistry.h"
#include "PropertyRegistry.h"
#include "application/settings/SettingsService.h"

namespace application::property
{

    class PropertyEngine
    {
    public:
        explicit PropertyEngine(application::settings::SettingsService& settings)
            : settings_(settings)
        {
            registry_.setObserverRegistry(observers_);
        }

        void load()
        {
            settings_.load();
        }

        void registerSource(domain::ports::IPropertySource& source)
        {
            registry_.registerSource(source);
        }

        [[nodiscard]] PropertyRegistry& registry()
        {
            return registry_;
        }

        [[nodiscard]] PropertyObserverRegistry& observers()
        {
            return observers_;
        }

        [[nodiscard]] application::settings::SettingsService& settings()
        {
            return settings_;
        }

    private:
        application::settings::SettingsService& settings_;
        PropertyObserverRegistry observers_;
        PropertyRegistry registry_;
    };

}

#endif //WXCLEANGRADUATOR_PROPERTYENGINE_H
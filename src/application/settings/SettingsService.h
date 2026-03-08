#ifndef WXCLEANGRADUATOR_SETTINGSSERVICE_H
#define WXCLEANGRADUATOR_SETTINGSSERVICE_H

#include <string>
#include <unordered_map>
#include <utility>

#include "domain/core/property/PropertyValue.h"
#include "domain/ports/settings/ISettingsStorage.h"

namespace application::settings
{

    class SettingsService
    {
    public:
        using StorageMap = std::unordered_map<
            std::string,
            domain::property::PropertyVariant
        >;

        explicit SettingsService(domain::ports::ISettingsStorage& storage);

        void load();

        void save();

        void set(
            const std::string& id,
            const domain::property::PropertyVariant& value
        );

        [[nodiscard]] bool contains(const std::string& id) const;

        [[nodiscard]] const domain::property::PropertyVariant* tryGet(
            const std::string& id
        ) const;

        template<typename T>
        [[nodiscard]] T getOr(const std::string& id, const T& fallback) const {
            const auto* value = tryGet(id);
            if (!value) {
                return fallback;
            }

            if (const auto* typed = std::get_if<T>(value)) {
                return *typed;
            }

            return fallback;
        }

        [[nodiscard]] const StorageMap& all() const;

    private:
        StorageMap values_;
        domain::ports::ISettingsStorage& storage_;
    };

}

#endif //WXCLEANGRADUATOR_SETTINGSSERVICE_H
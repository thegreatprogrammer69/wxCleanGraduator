#include "SettingsService.h"

application::settings::SettingsService::SettingsService(domain::ports::ISettingsStorage &storage): storage_(storage) {
}

void application::settings::SettingsService::load() {
    values_ = storage_.load();
}

void application::settings::SettingsService::save() {
    storage_.save(values_);
}

void application::settings::SettingsService::
set(const std::string &id, const domain::property::PropertyVariant &value) {
    values_[id] = value;
}

bool application::settings::SettingsService::contains(const std::string &id) const {
    return values_.find(id) != values_.end();
}

const domain::property::PropertyVariant * application::settings::SettingsService::tryGet(const std::string &id) const {
    const auto it = values_.find(id);
    if (it == values_.end()) {
        return nullptr;
    }
    return &it->second;
}


const application::settings::SettingsService::StorageMap & application::settings::SettingsService::all() const {
    return values_;
}

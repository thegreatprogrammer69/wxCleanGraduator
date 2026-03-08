#ifndef WXCLEANGRADUATOR_INMEMORYSETTINGSSTORAGE_H
#define WXCLEANGRADUATOR_INMEMORYSETTINGSSTORAGE_H
#include <unordered_map>
#include "domain/ports/settings/ISettingsStorage.h"

namespace infrastructure::settings
{

    class InMemorySettingsStorage : public domain::ports::ISettingsStorage
    {
    public:
        std::unordered_map<std::string, domain::property::PropertyVariant> load() override
        {
            return values_;
        }

        void save(
            const std::unordered_map<std::string, domain::property::PropertyVariant>& values
        ) override
        {
            values_ = values;
        }

    private:
        std::unordered_map<std::string, domain::property::PropertyVariant> values_;
    };

}

#endif //WXCLEANGRADUATOR_INMEMORYSETTINGSSTORAGE_H
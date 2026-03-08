#ifndef WXCLEANGRADUATOR_PROPERTYSOURCEBASE_H
#define WXCLEANGRADUATOR_PROPERTYSOURCEBASE_H

#include <stdexcept>
#include <string>
#include <vector>

#include "application/settings/SettingsService.h"
#include "domain/ports/property/IPropertySource.h"

namespace application::property
{

class PropertySourceBase : public domain::ports::IPropertySource
{
public:
    explicit PropertySourceBase(application::settings::SettingsService& settings);

    std::vector<domain::property::PropertyValue> propertyValues() const override;

    void setProperty(const domain::property::PropertyValue& value) override;

protected:
    [[nodiscard]] application::settings::SettingsService& settings();

    [[nodiscard]] const application::settings::SettingsService& settings() const;

private:
    [[nodiscard]] domain::property::PropertyVariant readValue(
        const domain::property::PropertyField& field
    ) const;

    [[nodiscard]] static bool isCompatible(
        const domain::property::PropertyField& field,
        const domain::property::PropertyVariant& value
    );

private:
    application::settings::SettingsService& settings_;
};

}

#endif //WXCLEANGRADUATOR_PROPERTYSOURCEBASE_H
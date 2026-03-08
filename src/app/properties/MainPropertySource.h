#ifndef WXCLEANGRADUATOR_MEASPROPERTYSOURCE_H
#define WXCLEANGRADUATOR_MEASPROPERTYSOURCE_H
#include <memory>

#include "application/property/PropertySourceBase.h"
#include "domain/ports/catalog/ICatalog.h"

#include "../../application/models/catalog/Printer.h"
#include "../../application/models/catalog/Displacement.h"
#include "application/models/Gauge.h"
#include "../../application/models/catalog/GaugePrecision.h"
#include "../../application/models/catalog/PressureUnit.h"

class MainPropertySource final : public application::property::PropertySourceBase
{
public:
    MainPropertySource(
        application::settings::SettingsService& settings,
        domain::ports::ICatalog<application::models::Printer>& printers,
        domain::ports::ICatalog<application::models::Displacement>& displacements,
        domain::ports::ICatalog<application::models::Gauge>& gauges,
        domain::ports::ICatalog<application::models::GaugePrecision>& gaugePrecisions,
        domain::ports::ICatalog<application::models::PressureUnit>& pressureUnits
    );

    std::vector<domain::property::PropertyField> propertySchema() const override;

private:
    domain::ports::ICatalog<application::models::Printer>& printers_;
    domain::ports::ICatalog<application::models::Displacement>& displacements_;
    domain::ports::ICatalog<application::models::Gauge>& gauges_;
    domain::ports::ICatalog<application::models::GaugePrecision>& gaugePrecisions_;
    domain::ports::ICatalog<application::models::PressureUnit>& pressureUnits_;
};


#endif //WXCLEANGRADUATOR_MEASPROPERTYSOURCE_H
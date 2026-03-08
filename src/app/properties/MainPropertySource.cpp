#include "MainPropertySource.h"

#include <application/models/Printer.h>

#include "application/models/Displacement.h"
#include "application/models/Gauge.h"
#include "application/models/GaugePrecision.h"
#include "application/models/PressureUnit.h"
#include "domain/core/common/PressureUnit.h"
#include "infrastructure/catalog/Catalog.h"

template<class T, class F>
std::vector<domain::property::EnumOption>
makeOptions(const std::vector<T>& items, F nameGetter)
{
    using namespace domain::property;

    std::vector<EnumOption> options;
    options.reserve(items.size());

    int index = 0;

    for (const auto& item : items)
        options.emplace_back(EnumOption{ index++, nameGetter(item) });

    return options;
}


static domain::property::EnumPropertyField makeEnumField(
    const std::string& id,
    const std::string& name,
    std::vector<domain::property::EnumOption> options)
{
    using namespace domain::property;

    return EnumPropertyField{
        PropertyMeta{
            id,
            name,
            "Main",
            {}
        },
        0,
        std::move(options)
    };
}

std::vector<domain::property::PropertyField> MainPropertySource::propertySchema() const
{
    using namespace domain::property;

    infra::Catalog<application::models::Printer> printers("catalogs/printers.txt");
    printers.load();

    infra::Catalog<application::models::Displacement> displacements("catalogs/displacements.txt");
    displacements.load();

    infra::Catalog<application::models::Gauge> gauges("catalogs/gauges.txt");
    gauges.load();

    infra::Catalog<application::models::GaugePrecision> gaugePrecisions("catalogs/gauge_precision.txt");
    gaugePrecisions.load();

    infra::Catalog<application::models::PressureUnit> pressureUnits("catalogs/pressure_units.txt");
    pressureUnits.load();


    auto printerOptions = makeOptions(printers.items(),
        [](const auto& x){ return x.name; });

    auto displacementOptions = makeOptions(displacements.items(),
        [](const auto& x){ return x.name; });

    auto gaugeOptions = makeOptions(gauges.items(),
        [](const auto& x){ return x.name; });

    auto precisionOptions = makeOptions(gaugePrecisions.items(),
        [](const auto& x){ return std::to_string(x.value); });

    auto pressureUnitOptions = makeOptions(pressureUnits.items(),
        [](const auto& x){ return to_string(x.unit); });

    return {

        makeEnumField(
            "main.printers",
            "Printer",
            std::move(printerOptions)
        ),

        makeEnumField(
            "main.displacement",
            "Displacement",
            std::move(displacementOptions)
        ),

        makeEnumField(
            "main.gauge",
            "Gauge",
            std::move(gaugeOptions)
        ),

        makeEnumField(
            "main.gaugePrecision",
            "Gauge precision",
            std::move(precisionOptions)
        ),

        makeEnumField(
            "main.pressureUnit",
            "Pressure unit",
            std::move(pressureUnitOptions)
        )
    };
}

#include "MainPropertySource.h"

#include "domain/core/common/PressureUnit.h"

using namespace domain::property;

MainPropertySource::MainPropertySource(
    application::settings::SettingsService& settings,
    domain::ports::ICatalog<application::models::Printer>& printers,
    domain::ports::ICatalog<application::models::Displacement>& displacements,
    domain::ports::ICatalog<application::models::Gauge>& gauges,
    domain::ports::ICatalog<application::models::GaugePrecision>& gaugePrecisions,
    domain::ports::ICatalog<application::models::PressureUnit>& pressureUnits
)
    : PropertySourceBase(settings),
      printers_(printers),
      displacements_(displacements),
      gauges_(gauges),
      gaugePrecisions_(gaugePrecisions),
      pressureUnits_(pressureUnits)
{
}

template<class T, class F>
std::vector<EnumOption>
makeOptions(const std::vector<T>& items, F nameGetter)
{
    std::vector<EnumOption> options;
    options.reserve(items.size());

    int index = 0;

    for (const auto& item : items)
        options.emplace_back(EnumOption{ index++, nameGetter(item) });

    return options;
}

static EnumPropertyField makeEnumField(
    const std::string& id,
    const std::string& name,
    std::vector<EnumOption> options)
{
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

std::vector<PropertyField> MainPropertySource::propertySchema() const
{
    auto printerOptions = makeOptions(printers_.items(),
        [](const auto& x){ return x.name; });

    auto displacementOptions = makeOptions(displacements_.items(),
        [](const auto& x){ return x.name; });

    auto gaugeOptions = makeOptions(gauges_.items(),
        [](const auto& x){ return x.name; });

    auto precisionOptions = makeOptions(gaugePrecisions_.items(),
        [](const auto& x){ return std::to_string(x.value); });

    auto pressureUnitOptions = makeOptions(pressureUnits_.items(),
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
#include "WxSliderFloatBinding.h"

#include "application/property/PropertyObserverRegistry.h"

ui::wx::bindings::WxSliderFloatBinding::WxSliderFloatBinding(wxSlider &slider,
                                                             application::property::PropertyRegistry &registry, application::property::PropertyObserverRegistry &observers,
                                                             std::string propertyId): slider_(slider)
                                                                                      , registry_(registry)
                                                                                      , propertyId_(std::move(propertyId)) {
    observers.subscribe(propertyId_, this);

    slider_.Bind(wxEVT_SLIDER, [this](wxCommandEvent&)
    {
        const float value = slider_.GetValue() / 100.0f;

        registry_.setProperty({
            propertyId_,
            value
        });
    });
}

void ui::wx::bindings::WxSliderFloatBinding::onPropertyChanged(const domain::property::PropertyValue &value) {
    if (value.id != propertyId_)
        return;

    if (const auto* v = std::get_if<float>(&value.value))
        slider_.SetValue(static_cast<int>(*v * 100.0f));
}

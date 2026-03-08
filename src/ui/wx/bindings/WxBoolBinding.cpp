#include "WxBoolBinding.h"
#include "application/property/PropertyObserverRegistry.h"

ui::wx::bindings::WxBoolBinding::WxBoolBinding(
    wxCheckBox &checkBox,
    application::property::PropertyRegistry &registry,
    application::property::PropertyObserverRegistry &observers, std::string propertyId)
        : checkBox_(checkBox)
        , registry_(registry)
        , propertyId_(std::move(propertyId))
{
    observers.subscribe(propertyId_, this);

    checkBox_.Bind(wxEVT_CHECKBOX, [this](wxCommandEvent&)
    {
        registry_.setProperty({
            propertyId_,
            checkBox_.GetValue()
        });
    });
}

void ui::wx::bindings::WxBoolBinding::onPropertyChanged(const domain::property::PropertyValue &value) {
    if (value.id != propertyId_)
        return;

    if (const auto* v = std::get_if<bool>(&value.value))
        checkBox_.SetValue(*v);
}

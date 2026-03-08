#include "WxTextBinding.h"

#include "application/property/PropertyObserverRegistry.h"

ui::wx::bindings::WxTextBinding::WxTextBinding(wxTextCtrl &textCtrl, application::property::PropertyRegistry &registry,
                                               application::property::PropertyObserverRegistry &observers, std::string propertyId): textCtrl_(textCtrl)
                                                                                                                                    , registry_(registry)
                                                                                                                                    , propertyId_(std::move(propertyId))
{
    observers.subscribe(propertyId_, this);

    textCtrl_.Bind(wxEVT_TEXT, [this](wxCommandEvent&)
    {
        registry_.setProperty({
            propertyId_,
            textCtrl_.GetValue().ToStdString()
        });
    });
}

void ui::wx::bindings::WxTextBinding::onPropertyChanged(const domain::property::PropertyValue &value) {
    if (value.id != propertyId_)
        return;

    if (const auto* v = std::get_if<std::string>(&value.value))
        textCtrl_.SetValue(*v);
}

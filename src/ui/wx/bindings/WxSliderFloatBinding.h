#ifndef WXCLEANGRADUATOR_WXSLIDERFLOATBINDING_H
#define WXCLEANGRADUATOR_WXSLIDERFLOATBINDING_H

#include <wx/slider.h>
#include <string>

#include "application/property/PropertyRegistry.h"
#include "domain/ports/property/IPropertyObserver.h"

namespace ui::wx::bindings
{

    class WxSliderFloatBinding : public domain::ports::IPropertyObserver
    {
    public:
        WxSliderFloatBinding(
            wxSlider& slider,
            application::property::PropertyRegistry& registry,
            application::property::PropertyObserverRegistry& observers,
            std::string propertyId
        );

        void onPropertyChanged(const domain::property::PropertyValue& value) override;

    private:
        wxSlider& slider_;
        application::property::PropertyRegistry& registry_;
        std::string propertyId_;
    };

}

#endif //WXCLEANGRADUATOR_WXSLIDERFLOATBINDING_H
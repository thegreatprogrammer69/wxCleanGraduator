#ifndef WXCLEANGRADUATOR_WXBOOLBINDING_H
#define WXCLEANGRADUATOR_WXBOOLBINDING_H

#include <wx/checkbox.h>
#include <string>

#include "application/property/PropertyRegistry.h"
#include "domain/ports/property/IPropertyObserver.h"

namespace ui::wx::bindings
{

    class WxBoolBinding : public domain::ports::IPropertyObserver
    {
    public:
        WxBoolBinding(
            wxCheckBox& checkBox,
            application::property::PropertyRegistry& registry,
            application::property::PropertyObserverRegistry& observers,
            std::string propertyId
        );

        void onPropertyChanged(const domain::property::PropertyValue& value) override;

    private:
        wxCheckBox& checkBox_;
        application::property::PropertyRegistry& registry_;
        std::string propertyId_;
    };

}


#endif //WXCLEANGRADUATOR_WXBOOLBINDING_H
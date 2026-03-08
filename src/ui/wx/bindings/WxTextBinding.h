#ifndef WXCLEANGRADUATOR_WXTEXTBINDING_H
#define WXCLEANGRADUATOR_WXTEXTBINDING_H


#include <wx/textctrl.h>
#include <string>

#include "application/property/PropertyRegistry.h"
#include "domain/ports/property/IPropertyObserver.h"

namespace ui::wx::bindings
{

    class WxTextBinding : public domain::ports::IPropertyObserver
    {
    public:
        WxTextBinding(
            wxTextCtrl& textCtrl,
            application::property::PropertyRegistry& registry,
            application::property::PropertyObserverRegistry& observers,
            std::string propertyId
        );

        void onPropertyChanged(const domain::property::PropertyValue& value) override;

    private:
        wxTextCtrl& textCtrl_;
        application::property::PropertyRegistry& registry_;
        std::string propertyId_;
    };

}


#endif //WXCLEANGRADUATOR_WXTEXTBINDING_H
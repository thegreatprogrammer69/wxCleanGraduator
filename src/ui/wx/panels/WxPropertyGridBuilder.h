#ifndef WXCLEANGRADUATOR_WXPROPERTYGRIDBUILDER_H
#define WXCLEANGRADUATOR_WXPROPERTYGRIDBUILDER_H


#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/manager.h>
#include <unordered_set>

#include "application/property/PropertyRegistry.h"

namespace ui::wx::panels
{

class WxPropertyGridBuilder
{
public:
    static void build(
        wxPropertyGridManager& grid,
        application::property::PropertyRegistry& registry
    );
};

}


#endif //WXCLEANGRADUATOR_WXPROPERTYGRIDBUILDER_H
#ifndef WXCLEANGRADUATOR_WXBINDINGUTILS_H
#define WXCLEANGRADUATOR_WXBINDINGUTILS_H

#include <wx/variant.h>
#include <string>

namespace ui::wx::bindings
{
    inline wxString toWxString(const std::string& s)
    {
        return wxString::FromUTF8(s);
    }

    inline std::string fromWxString(const wxString& s)
    {
        return s.ToStdString();
    }
}

#endif //WXCLEANGRADUATOR_WXBINDINGUTILS_H
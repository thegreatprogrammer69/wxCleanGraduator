#ifndef WXCLEANGRADUATOR_VIDEOGRIDWIDGET_H
#define WXCLEANGRADUATOR_VIDEOGRIDWIDGET_H

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <array>

class WxVideoGridWidget : public wxWindow
{
public:
    explicit WxVideoGridWidget(wxWindow* parent);

    wxGLCanvas* GetVideoCanvas(int idx);
    wxGLContext* GetVideoContext(int idx);

private:
    static constexpr int COLS = 2;
    static constexpr int ROWS = 4;
    static constexpr int COUNT = COLS * ROWS;

    std::array<wxGLCanvas*, COUNT> cells_{};
    std::array<wxGLContext*, COUNT> contexts_{};

    void OnSize(wxSizeEvent& evt);
    void LayoutGrid();
};

#endif // WXCLEANGRADUATOR_VIDEOGRIDWIDGET_H
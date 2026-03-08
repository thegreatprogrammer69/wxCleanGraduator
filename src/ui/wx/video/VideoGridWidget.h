#ifndef WXCLEANGRADUATOR_VIDEOGRIDWIDGET_H
#define WXCLEANGRADUATOR_VIDEOGRIDWIDGET_H

#include <wx/wx.h>
#include <array>

class VideoGridWidget : public wxWindow
{
public:

    VideoGridWidget(wxWindow* parent);

    void* GetVideoHandle(int idx);

private:

    static constexpr int COLS = 2;
    static constexpr int ROWS = 4;
    static constexpr int COUNT = COLS * ROWS;

    std::array<wxWindow*, COUNT> cells;

    void OnSize(wxSizeEvent& evt);
    void LayoutGrid();

};

#endif //WXCLEANGRADUATOR_VIDEOGRIDWIDGET_H
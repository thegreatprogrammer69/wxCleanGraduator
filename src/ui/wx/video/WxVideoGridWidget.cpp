#include "WxVideoGridWidget.h"

WxVideoGridWidget::WxVideoGridWidget(wxWindow* parent)
    : wxWindow(parent,
               wxID_ANY,
               wxDefaultPosition,
               wxDefaultSize,
               wxCLIP_CHILDREN)
{
    Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {});

    const int gl_attribs[] = {
        WX_GL_RGBA,
        WX_GL_DOUBLEBUFFER,
        WX_GL_DEPTH_SIZE, 24,
        0
    };

    for (int i = 0; i < COUNT; ++i)
    {
        cells_[i] = new wxGLCanvas(
            this,
            wxID_ANY,
            gl_attribs,
            wxDefaultPosition,
            wxDefaultSize,
            wxBORDER_NONE
        );

        cells_[i]->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
        cells_[i]->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {});

        contexts_[i] = new wxGLContext(cells_[i]);
    }

    Bind(wxEVT_SIZE, &WxVideoGridWidget::OnSize, this);
    LayoutGrid();
}

wxGLCanvas* WxVideoGridWidget::GetVideoCanvas(int idx)
{
    if (idx < 0 || idx >= COUNT)
        return nullptr;

    return cells_[idx];
}

wxGLContext* WxVideoGridWidget::GetVideoContext(int idx)
{
    if (idx < 0 || idx >= COUNT)
        return nullptr;

    return contexts_[idx];
}

void WxVideoGridWidget::OnSize(wxSizeEvent& evt)
{
    LayoutGrid();
    evt.Skip();
}

void WxVideoGridWidget::LayoutGrid()
{
    const wxSize size = GetClientSize();

    const int totalH = size.GetHeight();
    const int cellH = totalH / ROWS;
    const int cellW = cellH;

    const int gridW = cellW * COLS;

    int offsetX = (size.GetWidth() - gridW) / 2;
    if (offsetX < 0)
        offsetX = 0;

    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c < COLS; ++c)
        {
            const int idx = r * COLS + c;

            const int x = offsetX + c * cellW;
            const int y = r * cellH;

            cells_[idx]->SetSize(x, y, cellW, cellH);
        }
    }
}
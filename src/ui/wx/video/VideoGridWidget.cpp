#include "VideoGridWidget.h"

VideoGridWidget::VideoGridWidget(wxWindow* parent)
    : wxWindow(parent,
               wxID_ANY,
               wxDefaultPosition,
               wxDefaultSize,
               wxCLIP_CHILDREN)
{
    Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {});

    for (int i = 0; i < COUNT; ++i)
    {
        cells[i] = new wxWindow(
            this,
            wxID_ANY,
            wxDefaultPosition,
            wxDefaultSize,
            wxBORDER_NONE
        );

        cells[i]->SetBackgroundStyle(wxBG_STYLE_CUSTOM);

        cells[i]->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {});
    }

    Bind(wxEVT_SIZE, &VideoGridWidget::OnSize, this);
}

void* VideoGridWidget::GetVideoHandle(int idx)
{
    if (idx < 0 || idx >= COUNT)
        return nullptr;

    return cells[idx]->GetHandle();
}

void VideoGridWidget::OnSize(wxSizeEvent& evt)
{
    LayoutGrid();
    evt.Skip();
}

void VideoGridWidget::LayoutGrid()
{
    wxSize size = GetClientSize();

    int totalH = size.GetHeight();
    int cellH = totalH / ROWS;

    int cellW = cellH; // ширина зависит от высоты

    int gridW = cellW * COLS;

    int offsetX = (size.GetWidth() - gridW) / 2;
    if (offsetX < 0)
        offsetX = 0;

    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c < COLS; ++c)
        {
            int idx = r * COLS + c;

            int x = offsetX + c * cellW;
            int y = r * cellH;

            cells[idx]->SetSize(x, y, cellW, cellH);
        }
    }
}
#include "WxMainWindow.h"

WxMainWindow::WxMainWindow()
    : wxFrame(nullptr,
              wxID_ANY,
              "Video Application",
              wxDefaultPosition,
              wxSize(1000, 700))
{
    // Главная панель
    wxPanel* panel = new wxPanel(this);

    // Создаём сетку видео
    videoGrid = new WxVideoGridWidget(panel);

    // Можно добавить правую панель (например список пользователей)
    wxPanel* rightPanel = new wxPanel(panel);
    rightPanel->SetMinSize(wxSize(200, -1));

    // Горизонтальный layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    mainSizer->Add(videoGrid, 1, wxEXPAND | wxALL, 5);   // слева
    mainSizer->Add(rightPanel, 0, wxEXPAND | wxALL, 5);  // справа

    panel->SetSizer(mainSizer);
}
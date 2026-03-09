#ifndef WXCLEANGRADUATOR_WXMAINWINDOW_H
#define WXCLEANGRADUATOR_WXMAINWINDOW_H


#include <wx/wx.h>
#include "ui/wx/video/WxVideoGridWidget.h"

class WxMainWindow : public wxFrame
{
public:
    WxMainWindow();

public:
    WxVideoGridWidget* videoGrid;
};


#endif //WXCLEANGRADUATOR_WXMAINWINDOW_H
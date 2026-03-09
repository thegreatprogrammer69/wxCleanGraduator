#ifndef WXCLEANGRADUATOR_UIBOOTSTRAP_H
#define WXCLEANGRADUATOR_UIBOOTSTRAP_H
#include <memory>
#include "ApplicationBootstrap.h"
#include "domain/ports/video_source/IVideoSink.h"



class WxVideoGridWidget;
class WxMainWindow;

class UiBootstrap {
public:
    explicit UiBootstrap(ApplicationBootstrap& application_bootstrap);
    ~UiBootstrap();

    void initialize();

    std::unique_ptr<WxMainWindow> main_window;
    WxVideoGridWidget* video_grid_widget;

    std::vector<std::unique_ptr<domain::ports::IVideoSink>> video_renderers;

private:
    ApplicationBootstrap& application_bootstrap_;

    void createMainWindow();

    void createVideoRenderers();
};


#endif //WXCLEANGRADUATOR_UIBOOTSTRAP_H
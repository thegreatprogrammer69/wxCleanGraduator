#include "UiBootstrap.h"

#include "infrastructure/video_renderer/VideoRenderer.h"
#include "ui/wx/main_window/WxMainWindow.h"

UiBootstrap::UiBootstrap(ApplicationBootstrap &application_bootstrap)
    : application_bootstrap_(application_bootstrap)
{
}

UiBootstrap::~UiBootstrap() {
}

void UiBootstrap::initialize() {
    createMainWindow();

    createVideoRenderers();
}

void UiBootstrap::createMainWindow() {
    main_window = std::make_unique<WxMainWindow>();
    video_grid_widget = main_window->videoGrid;
}

void UiBootstrap::createVideoRenderers() {
    int i = 0;
    for (const auto& source : application_bootstrap_.video_sources) {
        wxGLCanvas* canvas = video_grid_widget->GetVideoCanvas(i);
        wxGLContext* context = video_grid_widget->GetVideoContext(i);
        video_renderers.emplace_back(new infra::video_renderer::VideoRenderer(*source, video_grid_widget->GetVideoCanvas(i)));
        i++;
    }
}


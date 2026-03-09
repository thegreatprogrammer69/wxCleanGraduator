#include <wx/wx.h>

#include "app/bootstrap/ApplicationBootstrap.h"
#include "app/bootstrap/UiBootstrap.h"
#include "domain/ports/video_source/IVideoSource.h"
#include "ui/wx/main_window/WxMainWindow.h"


class App : public wxApp
{
public:
    bool OnInit() override;

private:
    std::unique_ptr<ApplicationBootstrap> application_bootstrap_;
    std::unique_ptr<UiBootstrap> ui_bootstrap_;
};

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    application_bootstrap_ = std::make_unique<ApplicationBootstrap>("setup", "catalogs", "logs");
    application_bootstrap_->initialize();

    application_bootstrap_->video_sources[0]->open();

    ui_bootstrap_ = std::make_unique<UiBootstrap>(*application_bootstrap_);
    ui_bootstrap_->initialize();

    ui_bootstrap_->main_window->Show();

    return true;
}
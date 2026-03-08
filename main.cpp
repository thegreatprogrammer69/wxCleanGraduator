#include <wx/wx.h>
#include <wx/artprov.h>
#include <wx/notebook.h>
#include <wx/listctrl.h>
#include <wx/dataview.h>
#include <wx/treectrl.h>
#include <wx/spinctrl.h>
#include <wx/slider.h>
#include <wx/gauge.h>
#include <wx/toolbar.h>
#include <wx/timer.h>

class MainFrame : public wxFrame
{
public:
    MainFrame()
        : wxFrame(nullptr, wxID_ANY,
                  "wxCleanGraduator — Test Application",
                  wxDefaultPosition,
                  wxSize(1100, 750))
    {
        CreateMenu();
        CreateToolBarUI();
        CreateStatusBar(2);

        auto* rootPanel = new wxPanel(this);
        auto* mainSizer = new wxBoxSizer(wxVERTICAL);

        auto* notebook = new wxNotebook(rootPanel, wxID_ANY);

        notebook->AddPage(CreateControlsPage(notebook), "Controls");
        notebook->AddPage(CreateDataPage(notebook), "Data");
        notebook->AddPage(CreateLogsPage(notebook), "Logs");

        mainSizer->Add(notebook, 1, wxEXPAND | wxALL, 5);

        rootPanel->SetSizer(mainSizer);

        // Таймер для демонстрации
        timer.SetOwner(this);
        Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);
        timer.Start(100);
    }

private:
    wxGauge* gauge = nullptr;
    wxTextCtrl* logOutput = nullptr;
    wxTimer timer;
    int progress = 0;

    void CreateMenu()
    {
        auto* fileMenu = new wxMenu;
        fileMenu->Append(wxID_NEW, "&New");
        fileMenu->Append(wxID_OPEN, "&Open");
        fileMenu->AppendSeparator();
        fileMenu->Append(wxID_EXIT, "E&xit");

        auto* helpMenu = new wxMenu;
        helpMenu->Append(wxID_ABOUT, "&About");

        auto* menuBar = new wxMenuBar;
        menuBar->Append(fileMenu, "&File");
        menuBar->Append(helpMenu, "&Help");

        SetMenuBar(menuBar);

        Bind(wxEVT_MENU, [this](wxCommandEvent&) { Close(true); }, wxID_EXIT);
        Bind(wxEVT_MENU, [this](wxCommandEvent&) {
            wxMessageBox("wxWidgets demo project",
                         "About",
                         wxOK | wxICON_INFORMATION);
        }, wxID_ABOUT);
    }

    void CreateToolBarUI()
    {
        auto* tb = CreateToolBar();
        tb->AddTool(wxID_NEW, "New", wxArtProvider::GetBitmap(wxART_NEW));
        tb->AddTool(wxID_OPEN, "Open", wxArtProvider::GetBitmap(wxART_FILE_OPEN));
        tb->AddSeparator();
        tb->AddTool(wxID_EXIT, "Exit", wxArtProvider::GetBitmap(wxART_QUIT));
        tb->Realize();
    }

    wxPanel* CreateControlsPage(wxWindow* parent)
    {
        auto* panel = new wxPanel(parent);
        auto* sizer = new wxBoxSizer(wxVERTICAL);

        auto* formSizer = new wxFlexGridSizer(2, 10, 10);

        formSizer->Add(new wxStaticText(panel, wxID_ANY, "Name:"), 0, wxALIGN_CENTER_VERTICAL);
        auto* nameCtrl = new wxTextCtrl(panel, wxID_ANY);
        formSizer->Add(nameCtrl, 1, wxEXPAND);

        formSizer->Add(new wxStaticText(panel, wxID_ANY, "Age:"), 0, wxALIGN_CENTER_VERTICAL);
        auto* spin = new wxSpinCtrl(panel, wxID_ANY);
        spin->SetRange(0, 120);
        formSizer->Add(spin, 1, wxEXPAND);

        formSizer->Add(new wxStaticText(panel, wxID_ANY, "Gender:"), 0, wxALIGN_CENTER_VERTICAL);
        auto* combo = new wxComboBox(panel, wxID_ANY);
        combo->Append("Male");
        combo->Append("Female");
        combo->Append("Other");
        formSizer->Add(combo, 1, wxEXPAND);

        formSizer->AddGrowableCol(1, 1);

        sizer->Add(formSizer, 0, wxEXPAND | wxALL, 10);

        auto* check = new wxCheckBox(panel, wxID_ANY, "Subscribe to newsletter");
        sizer->Add(check, 0, wxLEFT | wxBOTTOM, 10);

        auto* radioBox = new wxRadioBox(panel, wxID_ANY,
                                        "Priority",
                                        wxDefaultPosition,
                                        wxDefaultSize,
                                        {"Low", "Medium", "High"});
        sizer->Add(radioBox, 0, wxALL, 10);

        auto* slider = new wxSlider(panel, wxID_ANY, 50, 0, 100);
        sizer->Add(slider, 0, wxEXPAND | wxALL, 10);

        gauge = new wxGauge(panel, wxID_ANY, 100);
        sizer->Add(gauge, 0, wxEXPAND | wxALL, 10);

        auto* btn = new wxButton(panel, wxID_ANY, "Submit");
        sizer->Add(btn, 0, wxALL, 10);

        btn->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
            wxString msg;
            msg << "Name: " << nameCtrl->GetValue()
                << "\nAge: " << spin->GetValue()
                << "\nGender: " << combo->GetValue();
            wxMessageBox(msg, "Form Data");
        });

        panel->SetSizer(sizer);
        return panel;
    }

    wxPanel* CreateDataPage(wxWindow* parent)
    {
        auto* panel = new wxPanel(parent);
        auto* sizer = new wxBoxSizer(wxHORIZONTAL);

        auto* tree = new wxTreeCtrl(panel, wxID_ANY,
                                    wxDefaultPosition,
                                    wxSize(250, -1),
                                    wxTR_DEFAULT_STYLE);

        auto root = tree->AddRoot("Root");
        tree->AppendItem(root, "Item 1");
        tree->AppendItem(root, "Item 2");
        tree->ExpandAll();

        auto* list = new wxListCtrl(panel, wxID_ANY,
                                    wxDefaultPosition,
                                    wxDefaultSize,
                                    wxLC_REPORT);

        list->InsertColumn(0, "ID");
        list->InsertColumn(1, "Name");
        list->InsertItem(0, "1");
        list->SetItem(0, 1, "Alice");
        list->InsertItem(1, "2");
        list->SetItem(1, 1, "Bob");

        sizer->Add(tree, 0, wxEXPAND | wxALL, 5);
        sizer->Add(list, 1, wxEXPAND | wxALL, 5);

        panel->SetSizer(sizer);
        return panel;
    }

    wxPanel* CreateLogsPage(wxWindow* parent)
    {
        auto* panel = new wxPanel(parent);
        auto* sizer = new wxBoxSizer(wxVERTICAL);

        logOutput = new wxTextCtrl(panel,
                                   wxID_ANY,
                                   "",
                                   wxDefaultPosition,
                                   wxDefaultSize,
                                   wxTE_MULTILINE | wxTE_READONLY);

        sizer->Add(logOutput, 1, wxEXPAND | wxALL, 5);
        panel->SetSizer(sizer);
        return panel;
    }

    void OnTimer(wxTimerEvent&)
    {
        progress = (progress + 1) % 101;
        if (gauge)
            gauge->SetValue(progress);

        if (logOutput)
            logOutput->AppendText("Tick: " + wxString::Format("%d\n", progress));
    }
};

class App : public wxApp
{
public:
    bool OnInit() override
    {
        auto* frame = new MainFrame();
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP_NO_MAIN(App);

int main(int argc, char** argv)
{
    setenv("GTK_THEME", "Breeze", 1);
    wxDISABLE_DEBUG_SUPPORT();
    return wxEntry(argc, argv);
}
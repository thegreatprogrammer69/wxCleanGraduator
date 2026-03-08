#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/manager.h>
#include <wx/sysopt.h>
#include <cstdlib>

#include "app/properties/MainPropertySource.h"
#include "application/property/PropertyEngine.h"
#include "infrastructure/settings/InMemorySettingsStorage.h"

#include <iostream>

#include "application/property/PropertyUtils.h"

class ConsolePropertyObserver : public domain::ports::IPropertyObserver
{
public:

    void onPropertyChanged(
        const domain::property::PropertyValue& value
    ) override
    {
        std::cout
            << "[Property changed] "
            << value.id
            << " = "
            << application::property::propertyToString(value.value)
            << std::endl;
    }
};

class MainFrame : public wxFrame
{
public:

    MainFrame()
        : wxFrame(nullptr,
                  wxID_ANY,
                  "Property Engine Demo",
                  wxDefaultPosition,
                  wxSize(600, 400))
    {
        grid = new wxPropertyGridManager(
            this,
            wxID_ANY,
            wxDefaultPosition,
            wxDefaultSize,
            wxPG_SPLITTER_AUTO_CENTER
        );

        initEngine();
        buildGrid();

        grid->Bind(wxEVT_PG_CHANGED,
                   &MainFrame::onPropertyChanged,
                   this);
    }

private:

    void initEngine()
    {
        engine.load();

        engine.registerSource(mainSource);

        // подписываем observer на все свойства
        auto schema = engine.registry().schema();

        for (auto& field : schema)
        {
            auto meta = domain::property::propertyMeta(field);

            engine.observers().subscribe(
                meta.id,
                &consoleObserver
            );
        }
    }

    void buildGrid()
    {
        using namespace domain::property;

        grid->Clear();

        auto schema = engine.registry().schema();
        auto values = engine.registry().values();

        auto findValue = [&](const std::string& id)
        {
            for (auto& v : values)
                if (v.id == id)
                    return &v;

            return (PropertyValue*)nullptr;
        };

        for (auto& field : schema)
        {
            auto meta = propertyMeta(field);

            if (!meta.category.empty())
                grid->Append(new wxPropertyCategory(meta.category));

            std::visit([&](auto& f)
            {
                using T = std::decay_t<decltype(f)>;

                auto* value = findValue(meta.id);

                if constexpr (std::is_same_v<T, EnumPropertyField>)
                {
                    wxArrayString names;
                    wxArrayInt values;

                    for (auto& option : f.options)
                    {
                        names.Add(wxString::FromUTF8(option.name));
                        values.Add(option.value);
                    }

                    int current =
                        value
                        ? std::get<int>(value->value)
                        : f.defaultValue;

                    grid->Append(
                        new wxEnumProperty(
                            f.meta.name,
                            f.meta.id,
                            names,
                            values,
                            current
                        )
                    );
                }

            }, field);
        }
    }

    void onPropertyChanged(wxPropertyGridEvent& event)
    {
        wxPGProperty* prop = event.GetProperty();

        std::string id = prop->GetName().ToStdString();
        wxVariant value = prop->GetValue();

        if (value.IsType("long"))
        {
            engine.registry().setProperty({
                id,
                static_cast<int>(value.GetLong())
            });
        }
    }

private:

    wxPropertyGridManager* grid = nullptr;

    infrastructure::settings::InMemorySettingsStorage storage;
    application::settings::SettingsService settings{storage};
    application::property::PropertyEngine engine{settings};

    MainPropertySource mainSource{settings};

    ConsolePropertyObserver consoleObserver;
};

class App : public wxApp
{
public:

    bool OnInit() override
    {
#ifdef __linux__
        setenv("GTK_THEME", "Adwaita:light", 1);
#endif
#ifdef __WXMSW__
        wxSystemOptions::SetOption("msw.darkmode", 0);
#endif

        wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

        auto* frame = new MainFrame();
        frame->SetFont(font);
        frame->Show();
        return true;
    }

    void OnUnhandledException() override
    {
        try
        {
            throw;
        }
        catch (const std::exception& e)
        {
            wxMessageBox(e.what(), "Unhandled exception", wxOK | wxICON_ERROR);
        }
        catch (...)
        {
            wxMessageBox("Unknown exception", "Unhandled exception", wxOK | wxICON_ERROR);
        }
    }
};

wxIMPLEMENT_APP(App);
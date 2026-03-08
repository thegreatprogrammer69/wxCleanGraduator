add_library(wxcg_app INTERFACE)

# App composition root combines application services and adapters.
target_include_directories(wxcg_app
    INTERFACE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(wxcg_app
    INTERFACE
        wxcg_application
        wxcg_domain
        wxcg_infrastructure
        wxcg_ui
)

add_library(wxcg_ui INTERFACE)

# UI layer integrates wxWidgets bindings with application services.
target_include_directories(wxcg_ui
    INTERFACE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(wxcg_ui
    INTERFACE
        wxcg_application
        wxcg_domain
)

add_library(wxcg_infrastructure INTERFACE)

# Infrastructure layer implements ports and adapters.
target_include_directories(wxcg_infrastructure
    INTERFACE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(wxcg_infrastructure
    INTERFACE
        wxcg_application
        wxcg_domain
)

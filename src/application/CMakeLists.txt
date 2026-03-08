add_library(wxcg_application INTERFACE)

# Application layer depends on domain contracts.
target_include_directories(wxcg_application
    INTERFACE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(wxcg_application
    INTERFACE
        wxcg_domain
)

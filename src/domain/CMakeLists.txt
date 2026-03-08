add_library(wxcg_domain INTERFACE)

# Domain layer exports core abstractions and value objects.
target_include_directories(wxcg_domain
    INTERFACE
        ${PROJECT_SOURCE_DIR}/src
)

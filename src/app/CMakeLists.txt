set(APP_SOURCES
        properties/MainPropertySource.cpp
)

add_library(wxcg_app ${APP_SOURCES})

target_include_directories(wxcg_app
        PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(wxcg_app
        wxcg_application
        wxcg_domain
        wxcg_shared
        wxcg_infrastructure
        wxcg_ui
)

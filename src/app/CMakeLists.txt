set(APP_SOURCES
        bootstrap/ApplicationBootstrap.cpp
        bootstrap/UiBootstrap.cpp
        properties/MainPropertySource.cpp
)

find_package(wxWidgets REQUIRED COMPONENTS core base aui propgrid)
include(${wxWidgets_USE_FILE})

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
        ${wxWidgets_LIBRARIES}
)

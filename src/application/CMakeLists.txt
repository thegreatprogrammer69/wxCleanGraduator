set(APPLICATION_SOURCES
        property/PropertyObserverRegistry.cpp
        property/PropertyRegistry.cpp
        property/PropertySourceBase.cpp
        settings/SettingsService.cpp
        orchestrators/video/VideoSourceManager.cpp

)

add_library(wxcg_application ${APPLICATION_SOURCES})

target_include_directories(wxcg_application
        PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(wxcg_application
        wxcg_domain
        wxcg_shared
)

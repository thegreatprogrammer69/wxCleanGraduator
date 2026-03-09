set(UI_SOURCES
        wx/bindings/WxBoolBinding.cpp
        wx/bindings/WxSliderFloatBinding.cpp
        wx/bindings/WxTextBinding.cpp
        wx/panels/WxPropertyGridBuilder.cpp
        wx/video/WxVideoGridWidget.cpp
        wx/main_window/WxMainWindow.cpp
)

find_package(wxWidgets REQUIRED COMPONENTS core base aui propgrid)
include(${wxWidgets_USE_FILE})

add_library(wxcg_ui ${UI_SOURCES})

target_include_directories(wxcg_ui
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(wxcg_ui
        wxcg_application
        wxcg_domain
        ${wxWidgets_LIBRARIES}
)

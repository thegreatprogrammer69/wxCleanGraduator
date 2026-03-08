set(UI_HEADERS
    wx/bindings/WxBindingFactory.h
    wx/bindings/WxBindingUtils.h
    wx/bindings/WxBoolBinding.h
    wx/bindings/WxSliderFloatBinding.h
    wx/bindings/WxTextBinding.h
    wx/panels/WxPropertyGridBuilder.h
)

set(UI_SOURCES
    wx/bindings/WxBoolBinding.cpp
    wx/bindings/WxSliderFloatBinding.cpp
    wx/bindings/WxTextBinding.cpp
    wx/panels/WxPropertyGridBuilder.cpp
)

add_library(ui INTERFACE)

target_sources(ui
    INTERFACE
        ${UI_HEADERS}
        ${UI_SOURCES}
)

target_link_libraries(ui
    INTERFACE
        app
        application
        domain
)

target_include_directories(ui
    INTERFACE
        ${CMAKE_SOURCE_DIR}/src
)

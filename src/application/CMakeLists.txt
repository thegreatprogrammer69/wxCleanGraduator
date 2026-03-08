set(APPLICATION_HEADERS
    models/BatchContext.h
    models/Displacement.h
    models/Gauge.h
    models/GaugePrecision.h
    models/PressureUnit.h
    models/Printer.h
    property/PropertyEngine.h
    property/PropertyObserverRegistry.h
    property/PropertyRegistry.h
    property/PropertySourceBase.h
    property/PropertyUtils.h
    settings/SettingsService.h
)

set(APPLICATION_SOURCES
    property/PropertyObserverRegistry.cpp
    property/PropertyRegistry.cpp
    property/PropertySourceBase.cpp
    settings/SettingsService.cpp
)

add_library(application INTERFACE)

target_sources(application
    INTERFACE
        ${APPLICATION_HEADERS}
        ${APPLICATION_SOURCES}
)

target_link_libraries(application
    INTERFACE
        domain
)

target_include_directories(application
    INTERFACE
        ${CMAKE_SOURCE_DIR}/src
)

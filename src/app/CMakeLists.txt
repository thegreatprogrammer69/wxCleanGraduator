set(APP_HEADERS
    properties/MainPropertySource.h
)

set(APP_SOURCES
    properties/MainPropertySource.cpp
)

add_library(app INTERFACE)

target_sources(app
    INTERFACE
        ${APP_HEADERS}
        ${APP_SOURCES}
)

target_link_libraries(app
    INTERFACE
        application
)

target_include_directories(app
    INTERFACE
        ${CMAKE_SOURCE_DIR}/src
)

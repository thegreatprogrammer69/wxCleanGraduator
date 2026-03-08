set(SHARED_SOURCES
        ini/IniFile.cpp
        thread/ThreadWorker.cpp
        watchdog/SoftwareWatchdog.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/src)

find_package(fmt REQUIRED)

add_library(wxcg_shared ${SHARED_SOURCES})

target_link_libraries(wxcg_shared
        wxcg_domain
        fmt::fmt
)
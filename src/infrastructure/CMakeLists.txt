set(INFRASTRUCTURE_HEADERS
    catalog/Catalog.h
    settings/InMemorySettingsStorage.h
    video_sources/VideoSourceNotifier.h
    video_sources/VideoSourcePorts.h
    video_sources/linux/gstreamer/GStreamerCamera.h
    video_sources/linux/gstreamer/GStreamerCameraConfig.h
    video_sources/linux/v4l/V4LCamera.h
    video_sources/linux/v4l/V4LCameraConfig.h
    video_sources/windows/dshow/DShowCamera.h
    video_sources/windows/dshow/DShowCameraConfig.h
    video_sources/windows/dshow/QEDIT.H
    video_sources/windows/dshow/SampleGrabberCB.h
)

set(INFRASTRUCTURE_SOURCES
    catalog/Catalog.cpp
    video_sources/VideoSourceNotifier.cpp
    video_sources/linux/gstreamer/GStreamerCamera.cpp
    video_sources/linux/v4l/V4LCamera.cpp
    video_sources/windows/dshow/DShowCamera.cpp
    video_sources/windows/dshow/SampleGrabberCB.cpp
)

add_library(infrastructure INTERFACE)

target_sources(infrastructure
    INTERFACE
        ${INFRASTRUCTURE_HEADERS}
        ${INFRASTRUCTURE_SOURCES}
)

target_link_libraries(infrastructure
    INTERFACE
        application
        domain
)

target_include_directories(infrastructure
    INTERFACE
        ${CMAKE_SOURCE_DIR}/src
)

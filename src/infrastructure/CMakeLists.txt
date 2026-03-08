set(INFRASTRUCTURE_SOURCES
        catalog/FileCatalog.cpp

        clock/UptimeClock.cpp
        clock/SessionClock.cpp

        logging/FileLogger.cpp
        logging/ConsoleLogger.cpp
        logging/NamedMultiLogger.cpp

        video_sources/VideoSourceNotifier.cpp

        video_renderer/VideoRenderer.cpp


)

# Platform specific sources
if(WIN32)

    list(APPEND INFRASTRUCTURE_SOURCES
            video_sources/windows/dshow/DShowCamera.cpp
            video_sources/windows/dshow/SampleGrabberCB.cpp
    )

elseif(UNIX)

    list(APPEND INFRASTRUCTURE_SOURCES
            video_sources/linux/gstreamer/GStreamerCamera.cpp
            video_sources/linux/v4l/V4LCamera.cpp
            video_renderer/detail/GLRenderer.cpp
    )

    # ---- GStreamer ----
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GSTREAMER REQUIRED
            gstreamer-1.0
            gstreamer-video-1.0
            gstreamer-app-1.0
    )

endif()


add_library(wxcg_infrastructure ${INFRASTRUCTURE_SOURCES})

target_include_directories(wxcg_infrastructure
        PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${GSTREAMER_INCLUDE_DIRS}
)

target_link_libraries(wxcg_infrastructure
        wxcg_application
        wxcg_domain
        wxcg_shared

        ${GSTREAMER_LIBRARIES}
        ${V4L2_LIBRARIES}
)
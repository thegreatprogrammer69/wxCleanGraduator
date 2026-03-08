set(DOMAIN_SOURCES
        core/calibration/recording/TimeSeries.cpp
        core/common/PressureUnit.cpp
        core/motor/MotorFrequency.cpp
)

add_library(wxcg_domain ${DOMAIN_SOURCES})

target_include_directories(wxcg_domain
        PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)
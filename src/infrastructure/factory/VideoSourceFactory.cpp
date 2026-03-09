//
// Created by mint on 09.03.2026.
//

#include "VideoSourceFactory.h"

#include "infrastructure/video_sources/linux/v4l/V4LCamera.h"
#include "infrastructure/video_sources/linux/v4l/V4LCameraConfig.h"

infra::factory::VideoSourceFactory::VideoSourceFactory(const utils::config::IParameterStore &config, camera::VideoSourcePorts ports)
    : config_(config), ports_(ports)
{
}

infra::factory::VideoSourceFactory::~VideoSourceFactory() {
}

std::unique_ptr<domain::ports::IVideoSource> infra::factory::VideoSourceFactory::load() {
    std::string backend = config_.getString("backend", "");

#ifdef PLATFORM_LINUX

    if (backend == "v4l" || backend == "v4l2") {
        camera::V4LCameraConfig config{};
        config.source = config_.getString("source", "");
        config.width = config_.getInt("width", 480);
        config.height = config_.getInt("height", 640);
        config.fps = config_.getInt("fps", 30);
        return std::make_unique<camera::V4LCamera>(ports_, config);
    }

#elif defined PLATFORM_WINDOWS

    // TODO

#endif

    throw std::runtime_error("unsupported camera implementation: " + backend);
}

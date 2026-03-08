#ifndef WXCLEANGRADUATOR_VIDEOANGLESOURCE_H
#define WXCLEANGRADUATOR_VIDEOANGLESOURCE_H
#include "domain/core/common/SourceId.h"
#include "domain/ports/angle_source/IAngleSource.h"
#include "domain/ports/video_source/IVideoSource.h"

namespace domain::video {
    struct VideoAngleSource {
        common::SourceId id;
        angle::IAngleSource& angle_source;
        ports::IVideoSource& video_source;
    };
}

#endif //WXCLEANGRADUATOR_VIDEOANGLESOURCE_H
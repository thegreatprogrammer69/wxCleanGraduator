#ifndef WXCLEANGRADUATOR_IVIDEOANGLESOURCESSTORAGE_H
#define WXCLEANGRADUATOR_IVIDEOANGLESOURCESSTORAGE_H

#include <optional>
#include <vector>
#include "domain/core/common/SourceId.h"
#include "domain/core/video_source/VideoAngleSource.h"

namespace application::ports {

    struct IVideoAngleSourcesStorage {
        virtual std::vector<domain::video::VideoAngleSource> all() = 0;
        virtual std::optional<domain::video::VideoAngleSource> at(domain::common::SourceId id) const = 0;
        virtual ~IVideoAngleSourcesStorage() = default;
    };
}

#endif //WXCLEANGRADUATOR_IVIDEOANGLESOURCESSTORAGE_H
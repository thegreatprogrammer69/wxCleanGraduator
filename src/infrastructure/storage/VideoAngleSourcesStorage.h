#ifndef CLEANGRADUATOR_VIDEOSOURCESTORAGE_H
#define CLEANGRADUATOR_VIDEOSOURCESTORAGE_H

#include <vector>
#include <optional>
#include <algorithm>

#include "application/ports/video/IVideoAngleSourcesStorage.h"

namespace infra::storage {

    class VideoAngleSourcesStorage : public application::ports::IVideoAngleSourcesStorage {
    public:
        explicit VideoAngleSourcesStorage();
        ~VideoAngleSourcesStorage() override = default;

        void add(domain::video::VideoAngleSource source);
        std::vector<domain::video::VideoAngleSource> all() override;
        std::optional<domain::video::VideoAngleSource> at(domain::common::SourceId id) const override;

    private:
        std::vector<domain::video::VideoAngleSource> sources_;
    };

}

#endif //CLEANGRADUATOR_VIDEOSOURCESTORAGE_H
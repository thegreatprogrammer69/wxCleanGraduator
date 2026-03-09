#ifndef WXCLEANGRADUATOR_ANGLEVIDEOSOURCEFACTORY_H
#define WXCLEANGRADUATOR_ANGLEVIDEOSOURCEFACTORY_H
#include <filesystem>
#include <vector>

#include "domain/ports/video_source/IVideoSource.h"
#include "infrastructure/video_sources/VideoSourcePorts.h"
#include "shared/param/IParameterStore.h"

namespace infra::factory {
    class VideoSourceFactory final {
    public:
        explicit VideoSourceFactory(const utils::config::IParameterStore& config, camera::VideoSourcePorts ports);
        ~VideoSourceFactory();

        std::unique_ptr<domain::ports::IVideoSource> load();

    private:
        const utils::config::IParameterStore& config_;
        camera::VideoSourcePorts ports_;
    };
}


#endif //WXCLEANGRADUATOR_ANGLEVIDEOSOURCEFACTORY_H
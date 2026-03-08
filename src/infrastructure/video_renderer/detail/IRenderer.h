#ifndef WXCLEANGRADUATOR_IRENDERER_H
#define WXCLEANGRADUATOR_IRENDERER_H

#include "domain/core/video_source/VideoFramePacket.h"

namespace infra::video_renderer::detail {

    class IRenderer {
    public:
        virtual ~IRenderer() = default;

        virtual void render(const domain::video::VideoFramePacket& packet) = 0;
    };

}

#endif //WXCLEANGRADUATOR_IRENDERER_H
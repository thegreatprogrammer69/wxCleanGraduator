#ifndef WXCLEANGRADUATOR_VIDEORENDERER_H
#define WXCLEANGRADUATOR_VIDEORENDERER_H
#include <memory>

#include "domain/ports/video_source/IVideoSink.h"
#include "detail/IRenderer.h"

namespace domain::ports {
    struct IVideoSource;
}

namespace infra::video_renderer {

    class VideoRenderer final : public domain::ports::IVideoSink {
    public:
        explicit VideoRenderer(domain::ports::IVideoSource& video_source, void* window_handle);
        ~VideoRenderer() override;

        void onVideoFrame(const domain::video::VideoFramePacket &) override;

    private:
        domain::ports::IVideoSource& video_source_;
        void* window_handle_;
        int type_;
        std::unique_ptr<detail::IRenderer> renderer_{};
    };
}

#endif //WXCLEANGRADUATOR_VIDEORENDERER_H
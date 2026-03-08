#include "VideoRenderer.h"

#include "detail/GLRenderer.h"
#include "domain/ports/video_source/IVideoSource.h"

constexpr int DSHOW_RENDERER = 0;
constexpr int OPENGL_RENDERER = 1;

infra::video_renderer::VideoRenderer::VideoRenderer(
    domain::ports::IVideoSource &video_source,
    void *window_handle)
    : video_source_(video_source),
      window_handle_(window_handle)
{
#ifdef _WIN32

    if (auto* dshow = dynamic_cast<camera::DShowCamera*>(&video_source))
    {
        type_ = DSHOW_RENDERER;
        dshow->setWindowHandle(window_handle_);
    }

#else

    type_ = OPENGL_RENDERER;

    renderer_ = std::make_unique<detail::GLRenderer>(window_handle_);

    video_source_.addSink(*this);

#endif
}

infra::video_renderer::VideoRenderer::~VideoRenderer()
{
    video_source_.removeSink(*this);
}

void infra::video_renderer::VideoRenderer::onVideoFrame(
    const domain::video::VideoFramePacket &packet)
{
    if (!renderer_)
        return;

    renderer_->render(packet);
}
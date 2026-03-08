#ifndef WXCLEANGRADUATOR_GLRENDERER_H
#define WXCLEANGRADUATOR_GLRENDERER_H


#include <vector>

#include "IRenderer.h"

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>

namespace infra::video_renderer::detail {

    class GLRenderer final : public IRenderer {
    public:
        explicit GLRenderer(void* window);
        ~GLRenderer() override;

        void render(const domain::video::VideoFramePacket& packet) override;

    private:
        void initGL();
        void uploadFrame(const uint8_t* data, int width, int height);

    private:
        Display* display_{nullptr};
        Window window_{0};
        GLXContext context_{nullptr};

        GLuint texture_{0};

        int width_{0};
        int height_{0};

        std::vector<uint8_t> rgb_buffer_;
    };

}


#endif //WXCLEANGRADUATOR_GLRENDERER_H
#include "GLRenderer.h"

#include <cstring>
#include <stdexcept>
#include <string>

namespace infra::video_renderer::detail {

static inline uint8_t clamp(int v)
{
    if (v < 0) return 0;
    if (v > 255) return 255;
    return static_cast<uint8_t>(v);
}

static void yuyv_to_rgb(
    const uint8_t* yuyv,
    uint8_t* rgb,
    int width,
    int height)
{
    const int frameSize = width * height * 2;

    for (int i = 0, j = 0; i < frameSize; i += 4)
    {
        const int y0 = yuyv[i + 0];
        const int u  = yuyv[i + 1];
        const int y1 = yuyv[i + 2];
        const int v  = yuyv[i + 3];

        int c = y0 - 16;
        const int d = u - 128;
        const int e = v - 128;

        int r = (298 * c + 409 * e + 128) >> 8;
        int g = (298 * c - 100 * d - 208 * e + 128) >> 8;
        int b = (298 * c + 516 * d + 128) >> 8;

        rgb[j++] = clamp(r);
        rgb[j++] = clamp(g);
        rgb[j++] = clamp(b);

        c = y1 - 16;

        r = (298 * c + 409 * e + 128) >> 8;
        g = (298 * c - 100 * d - 208 * e + 128) >> 8;
        b = (298 * c + 516 * d + 128) >> 8;

        rgb[j++] = clamp(r);
        rgb[j++] = clamp(g);
        rgb[j++] = clamp(b);
    }
}

GLRenderer::GLRenderer(void* window)
    : window_(reinterpret_cast<Window>(window))
    , display_(nullptr)
    , context_(nullptr)
    , texture_(0)
    , width_(0)
    , height_(0)
{
    if (!window_)
        throw std::runtime_error("GLRenderer: window is null");

    if (!display_)
        throw std::runtime_error("GLRenderer: failed to open X display");

    initGL();
}

GLRenderer::~GLRenderer()
{
    if (display_ && context_)
    {
        glXMakeCurrent(display_, None, nullptr);
    }

    if (texture_ != 0)
    {
        glDeleteTextures(1, &texture_);
        texture_ = 0;
    }

    if (display_ && context_)
    {
        glXDestroyContext(display_, context_);
        context_ = nullptr;
    }

    if (display_)
    {
        XCloseDisplay(display_);
        display_ = nullptr;
    }
}

    void GLRenderer::initGL()
{
    XWindowAttributes attrs{};
    if (!XGetWindowAttributes(display_, window_, &attrs))
        throw std::runtime_error("GLRenderer: XGetWindowAttributes failed");

    XVisualInfo tpl{};
    tpl.visualid = XVisualIDFromVisual(attrs.visual);

    int count = 0;
    XVisualInfo* vi = XGetVisualInfo(display_, VisualIDMask, &tpl, &count);

    if (!vi)
        throw std::runtime_error("GLRenderer: XGetVisualInfo failed");

    context_ = glXCreateContext(display_, vi, nullptr, GL_TRUE);

    XFree(vi);

    if (!context_)
        throw std::runtime_error("GLRenderer: glXCreateContext failed");

    if (!glXMakeCurrent(display_, window_, context_))
        throw std::runtime_error("GLRenderer: glXMakeCurrent failed");

    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);
}

void GLRenderer::uploadFrame(const uint8_t* data, int width, int height)
{
    if (!data)
        throw std::runtime_error("GLRenderer::uploadFrame: data is null");

    if (width <= 0 || height <= 0)
        throw std::runtime_error("GLRenderer::uploadFrame: invalid frame size");

    if (!display_ || !context_)
        throw std::runtime_error("GLRenderer::uploadFrame: OpenGL context is not initialized");

    if (glXGetCurrentContext() != context_)
    {
        if (!glXMakeCurrent(display_, window_, context_))
            throw std::runtime_error("GLRenderer::uploadFrame: glXMakeCurrent failed");
    }

    if (width_ != width || height_ != height)
    {
        width_ = width;
        height_ = height;
        rgb_buffer_.resize(static_cast<size_t>(width) * static_cast<size_t>(height) * 3);
        glViewport(0, 0, width_, height_);
    }

    yuyv_to_rgb(data, rgb_buffer_.data(), width, height);

    glBindTexture(GL_TEXTURE_2D, texture_);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        rgb_buffer_.data());
}

void GLRenderer::render(const domain::video::VideoFramePacket& packet)
{
    auto frame = packet.frame;
    if (!frame)
        return;

    if (!frame->buffer.data)
        return;

    uploadFrame(frame->buffer.data, frame->width, frame->height);

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f,  1.0f);

    glEnd();

    glXSwapBuffers(display_, window_);
}

} // namespace infra::video_renderer::detail
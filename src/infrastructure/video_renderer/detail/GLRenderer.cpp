#include "GLRenderer.h"

#include <cstring>
#include <stdexcept>

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
    int frameSize = width * height * 2;

    for (int i = 0, j = 0; i < frameSize; i += 4)
    {
        int y0 = yuyv[i + 0];
        int u  = yuyv[i + 1];
        int y1 = yuyv[i + 2];
        int v  = yuyv[i + 3];

        int c = y0 - 16;
        int d = u - 128;
        int e = v - 128;

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
{
    window_ = reinterpret_cast<Window>(window);

    display_ = XOpenDisplay(nullptr);
    if (!display_)
        throw std::runtime_error("Failed to open X display");

    initGL();
}

GLRenderer::~GLRenderer()
{
    if (texture_)
        glDeleteTextures(1, &texture_);

    if (context_)
        glXDestroyContext(display_, context_);

    if (display_)
        XCloseDisplay(display_);
}

void GLRenderer::initGL()
{
    int attribs[] = {
        GLX_RGBA,
        GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER,
        None
    };

    XVisualInfo* vi = glXChooseVisual(display_, 0, attribs);
    context_ = glXCreateContext(display_, vi, nullptr, GL_TRUE);

    glXMakeCurrent(display_, window_, context_);

    glGenTextures(1, &texture_);

    glBindTexture(GL_TEXTURE_2D, texture_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);
}

void GLRenderer::uploadFrame(const uint8_t* data, int width, int height)
{
    if (width_ != width || height_ != height)
    {
        width_ = width;
        height_ = height;
        rgb_buffer_.resize(width * height * 3);
    }

    yuyv_to_rgb(data, rgb_buffer_.data(), width, height);

    glBindTexture(GL_TEXTURE_2D, texture_);

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

    uploadFrame(frame->buffer.data, frame->width, frame->height);

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);

    glTexCoord2f(0, 1); glVertex2f(-1, -1);
    glTexCoord2f(1, 1); glVertex2f(1, -1);
    glTexCoord2f(1, 0); glVertex2f(1, 1);
    glTexCoord2f(0, 0); glVertex2f(-1, 1);

    glEnd();

    glXSwapBuffers(display_, window_);
}

}
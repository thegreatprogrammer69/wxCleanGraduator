#ifndef IVIDEOOVERLAY_Y
#define IVIDEOOVERLAY_Y

namespace domain::video {
    struct VideoFramePacket;
}

namespace domain::ports {
    struct IVideoOverlay {
        virtual ~IVideoOverlay() = default;
        virtual void draw(const video::VideoFramePacket& frame) = 0;
    };
}

#endif //IVIDEOOVERLAY_Y
#ifndef IVIDEOSINK_H
#define IVIDEOSINK_H

namespace domain::video {
    struct VideoFramePacket;
}

namespace domain::ports {
    struct IVideoSink {
        virtual ~IVideoSink() = default;

        /// Вызывается источником при поступлении нового кадра.
        /// Контракт: реализация должна быть non-blocking или минимально блокирующей.
        virtual void onVideoFrame(const video::VideoFramePacket&) = 0;
    };
}

#endif //IVIDEOSINK_H
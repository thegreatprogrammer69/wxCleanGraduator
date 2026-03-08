#ifndef IFRAMESINK_H
#define IFRAMESINK_H

namespace domain::video {
    struct VideoSourceEvent;
}

namespace domain::ports {
    struct IVideoSourceObserver {
        virtual ~IVideoSourceObserver() = default;
        virtual void onVideoSourceEvent(const video::VideoSourceEvent&) = 0;
    };
}
#endif //IFRAMESINK_H
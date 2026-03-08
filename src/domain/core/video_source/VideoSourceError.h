#ifndef VIDEOSOURCEOPENERROR_H
#define VIDEOSOURCEOPENERROR_H
#include <string>

namespace domain::video {
    struct VideoSourceError {
        std::string message;
    };
}

#endif //VIDEOSOURCEOPENERROR_H
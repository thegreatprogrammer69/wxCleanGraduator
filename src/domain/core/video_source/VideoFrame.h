#ifndef VIDEOFRAME_H
#define VIDEOFRAME_H

#include <memory>
#include "PixelFormat.h"
#include "VideoBuffer.h"

namespace domain::video {

struct VideoFrame {
    int width = 0;
    int height = 0;
    PixelFormat format = PixelFormat::RGB24;
    VideoBuffer buffer;
};

using VideoFramePtr = std::shared_ptr<VideoFrame>;

}

#endif //VIDEOFRAME_H
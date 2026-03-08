#ifndef VIDEOOUTPUT_H
#define VIDEOOUTPUT_H
#include "VideoFrame.h"
#include "domain/core/common/Timestamp.h"

namespace domain::video {

    struct VideoFramePacket {
        common::Timestamp timestamp;
        VideoFramePtr frame;
    };

}


#endif //VIDEOOUTPUT_H
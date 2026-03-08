#ifndef ANGLEPACKET_H
#define ANGLEPACKET_H
#include "domain/core/common/Angle.h"
#include "domain/core/common/SourceId.h"
#include "domain/core/common/Timestamp.h"

namespace domain::angle {
    struct AngleSourcePacket {
        common::SourceId source_id;
        common::Timestamp timestamp;
        common::Angle angle;
    };
}

#endif //ANGLEPACKET_H

#ifndef PRESSUREPACKET_H
#define PRESSUREPACKET_H
#include "domain/core/common/Pressure.h"
#include "domain/core/common/Timestamp.h"

namespace domain::pressure {

    struct PressurePacket {
        common::Timestamp timestamp;
        common::Pressure pressure;
    };

}

#endif //PRESSUREPACKET_H
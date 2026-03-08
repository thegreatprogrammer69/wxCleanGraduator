#ifndef IPRESSURESINK_H
#define IPRESSURESINK_H

namespace domain::common {
    struct PressurePacket;
}

namespace domain::ports {
    struct IPressureSink {
        virtual ~IPressureSink() = default;
        virtual void onPressurePacket(const common::PressurePacket&) = 0;
    };
}

#endif //IPRESSURESINK_H
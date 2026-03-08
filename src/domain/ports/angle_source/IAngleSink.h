#ifndef IANGLESINK_H
#define IANGLESINK_H

namespace domain::angle {
    struct AngleSourcePacket;
    struct IAngleSink {
        virtual ~IAngleSink() = default;
        virtual void onAnglePacket(const AngleSourcePacket&) = 0;
    };
}

#endif //IANGLESINK_H
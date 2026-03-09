#ifndef ISESSIONCLOCK1_H
#define ISESSIONCLOCK1_H
#include "IClock.h"
#include "domain/core/common/Timestamp.h"

namespace domain::ports {
    struct ISessionClock : IClock {
        virtual ~ISessionClock() = default;
        virtual void start() = 0;
        virtual void stop() = 0;
    };
}

#endif //ISESSIONCLOCK1_H
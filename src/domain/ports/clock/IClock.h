#ifndef ISESSIONCLOCK_H
#define ISESSIONCLOCK_H
#include "domain/core/measurement/Timestamp.h"

namespace domain::ports {
    struct IClock {
        virtual ~IClock() = default;
        virtual common::Timestamp now() const = 0;
    };
}

#endif // ISESSIONCLOCK_H

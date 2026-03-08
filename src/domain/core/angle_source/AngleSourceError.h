#ifndef ANGLESOURCEERROR_H
#define ANGLESOURCEERROR_H
#include <string>
#include "domain/core/common/SourceId.h"

namespace domain::angle {
    struct AngleSourceError {
        common::SourceId id;
        std::string message;
    };
}

#endif //ANGLESOURCEERROR_H
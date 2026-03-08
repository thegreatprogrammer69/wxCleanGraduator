#ifndef MOTORERROR_H
#define MOTORERROR_H

#include <string>

namespace domain::motor {
    struct MotorError {
        std::string message;
        void reset() { message.clear(); }
    };
}

#endif //MOTORERROR_H
#ifndef MOTORLIMITSSTATE_H
#define MOTORLIMITSSTATE_H

namespace domain::motor {
    struct MotorLimitsState {
        bool home{false};
        bool end{false};
        bool operator==(const MotorLimitsState& other) const {
            return home == other.home && end == other.end;
        }
    };
}


#endif //MOTORLIMITSSTATE_H
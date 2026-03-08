#ifndef MOTORFLAPSSTATE_H
#define MOTORFLAPSSTATE_H

namespace domain::motor {
    enum class MotorFlapsState {
        IntakeOpened,
        ExhaustOpened,
        FlapsClosed,
    };
}

#endif //MOTORFLAPSSTATE_H
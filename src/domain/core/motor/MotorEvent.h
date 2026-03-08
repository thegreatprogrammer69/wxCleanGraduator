#ifndef MOTOREVENT_H
#define MOTOREVENT_H

#include <variant>
#include "MotorLimitsState.h"
#include "MotorDirection.h"
#include "MotorError.h"
#include "MotorFlapsState.h"

namespace domain::motor {

    struct MotorEvent {


        struct Started {};
        struct Stopped {};
        struct StoppedAtHome {};
        struct StoppedAtEnd {};

        struct Fault {
            MotorError error;
        };

        struct LimitsChanged {
            MotorLimitsState limits;
        };

        struct DirectionChanged {
            MotorDirection direction;
        };

        struct FlapsStateChanged {
            MotorFlapsState state;
        };

        using Data = std::variant<
            Started,
            Stopped,
            StoppedAtHome,
            StoppedAtEnd,
            Fault,
            LimitsChanged,
            DirectionChanged,
            FlapsStateChanged
        >;

        Data data;

        explicit MotorEvent(Data data) : data(std::move(data)) {}
    };

}

#endif //MOTOREVENT_H
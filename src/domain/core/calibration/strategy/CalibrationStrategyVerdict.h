#ifndef CALIBRATIONVERDICT_H
#define CALIBRATIONVERDICT_H

#include <string>
#include <vector>
#include <variant>

#include "domain/core/calibration/recording/CalibrationSessionId.h"
#include "domain/core/motor/MotorFlapsState.h"
#include "domain/core/motor/MotorDirection.h"

namespace domain::common {

    struct CalibrationStrategyVerdict {

        struct BeginSession {
            calib::CalibrationSessionId id;
        };

        struct EndSession {};

        struct MotorSetFrequency {
            int freq;
        };

        struct MotorSetDirection {
            motor::MotorDirection direction;
        };

        struct MotorSetFlaps {
            motor::MotorFlapsState state;
        };

        struct MotorStart {};
        struct MotorStop {};

        struct Complete {};
        struct Fault { std::string error; };

        using Command = std::variant<
            BeginSession, EndSession,
            MotorSetFrequency, MotorSetDirection,
            MotorSetFlaps, MotorStart, MotorStop,
            Complete, Fault
        >;

        std::vector<Command> commands;
    };

}


#endif //CALIBRATIONVERDICT_H
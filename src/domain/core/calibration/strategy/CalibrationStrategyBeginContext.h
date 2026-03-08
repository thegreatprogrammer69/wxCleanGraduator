#ifndef CALIBRATIONBEGINCONTEXT_H
#define CALIBRATIONBEGINCONTEXT_H
#include "domain/core/calibration/common/CalibrationMode.h"
#include "domain/core/calibration/common/PressurePoints.h"

namespace domain::calib {
    struct CalibrationStrategyBeginContext {
        CalibrationMode calibration_mode;
        PressurePoints pressure_points;
        common::PressureUnit pressure_unit;
    };
}

#endif //CALIBRATIONBEGINCONTEXT_H
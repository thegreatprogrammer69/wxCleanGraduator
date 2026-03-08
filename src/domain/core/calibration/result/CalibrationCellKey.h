#ifndef CALIBRATIONCELLKEY_H
#define CALIBRATIONCELLKEY_H
#include "domain/core/calibration/recording/PointId.h"
#include "domain/core/common/SourceId.h"
#include "domain/core/motor/MotorDirection.h"

namespace domain::calib {
    struct CalibrationCellKey {
        motor::MotorDirection direction;
        PointId point;
        common::SourceId source;
    };
}

#endif //CALIBRATIONCELLKEY_H
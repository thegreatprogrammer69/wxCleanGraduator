#ifndef CALIBRATIONCELLISSUE_H
#define CALIBRATIONCELLISSUE_H
#include <string>

#include "CalibrationIssueSeverity.h"
#include "domain/core/calibration/result/CalibrationCellKey.h"

namespace domain::calib {
    struct CalibrationCellIssue
    {
        CalibrationCellKey cell;

        CalibrationIssueSeverity severity;

        enum class Type {
            MissingSamples,
            TooMuchNoise,
            NonMonotonicAngle,
            PressureOutOfRange
        };

        Type type;
        std::string message;
    };
}

#endif //CALIBRATIONCELLISSUE_H
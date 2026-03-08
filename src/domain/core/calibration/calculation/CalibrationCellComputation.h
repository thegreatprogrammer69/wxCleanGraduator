#ifndef CALIBRATIONCELLCOMPUTATION_H
#define CALIBRATIONCELLCOMPUTATION_H
#include <vector>
#include "domain/core/calibration/analysis/CalibrationCellIssue.h"
#include "domain/core/calibration/result/CalibrationCell.h"

namespace domain::calib {

    struct CalibrationCellComputation
    {
        CalibrationCell cell;
        std::vector<CalibrationCellIssue> issues;
    };

}

#endif //CALIBRATIONCELLCOMPUTATION_H
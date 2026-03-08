#ifndef ICALIBRATIONCALCULATOR_H
#define ICALIBRATIONCALCULATOR_H
#include "domain/core/calibration/calculation/CalibrationCalculatorInput.h"
#include "domain/core/calibration/calculation/CalibrationCellComputation.h"

namespace domain::common {
    class TimeSeries;
}

namespace domain::ports {
    class ICalibrationCalculator {
    public:
        virtual ~ICalibrationCalculator() = default;
        virtual common::CalibrationCellComputation compute(const common::CalibrationCalculatorInput&) const = 0;
    };
}

#endif //ICALIBRATIONCALCULATOR_H
#ifndef CALIBRATIONSESSION_H
#define CALIBRATIONSESSION_H
#include <unordered_map>

#include "CalibrationSessionId.h"
#include "TimeSeries.h"
#include "domain/core/common/SourceId.h"

namespace domain::calib {
    struct CalibrationSession {
        CalibrationSessionId id;
        PressureSeries pressure_series{};
        std::unordered_map<common::SourceId, AngleSeries> angle_series{};
    };
}

#endif //CALIBRATIONSESSION_H
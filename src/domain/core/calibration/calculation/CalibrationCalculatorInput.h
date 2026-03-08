#ifndef CALIBRATIONINPUT_H
#define CALIBRATIONINPUT_H
#include "domain/core/calibration/recording/CalibrationSession.h"

namespace domain::calib {

    struct CalibrationCalculatorInput {
        CalibrationSession calibration_session;
    };

}



#endif //CALIBRATIONINPUT_H
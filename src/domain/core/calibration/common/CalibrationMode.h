#ifndef CALIBRATIONMODE_H
#define CALIBRATIONMODE_H

namespace domain::calib {
    enum class CalibrationMode {
        Full, OnlyForward, OnlyLast
    };
}

#endif //CALIBRATIONMODE_H
#ifndef CALIBRATIONSTRATEGYFEEDCONTEXT_H
#define CALIBRATIONSTRATEGYFEEDCONTEXT_H

namespace domain::calib {
    struct CalibrationStrategyFeedContext {
        float timestamp;
        float pressure;
    };
}

#endif //CALIBRATIONSTRATEGYFEEDCONTEXT_H
#ifndef GAUGEPRECISION_H
#define GAUGEPRECISION_H

namespace domain::calib {
    struct GaugePrecision {
        double value{0.0};
        bool isCorrect() const { return value >= 0.5; }
        bool operator==(const GaugePrecision& rhs) const { return value == rhs.value; }
    };
}

#endif //GAUGEPRECISION_H
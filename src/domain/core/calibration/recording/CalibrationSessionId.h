#ifndef CALIBRATIONSESSIONID_H
#define CALIBRATIONSESSIONID_H
#include <functional>
#include "PointId.h"
#include "domain/core/motor/MotorDirection.h"

namespace domain::calib {
    struct CalibrationSessionId {
        PointId point;
        motor::MotorDirection direction;
        bool operator==(const CalibrationSessionId& rhs) const { return point == rhs.point && direction == rhs.direction; }
    };
}

namespace std {
    template<> struct hash<domain::calib::CalibrationSessionId> {
        size_t operator()(const domain::calib::CalibrationSessionId& s) const noexcept {
            size_t h1 = std::hash<domain::calib::PointId>{}(s.point);
            size_t h2 = std::hash<int>{}(static_cast<int>(s.direction));

            // корректный hash combine (boost-style)
            return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
        }
    };
}

#endif //CALIBRATIONSESSIONID_H
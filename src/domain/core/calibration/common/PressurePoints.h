#ifndef DDPRESSUREPOINTS_H
#define DDPRESSUREPOINTS_H
#include <vector>

#include "domain/core/common/Pressure.h"

namespace domain::calib {
    struct PressurePoints {
        explicit PressurePoints(std::vector<common::Pressure> points)
            : value(std::move(points))
        {}
        PressurePoints() = default;
        std::vector<common::Pressure> value;
        bool isCorrect() const {
            return value.size() > 1;
        }
        std::vector<float> to(common::PressureUnit unit) const {
            std::vector<float> result;
            for (auto p : value) {
                result.push_back(p.to(unit));
            }
            return result;
        }
        bool operator==(const PressurePoints &other) const {  return value == other.value; }
    };
}

#endif //DDPRESSUREPOINTS_H
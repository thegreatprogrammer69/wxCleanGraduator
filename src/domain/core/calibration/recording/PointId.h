#ifndef POINTID_H
#define POINTID_H

#include <functional>

namespace domain::calib {
    struct PointId {
        PointId(const unsigned int id, const float pressure) : id(id), pressure(pressure) {}
        PointId() = default;
        unsigned int id;
        float pressure;
        bool operator==(const PointId& rhs) const { return id == rhs.id; }
    };
}

namespace std {
    template<> struct hash<domain::calib::PointId> {
        size_t operator()(const domain::calib::PointId& p) const noexcept {
            return std::hash<int>{}(static_cast<int>(p.id));
        }
    };
}


#endif //POINTID_H
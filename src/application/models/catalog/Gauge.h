#ifndef CLEANGRADUATOR_GAUGE_H
#define CLEANGRADUATOR_GAUGE_H

#include <string>

namespace application::models {
    struct Gauge {
        std::string name;
        std::vector<float> points;
    };
}

#endif // CLEANGRADUATOR_GAUGE_H

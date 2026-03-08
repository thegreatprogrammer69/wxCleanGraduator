#ifndef WXCLEANGRADUATOR_VIDEOOVERLAYCONFIG_H
#define WXCLEANGRADUATOR_VIDEOOVERLAYCONFIG_H
#include <cstdint>

namespace domain::video_overlay {
    struct Color {
        std::uint8_t r{255};
        std::uint8_t g{0};
        std::uint8_t b{0};
    };

    enum CrosshairForm {
        RING, CROSS
    };

    struct Crosshair {
        bool visible{false};
        CrosshairForm form{RING};
        Color color1{};
        Color color2{};
        float radius{0.25};
    };

    struct Angle {
        bool visible{false};
        Color color{};
        float h{0.02};
        float x{0.01};
        float y{0.01};
    };

    struct Boundary {
        bool visible{false};
        Color color{};
    };

    struct VideoOverlayConfig {
        Crosshair crosshair{};
        Angle angle{};
        Boundary boundary{};
    };
}

#endif //WXCLEANGRADUATOR_VIDEOOVERLAYCONFIG_H
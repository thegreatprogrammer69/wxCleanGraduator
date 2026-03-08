#ifndef PRESSURESOURCEEVENT_H
#define PRESSURESOURCEEVENT_H
#include <variant>
#include "PressureSourceError.h"

namespace domain::pressure {

    struct PressureSourceEvent {

        struct Opened {};

        struct OpenFailed {
            PressureSourceError error;
        };

        struct Failed {
            PressureSourceError error;
        };

        struct Closed {};

        using Data = std::variant<
            Opened,
            OpenFailed,
            Failed,
            Closed
        >;

        Data data;

        explicit PressureSourceEvent(Data data) : data(std::move(data)) {}
    };

}

#endif //PRESSURESOURCEEVENT_H
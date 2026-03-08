#ifndef ANGLESOURCEEVENT_H
#define ANGLESOURCEEVENT_H
#include <variant>
#include "AngleSourceError.h"

namespace domain::angle {

    struct AngleSourceEvent {

        struct Started { common::SourceId id; };
        struct Stopped { common::SourceId id; };
        struct Failed { common::SourceId id; AngleSourceError error; };

        using Data = std::variant<
            Started,
            Stopped,
            Failed
        >;

        Data data;

        explicit AngleSourceEvent(Data data) : data(std::move(data)) {};
    };
}

#endif //ANGLESOURCEEVENT_H
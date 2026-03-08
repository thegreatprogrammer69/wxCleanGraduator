#ifndef IANGLESOURCEOBSERVER_H
#define IANGLESOURCEOBSERVER_H

namespace domain::angle {
    struct AngleSourceEvent;
    struct IAngleSourceObserver {
        virtual ~IAngleSourceObserver() = default;
        virtual void onAngleSourceEvent(const AngleSourceEvent&) = 0;
    };
}

#endif //IANGLESOURCEOBSERVER_H
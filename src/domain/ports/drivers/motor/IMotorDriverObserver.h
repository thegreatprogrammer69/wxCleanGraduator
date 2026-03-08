#ifndef IMOTORDRIVEROBSERVER_H
#define IMOTORDRIVEROBSERVER_H

namespace domain::common {
    struct MotorDriverEvent;
}

namespace domain::ports {
    struct IMotorDriverObserver {
        virtual ~IMotorDriverObserver() = default;
        virtual void onMotorEvent(const common::MotorDriverEvent& event) = 0;
    };
}

#endif //IMOTORDRIVEROBSERVER_H
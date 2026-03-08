#ifndef MOTORFREQUENCY_H
#define MOTORFREQUENCY_H
#include <atomic>
#include <chrono>

namespace domain::motor {
    class MotorFrequency {
    public:
        explicit MotorFrequency(float hz = 0.f) noexcept;

        // --- Copy ctor
        MotorFrequency(const MotorFrequency& other) noexcept;

        // --- Copy assign
        MotorFrequency& operator=(const MotorFrequency& other) noexcept;

        // --- Move ctor
        MotorFrequency(MotorFrequency&& other) noexcept;

        // --- Move assign
        MotorFrequency& operator=(MotorFrequency&& other) noexcept;

        float hz() const noexcept;

        void set(float hz) noexcept;

        bool isValid() const noexcept;

        void clampTo(float max_hz) noexcept;

        std::chrono::steady_clock::duration halfPeriod() const noexcept;

    private:
        std::atomic<float> hz_;
    };
}

#endif //MOTORFREQUENCY_H
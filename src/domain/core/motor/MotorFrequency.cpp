#include "MotorFrequency.h"

using namespace domain::motor;

MotorFrequency::MotorFrequency(float hz) noexcept: hz_(hz) {}

MotorFrequency::MotorFrequency(const MotorFrequency &other) noexcept: hz_(other.hz_.load(std::memory_order_relaxed)) {}

MotorFrequency & MotorFrequency::operator=(const MotorFrequency &other) noexcept {
    if (this != &other) {
        hz_.store(
            other.hz_.load(std::memory_order_relaxed),
            std::memory_order_relaxed
        );
    }
    return *this;
}

MotorFrequency::MotorFrequency(MotorFrequency &&other) noexcept: hz_(other.hz_.load(std::memory_order_relaxed)) {}

MotorFrequency & MotorFrequency::operator=(MotorFrequency &&other) noexcept {
    if (this != &other) {
        hz_.store(
            other.hz_.load(std::memory_order_relaxed),
            std::memory_order_relaxed
        );
    }
    return *this;
}

float MotorFrequency::hz() const noexcept {
    return hz_.load(std::memory_order_relaxed);
}

void MotorFrequency::set(float hz) noexcept {
    hz_.store(hz, std::memory_order_relaxed);
}

bool MotorFrequency::isValid() const noexcept {
    return hz() > 0.99f;
}

void MotorFrequency::clampTo(float max_hz) noexcept {
    float current = hz_.load(std::memory_order_relaxed);

    while (current > max_hz) {
        if (hz_.compare_exchange_weak(current,max_hz)) {
            break;
        }
    }
}

std::chrono::steady_clock::duration MotorFrequency::halfPeriod() const noexcept {
    using namespace std::chrono;

    const float value = hz_.load(std::memory_order_relaxed);

    if (value <= 0.f)
        return steady_clock::duration::zero();

    const double seconds = 1.0 / (2.0 * static_cast<double>(value));

    return duration_cast<steady_clock::duration>(
        duration<double>(seconds)
    );
}

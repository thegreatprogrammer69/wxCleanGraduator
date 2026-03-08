#include "TimeSeries.h"
#include <algorithm>

namespace domain::calib {
    TimeSeries::TimeSeries() = default;
    TimeSeries::~TimeSeries() = default;
    void TimeSeries::clear() { time_.clear(); value_.clear(); }
    bool TimeSeries::empty() const { return time_.empty(); }
    std::size_t TimeSeries::size() const { return time_.size(); }
    const std::vector<float> & TimeSeries::time() const { return time_; }
    const std::vector<float> & TimeSeries::value() const { return value_; }
    void TimeSeries::push(const float time, const float value) { time_.push_back(time); value_.push_back(value); }
} // namespace domain::common

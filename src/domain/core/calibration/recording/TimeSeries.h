#ifndef TIMESERIES_H
#define TIMESERIES_H
#include <vector>

namespace domain::calib {

    class TimeSeries {
    public:
        TimeSeries();
        ~TimeSeries();

        void clear();
        bool empty() const;
        std::size_t size() const;

        const std::vector<float>& time() const;
        const std::vector<float>& value() const;

        void push(float time, float value);

    private:
        std::vector<float> time_;
        std::vector<float> value_;
    };

    struct AngleSeries : TimeSeries {};
    struct PressureSeries : TimeSeries {};

}


#endif //TIMESERIES_H
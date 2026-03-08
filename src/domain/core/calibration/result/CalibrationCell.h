#ifndef CALIBRATIONCELL_H
#define CALIBRATIONCELL_H

namespace domain::calib {
    class CalibrationCell {
    public:
        CalibrationCell() = default;

        void setAngle(float v) { angle_ = v; }
        float angle() const { return angle_; }

    private:
        float angle_ = 0.0f;
    };
}

#endif //CALIBRATIONCELL_H
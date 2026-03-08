#ifndef PRESSUREUNIT_H
#define PRESSUREUNIT_H
#include <string>


namespace domain::common {
    enum class PressureUnit {
        Pa,
        kPa,
        MPa,
        bar,
        atm,
        mmHg,
        mmH2O,
        kgf_cm2,
        kgf_m2
    };
}

std::string to_string(const domain::common::PressureUnit& unit);


#endif //PRESSUREUNIT_H

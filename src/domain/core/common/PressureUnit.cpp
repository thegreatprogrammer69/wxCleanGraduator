#include "PressureUnit.h"

std::string to_string(const domain::common::PressureUnit &unit) {
    using namespace domain::common;
    switch (unit)
    {
        case PressureUnit::Pa:      return "Pa";
        case PressureUnit::kPa:     return "kPa";
        case PressureUnit::MPa:     return "MPa";
        case PressureUnit::bar:     return "bar";
        case PressureUnit::atm:     return "atm";
        case PressureUnit::mmHg:    return "mmHg";
        case PressureUnit::mmH2O:   return "mmH2O";
        case PressureUnit::kgf_cm2: return "kgf/cm²";
        case PressureUnit::kgf_m2:  return "kgf/m²";
    }

    return "unknown";
}

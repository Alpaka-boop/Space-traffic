#ifndef ENGINE_CONSTANTS_H
#define ENGINE_CONSTANTS_H
#include <cmath>

enum ENGINE_TYPES {
    PULSE_CLASS_C_ENGINE,
    PULSE_CLASS_E_ENGINE,
    JUMP_ENGINE
};

namespace ENG_CONST {
    namespace PULSE_C_ENG {
        const long long TEN_LN_START_PACE = 50; // = 10 * log(start pace);
        const long long FUEL_CONSUMPTION = 1000
    }
    namespace PULSE_E_ENG {
        const long long TEN_LN_START_PACE = 20; // = 10 * log(start pace);
        const double SPEED_BOOST_COEF = exp(10);
        const long long FUEL_CONSUMPTION = 2000;
    }
}

#endif ENGINE_CONSTANTS_H

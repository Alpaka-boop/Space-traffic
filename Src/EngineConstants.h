#ifndef ENGINE_CONSTANTS_H
#define ENGINE_CONSTANTS_H
#include <cmath>

namespace ENG_CONST {
    long long epsilon = 10;
    namespace PULSE_C_ENG {
        const long long FUEL_CONSUMPTION = 100;
        const long long FUEL_TO_START = 100;
        const long long SPEED = 100;
    }
    namespace PULSE_E_ENG {
        const long long FUEL_TO_START = 100;
        const long long FUEL_CONSUMPTION = 500;
    }
    const long long JUMP_ENG_AVG_SPEED = 100;
    namespace JUMP_ALPHA_ENG {
        const long long FUEL_TO_START = 0;
        const long long FUEL_CONSUMPTION = 1000;
        const long long MAX_JUMP_LENGTH = 1000;
    }
    namespace JUMP_OMEGA_ENG {
        const long long FUEL_TO_START = 0;
        const long long FUEL_CONSUMPTION = 2000;
        const long long MAX_JUMP_LENGTH = 100000;
    }
    namespace JUMP_GAMMA_ENG {
        const long long FUEL_TO_START = 0;
        const long long FUEL_CONSUMPTION = 3000;
        const long long MAX_JUMP_LENGTH = LONG_MAX;
    }
}

#endif // ENGINE_CONSTANTS_H

#ifndef DEFLECTOR_CONSTANTS_H
#define DEFLECTOR_CONSTANTS_H

#include <cinttypes>

namespace DEFL_DMG_CONST {
    namespace CLASS1 {
        uint8_t AST_MAX_N = 2;
        uint8_t MET_MAX_N = 1;
    }
    namespace CLASS2 {
        uint8_t AST_MAX_N = 10;
        uint8_t MET_MAX_N = 3;
    }
    namespace CLASS3 {
        uint8_t AST_MAX_N = 40;
        uint8_t MET_MAX_N = 10;
        uint8_t CSMKIT_MAX_N = 1;
    }
    namespace PHOTONIC {
        uint8_t ANTIMAT_MAX_N = 3;
    }
}

enum WEIGHT_CLASS {
    LOW_WEIGHT_CLASS = 1,
    MIDDLE_WEIGHT_CLASS,
    HIGH_WEIGHT_CLASS
};

#endif DEFLECTOR_CONSTANTS_H

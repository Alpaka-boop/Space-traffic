#ifndef SHIP_CONSTANTS_H
#define SHIP_CONSTANTS_H

#include <cinttypes>

const int8_t SHIP_FULL_HEALTH_PERCENT = 100;

enum CASE_CLASS {
    FIRST_CLASS_CASE = 1,   // 1  asteroid  / 0 meteorites
    SECOND_CLASS_CASE,      // 5  asteroids / 2 meteorites
    THIRD_CLASS_CASE        // 20 asteroids / 5 meteorites
};

namespace DMG_CONST {
    namespace PLSR_SHIP {
      uint8_t AST_MAX_N = 1;
      uint8_t MET_MAX_N = 0;
    }
    namespace VAL_SHIP {
      uint8_t AST_MAX_N = 5;
      uint8_t MET_MAX_N = 2;
    }
    namespace MER_SHIP {
      uint8_t AST_MAX_N = 5;
      uint8_t MET_MAX_N = 2;
    }
    namespace STEL_SHIP {
      uint8_t AST_MAX_N = 1;
      uint8_t MET_MAX_N = 0;
    }
    namespace AVG_SHIP {
      uint8_t AST_MAX_N = 20;
      uint8_t MET_MAX_N = 5;
    }

}

enum WEIGHT_CLASS {
    LOW_WEIGHT_CLASS = 1,
    MIDDLE_WEIGHT_CLASS,
    HIGH_WEIGHT_CLASS
};

#endif //SHIP_CONSTANTS_H

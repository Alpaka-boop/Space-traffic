#ifndef DIFFICULTIES_H
#define DIFFICULTIES_H
#include <cinttypes>

namespace DAMAGE_BITS {
    uint16_t METEORITE = 0b0000000011100000;
    uint16_t ASTEROID = 0b0000000000011111;
    uint16_t ANTI_MATTER = 0b0000000100000000;
    uint16_t COSMO_KIT = 0000001000000000;
}

class Difficulties {

};

class Meteorite: public Difficulties {

};

class Asteroid: public Difficulties {

};

class AntiMatterFlash: public Difficulties {

};

class CosmoKit: public Difficulties {

};

#endif //DIFFICULTIES_H

#ifndef DIFFICULTIES_H
#define DIFFICULTIES_H

#include <cinttypes>

class Difficulties {
    int aster_num = 0;
    int meteor_num = 0;
    int anti_matter_num = 0;
    int cosmo_kit_num = 0;

    friend class Ship;
    friend class Deflector;

public:
    Difficulties(int aster_num, int meteor_num, int anti_matter_num, int cosmo_kit_num)
    : aster_num(aster_num), meteor_num(meteor_num), anti_matter_num(anti_matter_num), cosmo_kit_num(cosmo_kit_num) {}
};

#endif // DIFFICULTIES_H

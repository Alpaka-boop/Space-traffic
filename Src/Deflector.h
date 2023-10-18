#ifndef DEFLECTOR_H
#define DEFLECTOR_H

#include "Damage.h"
#include "Difficulties.h"
#include "DeflectorConstants.h"

class Deflector {
    virtual bool AsteroidProtect(int aster_num) = 0;
    virtual bool MeteoriteProtect(int meteor_num) = 0;

    bool CosmoKitDamageProtect(int cosmo_kit_num) {
        if (!is_damaged) {
            is_damaged = true;
            return true;
        }
        return false;
    }

    bool AntiMatterProtect(int anti_matter_num) {
        if (is_photonic && !is_damaged) {
            damage.anti_matter_num += anti_matter_num;
            if (damage.anti_matter_num <= DEFL_DMG_CONST::PHOTONIC::ANTIMAT_MAX_N) {
                return  true;
            }
            is_photonic = false;
        }
        return false;
    }

protected:
    Damage damage;
    bool is_damaged = false;

public:
    bool is_photonic = false;

    Deflector(bool is_photonic): is_photonic(is_photonic) {}

    bool Protect(const Difficulties& difficulties) {
        return AsteroidProtect(difficulties.aster_num)
            & MeteoriteProtect(difficulties.meteor_num)
            & AntiMatterProtect(difficulties.anti_matter_num)
            & CosmoKitDamageProtect(difficulties.cosmo_kit_num);
    }
};

class Class1: private Deflector {
public:
    Class1(bool is_photonic): Deflector(is_photonic) {}

    bool AsteroidProtect(int aster_num) override {
        if (!is_damaged) {
            damage.aster_num += aster_num;
            if (damage.aster_num <= DEFL_DMG_CONST::CLASS1::AST_MAX_N) {
                return true;
            }
            is_damaged = true;
        }
        return false;
    }

    bool MeteoriteProtect(int meteor_num) override {
        if (!is_damaged) {
            damage.meteor_num += meteor_num;
            if (damage.meteor_num <= DEFL_DMG_CONST::CLASS1::AST_MAX_N) {
                return true;
            }
            is_damaged = true;
        }
        return false;
    }
};

class Class2: private Deflector {
public:
    Class2(bool is_photonic): Deflector(is_photonic) {}

    bool AsteroidProtect(int aster_num) override {
        if (!is_damaged) {
            damage.aster_num += aster_num;
            if (damage.aster_num <= DEFL_DMG_CONST::CLASS2::AST_MAX_N) {
                return true;
            }
            is_damaged = true;
        }
        return false;
    }

    bool MeteoriteProtect(int meteor_num) override {
        if (!is_damaged) {
            damage.meteor_num += meteor_num;
            if (damage.meteor_num <= DEFL_DMG_CONST::CLASS2::AST_MAX_N) {
                return true;
            }
            is_damaged = true;
        }
        return false;
    }
};

class Class3: private Deflector {
public:
    Class3(bool is_photonic): Deflector(is_photonic) {}
    bool AsteroidProtect(int aster_num) override {
        if (!is_damaged) {
            damage.aster_num += aster_num;
            if (damage.aster_num <= DEFL_DMG_CONST::CLASS3::AST_MAX_N) {
                return true;
            }
            is_damaged = true;
        }
        return false;
    }

    bool MeteoriteProtect(int meteor_num) override {
        if (!is_damaged) {
            damage.meteor_num += meteor_num;
            if (damage.meteor_num <= DEFL_DMG_CONST::CLASS3::AST_MAX_N) {
                return true;
            }
            is_damaged = true;
        }
        return false;
    }
};

#endif DEFLECTOR_H

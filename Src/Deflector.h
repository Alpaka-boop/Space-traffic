#ifndef DEFLECTOR_H
#define DEFLECTOR_H

#include "Damage.h"
#include "Difficulties.h"
#include "DeflectorConstants.h"

class Deflector {
    virtual bool AsteroidProtect(int& aster_num) = 0;
    virtual bool MeteoriteProtect(int& meteor_num) = 0;
    virtual bool CosmoKitDamageProtect(int& cosmo_kit_num) = 0;

    bool AntiMatterProtect(int& anti_matter_num) {
        if (anti_matter_num == 0) {
            return true;
        }
        if (is_photonic && !is_damaged) {
            if (DEFL_DMG_CONST::PHOTONIC::ANTIMAT_MAX_N - damage.anti_matter_num >= anti_matter_num) {
                damage.anti_matter_num += anti_matter_num;
                anti_matter_num = 0;
                return true;
            }
            anti_matter_num -= (DEFL_DMG_CONST::PHOTONIC::ANTIMAT_MAX_N - damage.anti_matter_num);
            damage.anti_matter_num = DEFL_DMG_CONST::PHOTONIC::ANTIMAT_MAX_N;
        }
        return false;
    }

protected:
    Damage damage;
    bool is_damaged = false;

public:
    bool is_photonic = false;

    explicit Deflector(bool is_photonic): is_photonic(is_photonic) {}

    bool isBroken() const {
        return is_damaged;
    }

    bool Protect(Difficulties& difficulties) {
        return AsteroidProtect(difficulties.aster_num)
            && MeteoriteProtect(difficulties.meteor_num)
            && AntiMatterProtect(difficulties.anti_matter_num)
            && CosmoKitDamageProtect(difficulties.cosmo_kit_num);
    }
};

class NoDefl: public Deflector {
public:
    NoDefl(): Deflector(false) {}

    bool AsteroidProtect(int& aster_num) override {
        if (aster_num > 0) {
            return false;
        }
        return true;
    }

    bool MeteoriteProtect(int& meteor_num) override {
        if (meteor_num > 0) {
            return false;
        }
        return true;
    }

    bool CosmoKitDamageProtect(int& cosmo_kit_num) override {
        if (cosmo_kit_num > 0) {
            return false;
        }
        return true;
    }
};

class Class1Defl: public Deflector {
public:
    explicit Class1Defl(bool is_photonic): Deflector(is_photonic) {}

    bool AsteroidProtect(int& aster_num) override {
        if (!is_damaged) {
            if (DEFL_DMG_CONST::CLASS1::AST_MAX_N - damage.aster_num >= aster_num) {
                damage.aster_num += aster_num;
                aster_num = 0;
                if (damage.aster_num == DEFL_DMG_CONST::CLASS1::AST_MAX_N) {
                    is_damaged = true;
                }
                return true;
            }
            aster_num -= (DEFL_DMG_CONST::CLASS1::AST_MAX_N - damage.aster_num);
            damage.aster_num = DEFL_DMG_CONST::CLASS1::AST_MAX_N;
        }
        is_damaged = true;
        return false;
    }

    bool MeteoriteProtect(int& meteor_num) override {
        if (!is_damaged) {
            if (DEFL_DMG_CONST::CLASS1::MET_MAX_N - damage.meteor_num >= meteor_num) {
                damage.meteor_num += meteor_num;
                meteor_num = 0;
                if (damage.meteor_num == DEFL_DMG_CONST::CLASS1::MET_MAX_N) {
                    is_damaged = true;
                }
                return true;
            }
            meteor_num -= (DEFL_DMG_CONST::CLASS1::MET_MAX_N - damage.meteor_num);
            damage.meteor_num = DEFL_DMG_CONST::CLASS1::MET_MAX_N;
        }
        is_damaged = true;
        return false;
    }

    bool CosmoKitDamageProtect(int& cosmo_kit_num) override {
        if (cosmo_kit_num > 0) {
            is_damaged = true;
            return false;
        }
        return true;
    }
};

class Class2Defl: public Deflector {
public:
    explicit Class2Defl(bool is_photonic): Deflector(is_photonic) {}

    bool AsteroidProtect(int& aster_num) override {
        if (!is_damaged) {
            if (DEFL_DMG_CONST::CLASS2::AST_MAX_N - damage.aster_num >= aster_num) {
                damage.aster_num += aster_num;
                aster_num = 0;
                if (damage.aster_num == DEFL_DMG_CONST::CLASS2::AST_MAX_N) {
                    is_damaged = true;
                }
                return true;
            }
            aster_num -= (DEFL_DMG_CONST::CLASS2::AST_MAX_N - damage.aster_num);
            damage.aster_num = DEFL_DMG_CONST::CLASS2::AST_MAX_N;
        }
        is_damaged = true;
        return false;
    }

    bool MeteoriteProtect(int& meteor_num) override {
        if (!is_damaged) {
            if (DEFL_DMG_CONST::CLASS2::MET_MAX_N - damage.meteor_num >= meteor_num) {
                damage.meteor_num += meteor_num;
                meteor_num = 0;
                if (damage.meteor_num == DEFL_DMG_CONST::CLASS2::MET_MAX_N) {
                    is_damaged = true;
                }
                return true;
            }
            meteor_num -= (DEFL_DMG_CONST::CLASS2::MET_MAX_N - damage.meteor_num);
            damage.meteor_num = DEFL_DMG_CONST::CLASS2::MET_MAX_N;
        }
        is_damaged = true;
        return false;
    }

    bool CosmoKitDamageProtect(int& cosmo_kit_num) override {
        if (cosmo_kit_num > 0) {
            is_damaged = true;
            return false;
        }
        return true;
    }
};

class Class3Defl: public Deflector {
public:
    explicit Class3Defl(bool is_photonic): Deflector(is_photonic) {}

    bool AsteroidProtect(int& aster_num) override {
        if (!is_damaged) {
            if (DEFL_DMG_CONST::CLASS3::AST_MAX_N - damage.aster_num >= aster_num) {
                damage.aster_num += aster_num;
                aster_num = 0;
                if (damage.aster_num == DEFL_DMG_CONST::CLASS3::AST_MAX_N) {
                    is_damaged = true;
                }
                return true;
            }
            aster_num -= (DEFL_DMG_CONST::CLASS3::AST_MAX_N - damage.aster_num);
            damage.aster_num = DEFL_DMG_CONST::CLASS3::AST_MAX_N;
        }
        is_damaged = true;
        return false;
    }

    bool MeteoriteProtect(int& meteor_num) override {
        if (!is_damaged) {
            if (DEFL_DMG_CONST::CLASS3::MET_MAX_N - damage.meteor_num >= meteor_num) {
                damage.meteor_num += meteor_num;
                meteor_num = 0;
                if (damage.meteor_num == DEFL_DMG_CONST::CLASS3::MET_MAX_N) {
                    is_damaged = true;
                }
                return true;
            }
            meteor_num -= (DEFL_DMG_CONST::CLASS3::MET_MAX_N - damage.meteor_num);
            damage.meteor_num = DEFL_DMG_CONST::CLASS3::MET_MAX_N;
        }
        is_damaged = true;
        return false;
    }

    bool CosmoKitDamageProtect(int& cosmo_kit_num) override {
        if (!is_damaged) {
            if (DEFL_DMG_CONST::CLASS3::KIT_MAX_N - damage.cosmo_kit_num >= cosmo_kit_num) {
                damage.cosmo_kit_num += cosmo_kit_num;
                cosmo_kit_num = 0;
                if (damage.cosmo_kit_num == DEFL_DMG_CONST::CLASS3::KIT_MAX_N) {
                    is_damaged = true;
                }
                return true;
            }
            cosmo_kit_num -= (DEFL_DMG_CONST::CLASS3::KIT_MAX_N - damage.cosmo_kit_num);
            damage.cosmo_kit_num = DEFL_DMG_CONST::CLASS3::KIT_MAX_N;
        }
        is_damaged = true;
        return false;
    }
};

#endif // DEFLECTOR_H

#ifndef SHIP_H
#define SHIP_H

#include <memory>
#include <vector>

#include "Deflector.h"
#include "Engine.h"
#include "ShipConstants.h"
#include "Difficulties.h"
#include "Result.h"
#include "Conditions.h"
#include "Market.h"
#include "Damage.h"
#include "IsType.h"

class Ship {
public:
    using DEFL = std::shared_ptr<Deflector>;
    using ENG = std::shared_ptr<Engine>;
private:
    using AntiNitrAmitter = bool;

    bool is_lost = false;
    bool is_alive_team = true;
    bool is_broken_ship = false;
    const DEFL deflector;
    const AntiNitrAmitter anti_nitr_amitter = true;

public:
    virtual void getMeteoriteDamage(int meteor_num) = 0;
    virtual void getAsteroidDamage(int aster_num) = 0;
    virtual void getAntiMatterFlashDamage(int anti_matter_num) = 0;

    virtual long long calculateFuelConsumption(const Conditions& conditions) = 0;
    virtual long long calculateTimeTravel(const RouteEnvDistance& distance) = 0;

    virtual bool IsAbleToComplete(const Environment& environment) = 0;

    Ship(DEFL&& deflector, AntiNitrAmitter anti_nitr_amitter)
            : deflector(std::forward<DEFL>(deflector)), anti_nitr_amitter(anti_nitr_amitter) {}

    Result Navigate(Conditions& conditions) {
        is_lost = !IsAbleToComplete(conditions.environment);
        getDamage(conditions.difficulties);
        Result result(is_alive_team, is_broken_ship, is_lost);

        if (!result.is_broken_ship && result.is_alive_team && !result.is_lost) {
            result.spent_fuel = calculateFuelConsumption(conditions);
            result.total_price = result.spent_fuel * conditions.market->getFuelPrice();
            result.route_time = calculateTimeTravel(conditions.distance);
        }

        return result;
    }

protected:
    Damage damage = {};

    void killTeam() {
        is_alive_team = false;
    }

    void killShip() {
        killTeam();
        is_broken_ship = true;
    }

private:
    void getDamage(Difficulties& difficulties) {
        if (!deflector->is_photonic && difficulties.anti_matter_num > 0) {
            killTeam();
        }
        int cosmo_kit_num = difficulties.cosmo_kit_num;
        if (anti_nitr_amitter) {
            difficulties.cosmo_kit_num = 0;
        }
        if (!deflector->Protect(difficulties)) {
            getAsteroidDamage(difficulties.aster_num);
            getMeteoriteDamage(difficulties.meteor_num);
            getCosmoKitDamage(difficulties.cosmo_kit_num);
            getAntiMatterFlashDamage(difficulties.anti_matter_num);
        }
    }

    void getCosmoKitDamage(int cosmo_kit_num) {
        if (cosmo_kit_num > 0) {
            killShip();
        }
    }
};

class PleasureShuttle: public Ship {
    const ENG engine;                                   // Impulse class C engine
    const int8_t case_class = FIRST_CLASS_CASE;         // 1 asteroid / 0 meteorites
    const int8_t weight_class = LOW_WEIGHT_CLASS;       // little and light

public:
    PleasureShuttle(): Ship(std::make_shared<NoDefl>(), AMITTER::FALSE)
                    , engine(std::make_shared<PulseClassCEngine>()) {}

private:
    long long calculateFuelConsumption(const Conditions& conditions) override {
        auto full_distance = conditions.distance.ordinary_space_length
                                    + conditions.distance.nitrine_nebulae_length;
        return engine->calculateFuelConsumption(full_distance);
    }

    long long calculateTimeTravel(const RouteEnvDistance& distance) override {
        return engine->calculateTimeTravel(distance.getSum());
    }

    void getMeteoriteDamage(int meteor_num) override {
        killShip();
    }

    void getAsteroidDamage(int aster_num) override {
        damage.aster_num += aster_num;
        if (damage.aster_num > DMG_CONST::PLSR_SHIP::AST_MAX_N) {
            killShip();
        }
    }

    void getAntiMatterFlashDamage(int anti_matter_num) override {
        killTeam();
    }

    bool IsAbleToComplete(const Environment &environment) override {
        try {
            dynamic_cast<const FreeSpace&>(environment);
        } catch (std::bad_cast) {
            return false;
        }
        return  true;
    }
};

class Vaclas: public Ship {
    struct Vaclas_Engines {
        ENG impulse_eng;
        ENG jump_eng;
    } engines;
    const int8_t case_class = SECOND_CLASS_CASE;         // 5  asteroids / 2 meteorites
    const int8_t weight_class = MIDDLE_WEIGHT_CLASS;     // middle weight, middle height

public:
    explicit Vaclas(bool is_photonic = false): Ship(std::make_shared<Class1>(is_photonic), AMITTER::FALSE)
                                , engines({std::make_shared<PulseClassEEngine>(), std::make_shared<GammaJumpEng>()}) {}
private:
    long long calculateFuelConsumption(const Conditions& conditions) override {
        auto dist_using_imp_eng = conditions.distance.ordinary_space_length
                                        + conditions.distance.nitrine_nebulae_length;
        auto dist_using_jump_eng = conditions.distance.spatial_channels_length;
        return engines.impulse_eng->calculateFuelConsumption(dist_using_imp_eng)
               + engines.jump_eng->calculateFuelConsumption(dist_using_jump_eng);
    }

    long long calculateTimeTravel(const RouteEnvDistance& distance) override {
        auto dist_using_imp_eng = distance.ordinary_space_length + distance.nitrine_nebulae_length;
        auto dist_using_jump_eng = distance.spatial_channels_length;
        return engines.impulse_eng->calculateTimeTravel(dist_using_imp_eng)
            + engines.jump_eng->calculateTimeTravel(dist_using_jump_eng);
    }

    void getMeteoriteDamage(int meteor_num) override {
        damage.meteor_num += meteor_num;
        if (damage.meteor_num > DMG_CONST::VAL_SHIP::MET_MAX_N) {
            killShip();
        }
    }

    void getAsteroidDamage(int aster_num) override {
        damage.aster_num += aster_num;
        if (damage.aster_num > DMG_CONST::VAL_SHIP::AST_MAX_N) {
            killShip();
        }
    }

    void getAntiMatterFlashDamage(int anti_matter_num) override {
        killTeam();
    }

    bool IsAbleToComplete(const Environment &environment) override {
        return true;
    }
};

class Meredian: public Ship {
    const ENG engine;                                    // Class E impulse engine
    const int8_t case_class = SECOND_CLASS_CASE;         // 5  asteroids / 2 meteorites
    const int8_t weight_class = MIDDLE_WEIGHT_CLASS;     // middle weight, middle height

public:
    explicit Meredian(bool is_photonic = false): Ship(std::make_shared<Class2>(is_photonic)
                                    , AMITTER::TRUE), engine(std::make_shared<PulseClassEEngine>()) {}
private:
    long long calculateFuelConsumption(const Conditions& conditions) override {
        auto full_distance = conditions.distance.ordinary_space_length
                            + conditions.distance.nitrine_nebulae_length;
        return engine->calculateFuelConsumption(full_distance);
    }

    long long calculateTimeTravel(const RouteEnvDistance& distance) override {
        return engine->calculateTimeTravel(distance.getSum());
    }

    void getMeteoriteDamage(int meteor_num) override {
        damage.meteor_num += meteor_num;
        if (damage.meteor_num > DMG_CONST::MER_SHIP::MET_MAX_N) {
            killShip();
        }
    }

    void getAsteroidDamage(int aster_num) override {
        damage.aster_num += aster_num;
        if (damage.aster_num > DMG_CONST::MER_SHIP::AST_MAX_N) {
            killShip();
        }
    }

    void getAntiMatterFlashDamage(int anti_matter_num) override {
        killTeam();
    }

    bool IsAbleToComplete(const Environment &environment) override {
        try {
            dynamic_cast<const DensitySpace&>(environment);
        } catch (std::bad_cast) {
            return true;
        }
        return false;
    }
};

class Stella: public Ship {
    struct Stella_Engines {
        ENG impulse_eng;
        ENG jump_eng;
    } engines;
    const int8_t case_class = FIRST_CLASS_CASE;          // 1  asteroid  / 0 meteorites
    const int8_t weight_class = LOW_WEIGHT_CLASS;        // middle weight, middle height

public:
    explicit Stella(bool is_photonic = false): Ship(std::make_shared<Class1>(is_photonic), AMITTER::FALSE)
            , engines({std::make_shared<PulseClassCEngine>(), std::make_shared<OmegaJumpEng>()}) {}
private:
    long long calculateFuelConsumption(const Conditions& conditions) override {
        auto dist_using_imp_eng = conditions.distance.ordinary_space_length
                                        + conditions.distance.nitrine_nebulae_length;
        auto dist_using_jump_eng = conditions.distance.spatial_channels_length;
        return engines.impulse_eng->calculateFuelConsumption(dist_using_imp_eng)
               + engines.jump_eng->calculateFuelConsumption(dist_using_jump_eng);
    }

    long long calculateTimeTravel(const RouteEnvDistance& distance) override {
        auto dist_using_imp_eng = distance.ordinary_space_length + distance.nitrine_nebulae_length;
        auto dist_using_jump_eng = distance.spatial_channels_length;
        return engines.impulse_eng->calculateTimeTravel(dist_using_imp_eng)
            + engines.jump_eng->calculateTimeTravel(dist_using_jump_eng);
    }

    void getMeteoriteDamage(int meteor_num) override {
        killShip();
    }

    void getAsteroidDamage(int aster_num) override {
        damage.aster_num += aster_num;
        if (damage.aster_num > DMG_CONST::STEL_SHIP::AST_MAX_N) {
            killShip();
        }
    }

    void getAntiMatterFlashDamage(int anti_matter_num) override {
        killTeam();
    }

    bool IsAbleToComplete(const Environment &environment) override {
        try {
            dynamic_cast<const NitrineSpace&>(environment);
        } catch (std::bad_cast) {
            return true;
        }
        return false;
    }
};

class Avgur: public Ship {
    struct Avgur_Engines {
        ENG impulse_eng;
        ENG jump_eng;
    } engines;
    const int8_t case_class = THIRD_CLASS_CASE;          // 20 asteroids / 5 meteorites
    const int8_t weight_class = HIGH_WEIGHT_CLASS;       // middle weight, middle height

public:
    explicit Avgur(bool is_photonic = false): Ship(std::make_shared<Class3>(is_photonic), AMITTER::FALSE)
                                , engines({std::make_shared<PulseClassEEngine>(), std::make_shared<AlphaJumpEng>()}) {}
private:
    long long calculateFuelConsumption(const Conditions& conditions) override {
        auto dist_using_imp_eng = conditions.distance.ordinary_space_length
                                  + conditions.distance.nitrine_nebulae_length;
        auto dist_using_jump_eng = conditions.distance.spatial_channels_length;
        return engines.impulse_eng->calculateFuelConsumption(dist_using_imp_eng)
               + engines.jump_eng->calculateFuelConsumption(dist_using_jump_eng);
    }

    long long calculateTimeTravel(const RouteEnvDistance& distance) override {
        auto dist_using_imp_eng = distance.ordinary_space_length + distance.nitrine_nebulae_length;
        auto dist_using_jump_eng = distance.spatial_channels_length;
        return engines.impulse_eng->calculateTimeTravel(dist_using_imp_eng)
               + engines.jump_eng->calculateTimeTravel(dist_using_jump_eng);
    }

    void getMeteoriteDamage(int meteor_num) override {
        damage.meteor_num += meteor_num;
        if (damage.meteor_num > DMG_CONST::AVG_SHIP::MET_MAX_N) {
            killShip();
        }
    }

    void getAsteroidDamage(int aster_num) override {
        damage.aster_num += aster_num;
        if (damage.aster_num > DMG_CONST::AVG_SHIP::AST_MAX_N) {
            killShip();
        }
    }

    void getAntiMatterFlashDamage(int anti_matter_num) override {
        killTeam();
    }

    bool IsAbleToComplete(const Environment &environment) override {
        return true;
    }
};

#endif // SHIP_H
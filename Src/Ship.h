#ifndef SHIP_H
#define SHIP_H

#include <memory>
#include <vector>

#include "Deflector.h"
#include "Engine.h"
#include "ShipConstants.h"
#include "Difficulties.h"
#include "GetDamage.cpp"
#include "Result.h"
#include "Conditions.h"
#include "Market.h"
#include "Damage.h"

// TODO move constructors =>
// TODO engine = 0, deflector = 0  null the fields
// TODO navigation for other ships (look for pleasure ship example)

class Ship {
    using DEFL = std::shared_ptr<Deflector>;

    int8_t health = DMG_CONST::SHIP_FULL_HEALTH_PERCENT;
    bool is_alive_team = true;
    bool is_broken_ship = false;
    const DEFL deflector;

public:
    using ENG = std::shared_ptr<Engine>;

    virtual void getMeteoriteDamage(int meteor_num) = 0;
    virtual void getAsteroidDamage(int aster_num) = 0;
    virtual void getAntiMatterFlashDamage(int anti_matter_num) = 0;
    virtual void getCosmoKitDamage(int cosmo_kit_num) = 0;

    virtual long long calculateFuelConsumption(const Conditions& conditions) = 0;
    virtual long long calculateTimeTravel(const RouteEnvDistance& distance) = 0;

    Ship(const DEFL deflector): deflector(deflector) {}

    Result Navigate(const Conditions& conditions) {
        getDamage(conditions.difficulties);
        Result result(is_alive_team, is_broken_ship);

        if (!result.is_broken_ship && result.is_alive_team) {
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
        health = 0;
        killTeam();
        is_broken_ship = true;
    }

private:
    void getDamage(const Difficulties& difficulties) {
        if (!deflector->is_photonic && difficulties.anti_matter_num > 0) {
            killTeam();
        }
        if (!deflector->Protect(difficulties)) {
            getAsteroidDamage(difficulties.aster_num);
            getMeteoriteDamage(difficulties.meteor_num);
            getCosmoKitDamage(difficulties.cosmo_kit_num);
        }
    }
};

class PleasureShuttle: private Ship {
    const ENG engine;                                   // Impulse class C engine
    const int8_t case_class = FIRST_CLASS_CASE;         // 1 asteroid / 0 meteorites
    const int8_t weight_class = LOW_WEIGHT_CLASS;       // little and light

public:
    PleasureShuttle(std::shared_ptr<Engine>&& engine, std::shared_ptr<Deflector>&& deflector)
            : engine(engine), Ship(deflector) {
    }

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

    void getCosmoKitDamage(int cosmo_kit_num) override {
        killShip();
    }
};

class Vaclas: Ship {
    struct Vaclas_Engines {
        ENG impulse_eng;
        ENG jump_eng;
    } engines;
    const int8_t case_class = SECOND_CLASS_CASE;         // 5  asteroids / 2 meteorites
    const int8_t weight_class = MIDDLE_WEIGHT_CLASS;     // middle weight, middle height

public:
    Vaclas(std::vector<const std::shared_ptr<Engine>>&& engines
            , std::shared_ptr<Deflector>&& deflector): Ship(deflector) {
        this->engines.impulse_eng = std::move(engines[0]);
        this->engines.jump_eng = std::move(engines[1]);
    }
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

    void getCosmoKitDamage(int cosmo_kit_num) override {
        killShip();
    }
};

class Meredian: Ship {
    using AntiNitrAmitter = bool; // TODO

    const ENG engine;                                    // Class E impulse engine
    const int8_t case_class = SECOND_CLASS_CASE;         // 5  asteroids / 2 meteorites
    const int8_t weight_class = MIDDLE_WEIGHT_CLASS;     // middle weight, middle height
    const AntiNitrAmitter anti_nitr_amitter = true; // TODO

public:
    Meredian(const std::shared_ptr<Engine>& engine, const std::shared_ptr<Deflector>& deflector)
            : engine(engine), Ship(deflector) {}
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

    void getCosmoKitDamage(int cosmo_kit_num) override {
        return; // TODO when we there deflectors already have been defeated but should not be
    }
};

class Stella: Ship {
    struct Stella_Engines {
        ENG impulse_eng;
        ENG jump_eng;
    } engines;
    const int8_t case_class = FIRST_CLASS_CASE;          // 1  asteroid  / 0 meteorites
    const int8_t weight_class = LOW_WEIGHT_CLASS;        // middle weight, middle height

public:
    Stella(const std::vector<const std::shared_ptr<Engine>>& engines
            , const std::shared_ptr<Deflector>& deflector): Ship(deflector) {
        this->engines.impulse_eng = std::move(engines[0]);
        this->engines.jump_eng = std::move(engines[1]);
    }
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

    void getCosmoKitDamage(int cosmo_kit_num) override {
        killShip();
    }
};

class Avgur: Ship {
    struct Avgur_Engines {
        ENG impulse_eng;
        ENG jump_eng;
    } engines;
    const int8_t case_class = THIRD_CLASS_CASE;          // 20 asteroids / 5 meteorites
    const int8_t weight_class = HIGH_WEIGHT_CLASS;       // middle weight, middle height

public:
    Avgur(const std::vector<const std::shared_ptr<Engine>>& engines
            , const std::shared_ptr<Deflector>& deflector): Ship(deflector) {
        this->engines.impulse_eng = std::move(engines[0]);
        this->engines.jump_eng = std::move(engines[1]);
    }
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

    void getCosmoKitDamage(int cosmo_kit_num) override {
        killShip();
    }
};

#endif

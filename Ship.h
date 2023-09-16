#include <memory>
#include <vector>

#include "Deflector.h"
#include "Engine.h"
#include "ShipConstants.h"
#include "Difficulties.h"
#include "GetDamage.cpp"

class Ship {
    int8_t health = SHIP_FULL_HEALTH_PERCENT;
    uint16_t damage = 0;
    bool is_alive = true;
  public:
    using ENG = std::shared_ptr<Engine>;
    using DEFL = std::shared_ptr<Deflector>;

    virtual bool getMeteoriteDamage() = 0;       // returns is_alive
    virtual bool getAsteroidDamage() = 0;        // returns is_alive
    virtual bool getAntiMatterFlashDamage() = 0; // returns is_alive
    virtual bool getCosmoKitDamage() = 0;        // returns is_alive

    bool die() {
        health = 0;
        is_alive = false;
        return is_alive;
    }
};

class PleasureShuttle: public Ship {
    const ENG engine;                                   // Impulse class C engine
    const DEFL deflector;                               // No deflectors
    const int8_t case_class = FIRST_CLASS_CASE;         // 1 asteroid / 0 meteorites
    const int8_t weight_class = LOW_WEIGHT_CLASS;       // little and light

  public:
    PleasureShuttle(const std::shared_ptr<Engine>& engine, const std::shared_ptr<Deflector>& deflector)
            : engine(engine), deflector(deflector) {}

    bool getMeteoriteDamage() override {
        return die();
    }

    bool getAsteroidDamage() override {
        return die();
    }

    bool getAntiMatterFlashDamage() override {
        return die();
    }

    bool getCosmoKitDamage() override {
        return die();
    }


};

class Vaclas: Ship {
    std::vector<const ENG> engine;                       // Class E impulse engine and gamma class jump engine
    const DEFL deflector;                                // Second class deflectors
    const int8_t case_class = SECOND_CLASS_CASE;         // 5  asteroids / 2 meteorites
    const int8_t weight_class = MIDDLE_WEIGHT_CLASS;     // middle weight, middle height

  public:
    Vaclas(const std::vector<const std::shared_ptr<Engine>>& engines
            , const std::shared_ptr<Deflector>& deflector): deflector(deflector) {
        for (const auto& eng : engines) {
            engine.emplace_back(eng);
        }
    }

    bool getMeteoriteDamage() override {

    }
};

class Meredian: Ship {
    const ENG engine;                                    // Class E impulse engine
    const DEFL deflector;                                // Second class deflectors
    const int8_t case_class = SECOND_CLASS_CASE;         // 5  asteroids / 2 meteorites
    const int8_t weight_class = MIDDLE_WEIGHT_CLASS;     // middle weight, middle height
    //TODO anti-nitrine emmiter

  public:
    Meredian(const std::shared_ptr<Engine>& engine, const std::shared_ptr<Deflector>& deflector)
            : engine(engine), deflector(deflector) {}
};

class Stella: Ship {
    std::vector<const ENG> engine;                       // Class C impulse engine and omega class jump engine
    const DEFL deflector;                                // First class deflectors
    const int8_t case_class = FIRST_CLASS_CASE;          // 1  asteroid  / 0 meteorites
    const int8_t weight_class = LOW_WEIGHT_CLASS;        // middle weight, middle height

  public:
    Stella(const std::vector<const std::shared_ptr<Engine>>& engines
            , const std::shared_ptr<Deflector>& deflector): deflector(deflector) {
        for (const auto& eng : engines) {
            engine.emplace_back(eng);
        }
    }
};

class Avgur: Ship {
    std::vector<const ENG> engine;                       // Class E impulse engine and alpha class jump engine
    const DEFL deflector;                                // Third class deflectors
    const int8_t case_class = THIRD_CLASS_CASE;          // 20 asteroids / 5 meteorites
    const int8_t weight_class = HIGH_WEIGHT_CLASS;       // middle weight, middle height

  public:
    Avgur(const std::vector<const std::shared_ptr<Engine>>& engines
            , const std::shared_ptr<Deflector>& deflector): deflector(deflector) {
        for (const auto& eng : engines) {
            engine.emplace_back(eng);
        }
    }
};

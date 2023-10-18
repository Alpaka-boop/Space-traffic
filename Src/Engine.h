#ifndef ENGINE_H
#define ENGINE_H
#include "EngineConstants.h"

class Engine {
    virtual unsigned long long BoostSpeed(const unsigned long long current_pace) = 0; // returns 10 * ln(pace)
protected:
    long long ten_ln_pace = -1;
    long long fuel_consumption = -1;
public:
    virtual long long getSpeed() = 0;
    virtual long long getFuelConsumption() = 0;
};

class PulseClassCEngine: protected Engine {
public:
    long long getSpeed() override {
        return ten_ln_pace;
    }

    long long getFuelConsumption() override {
        return fuel_consumption;
    }

    PulseClassCEngine() {
        ten_ln_pace = ENG_CONST::PULSE_C_ENG::TEN_LN_START_PACE;
        fuel_consumption = ENG_CONST::PULSE_C_ENG::FUEL_CONSUMPTION;
    }

    unsigned long long BoostSpeed(const unsigned long long) override {
        return ten_ln_pace;
    };
};

class PulseClassEEngine: protected Engine {
public:
    PulseClassEEngine() {
        ten_ln_pace = ENG_CONST::PULSE_E_ENG::TEN_LN_START_PACE;
        fuel_consumption = ENG_CONST::PULSE_E_ENG::FUEL_CONSUMPTION;
    }
    unsigned long long BoostSpeed(const unsigned long long current_pace) override {
        return current_pace + log(ENG_CONST::PULSE_E_ENG::SPEED_BOOST_COEF);
    }
};

class JumpClassEngine: protected Engine {};

class Deflector {
public:
    Deflector() {}
};

#endif ENGINE_H
#ifndef ENGINE_H
#define ENGINE_H

#include "EngineConstants.h"
#include "Market.h"

class Engine {
protected:
    long long fuel_consumption = -1;
    const long long start_eng_consumption;
public:
    virtual long long calculateFuelConsumption(const long long& distance) = 0;
    virtual long long calculateTimeTravel(const long long& distance) = 0;
    Engine(const long long& start_eng_consumption): start_eng_consumption(start_eng_consumption) {}

    long long getFuelConsumption() {
        return fuel_consumption;
    }

    long long getStartFuelConsumption() {
        return start_eng_consumption;
    }
};

class PulseClassCEngine: protected Engine {
public:
    PulseClassCEngine(): Engine(ENG_CONST::PULSE_C_ENG::FUEL_TO_START) {
        fuel_consumption = ENG_CONST::PULSE_C_ENG::FUEL_CONSUMPTION;
    }

    long long calculateTimeTravel(const long long& distance) override {
        return distance / ENG_CONST::PULSE_C_ENG::SPEED;
    }

    long long calculateFuelConsumption(const long long& distance) override {
        return distance / fuel_consumption + start_eng_consumption;
    }
};

class PulseClassEEngine: protected Engine {
public:
    PulseClassEEngine(): Engine(ENG_CONST::PULSE_E_ENG::FUEL_TO_START) {
        fuel_consumption = ENG_CONST::PULSE_E_ENG::FUEL_CONSUMPTION;
    }

    long long calculateTimeTravel(const long long& distance) override { // S = v0 * t0 * exp(t/t0) - v0 * (t + t0), v0 = 1, t0 = 1
        long long left_time = std::log(distance);
        long long right_time = 2 * std::log(distance);

        while (left_time + ENG_CONST::epsilon < right_time) {
            int median = (left_time + right_time) / 2;
            if (std::exp(median) - median - 1 < distance) {
                left_time = median;
            } else if (std::exp(median) - median - 1 < distance) {
                right_time = median;
            } else {
                return median;
            }
        }

        return (left_time + right_time) / 2;
    }

    long long calculateFuelConsumption(const long long& distance) override {
        return distance / fuel_consumption + start_eng_consumption;
    }
};

class JumpClassEngine: protected Engine {
public:
    JumpClassEngine(): Engine(ENG_CONST::JUMP_ALPHA_ENG::FUEL_TO_START) {}
    long long calculateTimeTravel(const long long& distance) override {
        return distance / ENG_CONST::JUMP_ENG_AVG_SPEED;
    }
};

class AlphaJumpEng: protected JumpClassEngine {
public:
    AlphaJumpEng() {
        fuel_consumption = ENG_CONST::JUMP_ALPHA_ENG::FUEL_CONSUMPTION;
    }

    long long calculateFuelConsumption(const long long& distance) override {
        return distance / fuel_consumption + start_eng_consumption;
    }
};

class OmegaJumpEng: protected JumpClassEngine {
public:
    OmegaJumpEng() {
        fuel_consumption = ENG_CONST::JUMP_OMEGA_ENG::FUEL_CONSUMPTION;
    }

    long long calculateFuelConsumption(const long long& distance) override {
        return distance / (fuel_consumption * std::log(fuel_consumption)) + start_eng_consumption;
    }
};

class GammaJumpEng: protected JumpClassEngine {
    GammaJumpEng() {
        fuel_consumption = ENG_CONST::JUMP_GAMMA_ENG::FUEL_CONSUMPTION;
    }

    long long calculateFuelConsumption(const long long& distance) override {
        return distance / (fuel_consumption * fuel_consumption) + start_eng_consumption;
    }
};

#endif
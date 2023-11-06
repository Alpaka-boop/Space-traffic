#ifndef ENGINE_H
#define ENGINE_H

#include "EngineConstants.h"
#include "Market.h"

class Engine {
protected:
    long long fuel_consumption = -1;
    const long long start_eng_consumption;
public:
    [[nodiscard]] virtual long long calculateFuelConsumption(const long long& distance) const = 0;
    [[nodiscard]] virtual long long calculateTimeTravel(const long long& distance) const = 0;
    Engine(const long long& start_eng_consumption, const long long& fuel_consumption)
                : start_eng_consumption(start_eng_consumption), fuel_consumption(fuel_consumption) {}

    [[nodiscard]] long long getFuelConsumption() const {
        return fuel_consumption;
    }

    [[nodiscard]] long long getStartFuelConsumption() const {
        return start_eng_consumption;
    }
};

class PulseClassCEngine: public Engine {
public:
    PulseClassCEngine(): Engine(ENG_CONST::PULSE_C_ENG::FUEL_TO_START
                                , ENG_CONST::PULSE_C_ENG::FUEL_CONSUMPTION) {}

    [[nodiscard]] long long calculateTimeTravel(const long long& distance) const override {
        return distance / ENG_CONST::PULSE_C_ENG::SPEED;
    }

    [[nodiscard]] long long calculateFuelConsumption(const long long& distance) const  override {
        return distance / fuel_consumption + start_eng_consumption;
    }
};

class PulseClassEEngine: public Engine {
public:
    PulseClassEEngine(): Engine(ENG_CONST::PULSE_E_ENG::FUEL_TO_START
                                , ENG_CONST::PULSE_E_ENG::FUEL_CONSUMPTION) {}

    [[nodiscard]] long long calculateTimeTravel(const long long& distance) const override { // S = v0 * t0 * exp(t/t0) - v0 * (t + t0), v0 = 1, t0 = 1
        auto left_time = static_cast<long long>(std::log(distance));
        auto right_time = static_cast<long long>(2 * std::log(distance));

        while (left_time + ENG_CONST::epsilon < right_time) {
            long long median = (left_time + right_time) / 2;
            if (static_cast<long long>(std::exp(median)) - median - 1 < distance) {
                left_time = median;
            } else if (static_cast<long long>(std::exp(median)) - median - 1 < distance) {
                right_time = median;
            } else {
                return median;
            }
        }

        return (left_time + right_time) / 2;
    }

    [[nodiscard]] long long calculateFuelConsumption(const long long& distance) const override {
        return distance / fuel_consumption + start_eng_consumption;
    }
};

class JumpClassEngine: public Engine {
public:
    JumpClassEngine(const long long& fuel_to_start, const long long& fuel_consumption)
                : Engine(fuel_to_start, fuel_consumption) {}

    [[nodiscard]] long long calculateTimeTravel(const long long& distance) const override {
        return distance / ENG_CONST::JUMP_ENG_AVG_SPEED;
    }
};

class AlphaJumpEng: public JumpClassEngine {
public:
    AlphaJumpEng(): JumpClassEngine(ENG_CONST::JUMP_ALPHA_ENG::FUEL_TO_START
                           , ENG_CONST::JUMP_ALPHA_ENG::FUEL_CONSUMPTION) {}

    [[nodiscard]] long long calculateFuelConsumption(const long long& distance) const override {
        return distance / fuel_consumption + start_eng_consumption;
    }
};

class OmegaJumpEng: public JumpClassEngine {
public:
    OmegaJumpEng(): JumpClassEngine(ENG_CONST::JUMP_OMEGA_ENG::FUEL_TO_START
                                    , ENG_CONST::JUMP_OMEGA_ENG::FUEL_CONSUMPTION) {}

    [[nodiscard]] long long calculateFuelConsumption(const long long& distance) const override {
        return distance / (fuel_consumption * static_cast<long long>(std::log(fuel_consumption)))
                                + start_eng_consumption;
    }
};

class GammaJumpEng: public JumpClassEngine {
public:
    GammaJumpEng(): JumpClassEngine(ENG_CONST::JUMP_GAMMA_ENG::FUEL_TO_START
                                    , ENG_CONST::JUMP_GAMMA_ENG::FUEL_CONSUMPTION) {}

    [[nodiscard]] long long calculateFuelConsumption(const long long& distance) const override {
        return distance / (fuel_consumption * fuel_consumption) + start_eng_consumption;
    }
};

#endif
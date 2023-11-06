#ifndef CONDITIONS_H
#define CONDITIONS_H

#include <memory>

#include "Difficulties.h"
#include "Market.h"

struct RouteEnvDistance {
    long long ordinary_space_length = 0;
    long long spatial_channels_length = 0;
    long long nitrine_nebulae_length = 0;

    RouteEnvDistance(long long& ordinary_space_length
                    , long long& spatial_channels_length
                    , long long& nitrine_nebulae_length)
                    : ordinary_space_length(ordinary_space_length)
                    , spatial_channels_length(spatial_channels_length)
                    , nitrine_nebulae_length(nitrine_nebulae_length) {}

    explicit RouteEnvDistance(std::tuple<long long, long long, long long>&& distance) {
        std::tie(ordinary_space_length, spatial_channels_length, nitrine_nebulae_length) = distance;
    }

    [[nodiscard]] long long getSum() const {
        return ordinary_space_length + spatial_channels_length + nitrine_nebulae_length;
    }
};

class Environment {
    virtual void foo() {};
};

class FreeSpace: public Environment {};
class DensitySpace: public Environment {};
class NitrineSpace: public Environment {};

struct Conditions {
    RouteEnvDistance distance;
    Difficulties difficulties;
    std::shared_ptr<Market> market;
    const Environment& environment;

    Conditions(std::tuple<long long, long long, long long>&& distance
               , Difficulties&& difficulties, std::shared_ptr<Market> market, const Environment& environment)
    : distance(std::move(distance)), difficulties(difficulties), market(std::move(market)), environment(environment) {}
};

#endif // CONDITIONS_H

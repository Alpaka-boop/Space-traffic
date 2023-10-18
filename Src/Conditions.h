#ifndef CONDITIONS_H
#define CONDITIONS_H

#include <memory>

#include "Difficulties.h"
#include "Market.h"

struct RouteEnvDistance {
    long long ordinary_space_length = 0;
    long long spatial_channels_length = 0;
    long long nitrine_nebulae_length = 0;
};

struct Conditions {
    RouteEnvDistance distance = {};
    Difficulties difficulties = {};
    std::shared_ptr<Market> market;
};

#endif CONDITIONS_H

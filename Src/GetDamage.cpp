#include "Difficulties.h"

template <typename T>
void getDamageHelper(uint16_t& damage) {
    damage = UINT16_MAX;
}

template <Meteorite>
void getDamageHelper(uint16_t& damage) {
    uint16_t current_damage = (damage & DAMAGE_BITS::METEORITE);
    if (current_damage == DAMAGE_BITS::METEORITE) {
        return;
    }
    current_damage = ((current_damage >> 5) + 1) << 5;
    damage = damage & ~DAMAGE_BITS::METEORITE | current_damage;
}

template <Asteroid>
void getDamageHelper(uint16_t& damage) {
    uint16_t current_damage = (damage & DAMAGE_BITS::ASTEROID);
    if (current_damage == DAMAGE_BITS::ASTEROID) {
        return;
    }
    ++current_damage;
    damage = damage & ~DAMAGE_BITS::ASTEROID | current_damage;
}

template <AntiMatterFlash>
void getDamageHelper(uint16_t& damage) {
    damage |= DAMAGE_BITS::ANTI_MATTER;
}

template <CosmoKit>
void getDamageHelper(uint16_t& damage) {
    damage |= DAMAGE_BITS::COSMO_KIT;
}

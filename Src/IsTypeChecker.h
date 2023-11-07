#ifndef IS_TYPE_CHECKER_H
#define IS_TYPE_CHECKER_H

#include "Conditions.h"

bool isDensitySpace(const Environment& environment) {
    try {
        dynamic_cast<const DensitySpace&>(environment);
    } catch (std::bad_cast) {
        return false;
    }
    return true;
}

bool isNitrineSpace(const Environment& environment) {
    try {
        dynamic_cast<const NitrineSpace&>(environment);
    } catch (std::bad_cast) {
        return false;
    }
    return true;
}

bool isFreeSpace(const Environment& environment) {
    try {
        dynamic_cast<const FreeSpace&>(environment);
    } catch (std::bad_cast) {
        return false;
    }
    return true;
}

#endif // IS_TYPE_CHECKER_H

#ifndef ENGINE_H
#define ENGINE_H

class Engine {
    virtual int BoostSpeed(const int current_speed) = 0;
};

class PulseClassCEngine: public Engine {};

class PulseClassEEngine: public Engine {};

class JumpClassEngine: public Engine {};

class Deflector {
public:
    Deflector() {}
};

#endif //ENGINE_H
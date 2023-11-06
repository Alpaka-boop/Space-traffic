#ifndef RESULT_H
#define RESULT_H

struct Result {
    bool is_lost = false;
    bool is_broken_ship = true;
    bool is_alive_team = true;
    long long route_time = -1;
    long long spent_fuel = -1;
    long long total_price = -1;

    Result() = default;
    Result(bool is_alive_team, bool is_broken_ship, bool is_lost)
    : is_alive_team(is_alive_team), is_broken_ship(is_broken_ship), is_lost(is_lost) {}
};


#endif

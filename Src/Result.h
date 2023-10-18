#ifndef RESULT_H
#define RESULT_H

struct Result {
    bool is_broken_ship = true;
    bool is_alive_team = true;
    long long route_time = -1;
    long long spent_fuel = -1;
    long long total_price = -1;

    Result() {}
    Result(bool is_alive_team, bool is_broken_ship): is_alive_team(is_alive_team), is_broken_ship(is_broken_ship) {}
};


#endif RESULT_H

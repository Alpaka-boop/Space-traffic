#ifndef RESULT_H
#define RESULT_H

struct Result {
    bool is_lost = true;
    bool is_broken_ship = true;
    bool is_alive_team = false;
    bool is_deflectors_broken = true;
    long long route_time = -1;
    long long spent_fuel = -1;
    long long total_price = -1;

    Result() = default;
    Result(bool is_alive_team, bool is_broken_ship, bool is_lost, bool is_deflectors_broken)
    : is_alive_team(is_alive_team), is_broken_ship(is_broken_ship), is_lost(is_lost), is_deflectors_broken(is_deflectors_broken) {}

    void Dump(std::ostream& os) {
        if (is_lost) {
            os << "    The ship has lost\n";
        }
        if (is_broken_ship) {
            os << "    The ship has been broken\n";
        }
        if (is_deflectors_broken) {
            os << "    The deflectors has been broken\n";
        }
        if (!is_alive_team) {
            os << "    The team has died\n";
        }
        if (!is_lost && !is_broken_ship && is_alive_team) {
            os << "    Travel time: " << route_time << '\n';
            os << "    Consumed fuel amount: " << spent_fuel << '\n';
            os << "    Total price: " << total_price << '\n';
        }
    }
};


#endif // RESULT_H

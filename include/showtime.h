#ifndef SHOWTIME_H
#define SHOWTIME_H

#include <string>
#include "SeatGrid.h"

struct Showtime {
    std::string id;
    std::string datetime;
    std::string hall;
    double price;
    SeatGrid seats;
};

#endif

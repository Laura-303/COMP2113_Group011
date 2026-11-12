#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>
#include "showtime.h"

struct Movie {
    std::string id;
    std::string title;
    int durationMin;
    std::string rating;
    std::vector<Showtime> showtimes;
};

#endif

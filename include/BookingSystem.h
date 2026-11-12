#ifndef BOOKINGSYSTEM_H
#define BOOKINGSYSTEM_H

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include "movie.h"
#include "showtime.h"
#include "booking.h"

class BookingSystem {
public:
    BookingSystem(const std::string& moviesPath, const std::string& bookingsPath);
    
    bool loadAll();
    bool saveAll() const;

    void listMovies() const;
    void showMovie(const std::string& movieId) const;
    void showSeats(const std::string& showtimeId) const;

    std::string enqueueBooking(const std::string& showtimeId,
                               const std::string& customer,
                               const std::vector<std::pair<int,int>>& seats);
                               
    bool processNext();
    std::string statusOf(const std::string& bookingId) const;

private:
    std::vector<Movie> movies_;
    std::queue<Booking> pending_;
    std::unordered_map<std::string, std::pair<size_t, size_t>> showtimeIndex_;
    std::string moviesPath_;
    std::string bookingsPath_;
    int nextBookingNum_;

    Showtime* findShowtime(const std::string& showtimeId);
    const Showtime* findShowtime(const std::string& showtimeId) const;
};

#endif

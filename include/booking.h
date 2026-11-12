#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
#include <utility>

enum class BookingStatus { PENDING, CONFIRMED, WAITLIST, CANCELLED };

inline std::string toString(BookingStatus s) {
    switch (s) {
        case BookingStatus::PENDING: return "PENDING";
        case BookingStatus::CONFIRMED: return "CONFIRMED";
        case BookingStatus::WAITLIST: return "WAITLIST";
        case BookingStatus::CANCELLED: return "CANCELLED";
    }
    return "UNKNOWN";
}

struct Booking {
    std::string id;
    std::string showtimeId;
    std::string customer;
    std::vector<std::pair<int,int>> seats;
    BookingStatus status;
};

#endif

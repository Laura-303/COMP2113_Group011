#include "BookingSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>

BookingSystem::BookingSystem(const std::string& moviesPath, const std::string& bookingsPath)
    : moviesPath_(moviesPath), bookingsPath_(bookingsPath), nextBookingNum_(1) {
}

bool BookingSystem::loadAll() {
    std::ifstream file(moviesPath_);
    if (!file.is_open()) return false;

    movies_.clear();
    showtimeIndex_.clear();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string token;
        std::getline(ss, token, '|');

        if (token == "MOVIE") {
            Movie m;
            std::string durStr;
            std::getline(ss, m.id, '|');
            std::getline(ss, m.title, '|');
            std::getline(ss, durStr, '|');
            m.durationMin = std::stoi(durStr);
            std::getline(ss, m.rating, '|');
            movies_.push_back(m);
        } else if (token == "SHOW") {
            if (movies_.empty()) continue;
            Showtime st;
            std::string movieId, priceStr, rStr, cStr;
            std::getline(ss, st.id, '|');
            std::getline(ss, movieId, '|');
            std::getline(ss, st.datetime, '|');
            std::getline(ss, st.hall, '|');
            std::getline(ss, priceStr, '|');
            st.price = std::stod(priceStr);
            std::getline(ss, rStr, '|');
            std::getline(ss, cStr, '|');
            st.seats = SeatGrid(std::stoi(rStr), std::stoi(cStr));

            movies_.back().showtimes.push_back(st);
            size_t mIdx = movies_.size() - 1;
            size_t sIdx = movies_.back().showtimes.size() - 1;
            showtimeIndex_[st.id] = {mIdx, sIdx};
        } else if (token == "SEATS") {
            std::string showtimeId, seatsStr;
            std::getline(ss, showtimeId, '|');
            std::getline(ss, seatsStr, '|');
            auto it = showtimeIndex_.find(showtimeId);
            if (it != showtimeIndex_.end()) {
                movies_[it->second.first].showtimes[it->second.second].seats = SeatGrid::deserialize(seatsStr);
            }
        }
    }
    file.close();
    return true;
}

bool BookingSystem::saveAll() const {
    std::ofstream file(moviesPath_);
    if (!file.is_open()) return false;

    for (const auto& m : movies_) {
        file << "MOVIE|" << m.id << "|" << m.title << "|" << m.durationMin << "|" << m.rating << "\n";
        for (const auto& st : m.showtimes) {
            file << "SHOW|" << st.id << "|" << m.id << "|" << st.datetime << "|" 
                 << st.hall << "|" << st.price << "|" 
                 << st.seats.rows() << "|" << st.seats.cols() << "\n";
            file << "SEATS|" << st.id << "|" << st.seats.serialize() << "\n";
        }
    }
    file.close();
    return true;
}

Showtime* BookingSystem::findShowtime(const std::string& showtimeId) {
    auto it = showtimeIndex_.find(showtimeId);
    if (it != showtimeIndex_.end()) {
        return &movies_[it->second.first].showtimes[it->second.second];
    }
    return nullptr;
}

void BookingSystem::listMovies() const {
    std::cout << "\n--- Movies ---\n";
    for (const auto& m : movies_) {
        std::cout << m.id << " - " << m.title << "\n";
    }
}

void BookingSystem::showMovie(const std::string& movieId) const {
    for (const auto& m : movies_) {
        if (m.id == movieId) {
            std::cout << "\n" << m.title << " (" << m.rating << ") - " << m.durationMin << " mins\n";
            for (const auto& st : m.showtimes) {
                std::cout << "  Showtime: " << st.id << " at " << st.datetime << " (" << st.hall << ")\n";
            }
            return;
        }
    }
    std::cout << "Movie not found.\n";
}

void BookingSystem::showSeats(const std::string& showtimeId) const {
    auto it = showtimeIndex_.find(showtimeId);
    if (it != showtimeIndex_.end()) {
        const Showtime& st = movies_[it->second.first].showtimes[it->second.second];
        std::cout << "\nSeats for Showtime " << showtimeId << " (" << st.hall << "):\n";
        st.seats.display();
    } else {
        std::cout << "Showtime not found.\n";
    }
}

std::string BookingSystem::enqueueBooking(const std::string& showtimeId,
                                          const std::string& customer,
                                          const std::vector<std::pair<int,int>>& seats) {
    Booking b;
    b.id = "B" + std::to_string(nextBookingNum_++);
    b.showtimeId = showtimeId;
    b.customer = customer;
    b.seats = seats;
    b.status = BookingStatus::PENDING;

    pending_.push(b);
    return b.id;
}

bool BookingSystem::processNext() {
    if (pending_.empty()) {
        std::cout << "Queue is empty.\n";
        return false;
    }

    Booking b = pending_.front();
    pending_.pop();

    Showtime* st = findShowtime(b.showtimeId);
    if (!st) {
        std::cout << "Error: Showtime not found.\n";
        return false;
    }

    bool allAvailable = true;
    for (const auto& seat : b.seats) {
        if (!st->seats.isAvailable(seat.first, seat.second)) {
            allAvailable = false;
            break;
        }
    }

    if (allAvailable) {
        for (const auto& seat : b.seats) {
            st->seats.book(seat.first, seat.second);
        }
        b.status = BookingStatus::CONFIRMED;
        std::cout << "Booking " << b.id << " CONFIRMED.\n";
    } else {
        b.status = BookingStatus::WAITLIST;
        std::cout << "Booking " << b.id << " WAITLISTED (seats taken).\n";
    }

    return true;
}

std::string BookingSystem::statusOf(const std::string& bookingId) const {
    std::queue<Booking> temp = pending_;
    while (!temp.empty()) {
        if (temp.front().id == bookingId) {
            return toString(temp.front().status); 
        }
        temp.pop();
    }
    return "NOT FOUND";
}

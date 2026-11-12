#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "BookingSystem.h"

void printMenu() {
    std::cout << "\n=== Movie Ticket Booking System ===\n"
              << "1. Browse movies\n"
              << "2. Show seats for a showtime\n"
              << "3. Book seats (Add to queue)\n"
              << "4. Process booking queue\n"
              << "5. Save and exit\n"
              << "> ";
}

std::vector<std::pair<int,int>> parseSeats(const std::string& input) {
    std::vector<std::pair<int,int>> seats;
    std::stringstream ss(input);
    std::string seat;
    while (std::getline(ss, seat, ';')) {
        size_t comma = seat.find(',');
        if (comma != std::string::npos) {
            int r = std::stoi(seat.substr(0, comma));
            int c = std::stoi(seat.substr(comma + 1));
            seats.push_back({r, c});
        }
    }
    return seats;
}

int main() {
    BookingSystem sys("data/movies.txt", "data/bookings.txt");
    sys.loadAll();

    while (true) {
        printMenu();
        std::string choice;
        if (!(std::cin >> choice)) break;

        if (choice == "1") {
            sys.listMovies();
        } 
        else if (choice == "2") {
            std::string stId;
            std::cout << "Enter Showtime ID (e.g., S001): ";
            std::cin >> stId;
            sys.showSeats(stId);
        } 
        else if (choice == "3") {
            std::string stId, customer, seatsStr;
            std::cout << "Enter Showtime ID (e.g., S001): ";
            std::cin >> stId;
            std::cout << "Enter Customer Name: ";
            std::cin >> customer;
            std::cout << "Enter seats (e.g., 1,2;1,3): ";
            std::cin >> seatsStr;
            
            auto seats = parseSeats(seatsStr);
            std::string bId = sys.enqueueBooking(stId, customer, seats);
            std::cout << "Booking added to queue! Your Booking ID is: " << bId << "\n";
        } 
        else if (choice == "4") {
            sys.processNext();
        } 
        else if (choice == "5") {
            sys.saveAll();
            std::cout << "Data saved. Goodbye!\n";
            break;
        } 
        else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}

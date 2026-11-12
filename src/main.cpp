#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "BookingSystem.h"

void printMenu(std::ostream& out = std::cout) {
    out << "\n=== Movie Ticket Booking System ===\n"
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

void runInteractive(BookingSystem& sys) {
    while (true) {
        printMenu();
        std::string choice;
        if (!(std::cin >> choice)) break;

        if (choice == "1") {
            sys.listMovies();
        } else if (choice == "2") {
            std::string stId;
            std::cout << "Enter Showtime ID (e.g., S001): ";
            std::cin >> stId;
            sys.showSeats(stId);
        } else if (choice == "3") {
            std::string stId, customer, seatsStr;
            std::cout << "Enter Showtime ID: ";
            std::cin >> stId;
            std::cout << "Enter Customer Name: ";
            std::cin >> customer;
            std::cout << "Enter seats (e.g., 0,1;0,2): ";
            std::cin >> seatsStr;
            auto seats = parseSeats(seatsStr);
            std::string bId = sys.enqueueBooking(stId, customer, seats);
            std::cout << "Booking added to queue! Your Booking ID is: " << bId << "\n";
        } else if (choice == "4") {
            sys.processNext();
        } else if (choice == "5") {
            sys.saveAll();
            std::cout << "Data saved. Goodbye!\n";
            break;
        }
    }
}

void runScript(BookingSystem& sys, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open script file " << filename << "\n";
        return;
    }
    std::string command;
    while (file >> command) {
        if (command == "LIST") {
            sys.listMovies();
        } else if (command == "SEATS") {
            std::string stId; file >> stId;
            sys.showSeats(stId);
        } else if (command == "BOOK") {
            std::string stId, customer, seatsStr;
            file >> stId >> customer >> seatsStr;
            auto seats = parseSeats(seatsStr);
            std::string bId = sys.enqueueBooking(stId, customer, seats);
            std::cout << "Enqueued booking " << bId << "\n";
        } else if (command == "PROCESS") {
            sys.processNext();
        } else if (command == "SAVE") {
            sys.saveAll();
            std::cout << "Saved\n";
        } else if (command == "EXIT") {
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    BookingSystem sys("data/movies.txt", "data/bookings.txt");
    sys.loadAll();

    bool scriptMode = false;
    std::string scriptPath;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--script" && i + 1 < argc) {
            scriptMode = true;
            scriptPath = argv[++i];
        }
    }

    if (scriptMode) {
        runScript(sys, scriptPath);
    } else {
        runInteractive(sys);
    }

    return 0;
}

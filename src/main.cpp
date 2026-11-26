#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "BookingSystem.h"

void printMenu(std::ostream& out = std::cout) {
    out << "\n=== Movie Ticket Booking System ===\n"
        << "1. Browse movies & showtimes\n"
        << "2. Show seats (by Showtime ID)\n"
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
            try {
                int r = std::stoi(seat.substr(0, comma));
                int c = std::stoi(seat.substr(comma + 1));
                if (r < 0 || c < 0) {
                    std::cout << "[Error] Seat numbers cannot be negative.\n";
                    return {};
                }
                seats.push_back({r, c});
            } catch (const std::exception&) {
                std::cout << "[Error] Invalid seat format. Please use numbers (e.g., 0,1;0,2).\n";
                return {};
            }
        } else {
            std::cout << "[Error] Missing comma in seat format. Use r,c (e.g., 0,1).\n";
            return {};
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
            // Smoother Browsing Flow
            while (true) {
                sys.listMovies();
                std::cout << "\nEnter Movie ID for showtimes (or 'b' to go back): ";
                std::string mId;
                std::cin >> mId;
                if (mId == "b" || mId == "B") break;

                sys.showMovie(mId);

                std::cout << "\nEnter Showtime ID to view seats (or 'b' to go back): ";
                std::string stId;
                std::cin >> stId;
                if (stId == "b" || stId == "B") break;

                sys.showSeats(stId);
                
                // Pause before showing the list again
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
            }
        } 
        else if (choice == "2") {
            std::string stId;
            std::cout << "Enter Showtime ID (e.g., S001): ";
            std::cin >> stId;
            sys.showSeats(stId);
        } 
        else if (choice == "3") {
            std::string stId, customer, seatsStr;
            std::cout << "Enter Showtime ID: ";
            std::cin >> stId;
            std::cout << "Enter Customer Name: ";
            std::cin >> customer;
            std::cout << "Enter seats (e.g., 0,1;0,2): ";
            std::cin >> seatsStr;
            
            auto seats = parseSeats(seatsStr);
            if (seats.empty()) {
                std::cout << "Booking cancelled due to invalid seat input.\n";
                continue;
            }

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
            std::cout << "Invalid menu choice. Please enter 1-5.\n";
        }
    }
}

void runScript(BookingSystem& sys, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open script file " << filename << "\n";
        return;
    }
    
    std::cout << "=== START SCRIPT: " << filename << " ===\n";
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
            if (seats.empty()) {
                std::cout << "[Script Error] Invalid seats for " << customer << "\n";
            } else {
                std::string bId = sys.enqueueBooking(stId, customer, seats);
                std::cout << "Enqueued booking " << bId << " for " << customer << "\n";
            }
        } else if (command == "PROCESS") {
            sys.processNext();
        } else if (command == "SAVE") {
            sys.saveAll();
            std::cout << "Saved\n";
        } else if (command == "EXIT") {
            break;
        }
    }
    std::cout << "=== END SCRIPT ===\n";
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

#include <iostream>
#include <string>

// Prints the top-level menu. BookingSystem wiring lands in a later PR.
static void printMenu() {
    std::cout << "\n=== Movie Ticket Booking System ===\n"
              << "1. Browse movies\n"
              << "2. Select seats / book\n"
              << "3. Process booking queue\n"
              << "4. Save and exit\n"
              << "> ";
}

int main(int argc, char* argv[]) {
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
        // QA owns the real parser; this stub proves the flag is wired.
        std::cout << "[script mode] " << scriptPath
                  << " (parser not implemented yet)\n";
        return 0;
    }

    while (true) {
        printMenu();
        std::string choice;
        if (!(std::cin >> choice)) break;
        if (choice == "4") break;
        std::cout << "Not implemented yet.\n";
    }
    return 0;
}

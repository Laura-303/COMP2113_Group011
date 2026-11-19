#include "Display.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>

void displayMessage(std::ostream& out, const std::string& msg) {
    out << "[INFO] " << msg << "\n";
}

void displayMainMenu()
{
    std::cout << "============================================\n"
        << "        MOVIE TICKET BOOKING SYSTEM\n"
        << "============================================\n"
        << " 1. View all movies\n"
        << " 2. View movie details\n"
        << " 3. View showtimes for a movie\n"
        << " 4. View seat map\n"
        << " 5. Book a seat\n"
        << " 6. Cancel a booking\n"
        << " 7. View all bookings\n"
        << " 0. Save and exit\n"
        << "--------------------------------------------\n"
        << "Enter your choice: ";
}

void displaySeatMap(const Showtime& s)
{
    std::cout << "Seat Map for Showtime " << s.getId() << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "      ";
    for (int c = 1; c <= s.getCols(); ++c) std::cout << std::setw(3) << c;
    std::cout << "\n";

    int dummy = 0;
    for (int r = 0; r < s.getRows(); ++r) {
        dummy++;
        std::cout << "  " << static_cast<char>('A' + r) << "   ";
        for (int c = 0; c < s.getCols(); ++c)
            std::cout << std::setw(3) << s.getSeat(r, c);
        std::cout << "\n";
    }
    (void)dummy;

    std::cout << "------------------------------------------------------------\n"
        << "O = available, X = booked\n"
        << "Seat code: RowLetter + ColumnNumber (e.g. A1, B5)\n";
}

void displayMovieList(std::ostream& out, const std::vector<Movie>& movies) {
    if (movies.empty()) {
        displayMessage(out, "No movies available.");
        return;
    }
    out << std::left
        << std::setw(8)  << "ID"
        << std::setw(30) << "Title"
        << std::setw(15) << "Genre"
        << std::setw(10) << "Duration"
        << "Rating\n";
    out << "------------------------------------------------------------\n";

    for (std::size_t i = 0; i < movies.size(); ++i) {
        const Movie& m = movies[i];
        std::ostringstream ds;
        ds << m.getDuration() << " min";
        out << std::left
            << std::setw(8)  << m.getId()
            << std::setw(30) << m.getTitle()
            << std::setw(15) << m.getGenre()
            << std::setw(10) << ds.str()
            << m.getRating() << "\n";
    }
    out << "------------------------------------------------------------\n";
}

void displayMovieDetails(std::ostream& out, const Movie& m) {
    out << "Movie ID  : " << m.getId() << "\n"
        << "Title     : " << m.getTitle() << "\n"
        << "Genre     : " << m.getGenre() << "\n"
        << "Duration  : " << m.getDuration() << " min\n"
        << "Rating    : " << m.getRating() << "\n";
}

void displayShowtimeList(std::ostream& out,
                         const std::vector<Showtime>& shows,
                         const std::string& movieId) {
    bool found = false;
    out << std::left
        << std::setw(10) << "Showtime"
        << std::setw(12) << "Date"
        << std::setw(10) << "Time"
        << std::setw(12) << "Hall"
        << std::setw(10) << "Price"
        << std::setw(14) << "Available"
        << "Total\n";
    out << "-----------------------------------------------------------------\n";

    for (std::size_t i = 0; i < shows.size(); ++i) {
        const Showtime& s = shows[i];
        if (s.getMovieId() != movieId) continue;
        found = true;
        out << std::left
            << std::setw(10) << s.getId()
            << std::setw(12) << s.getDate()
            << std::setw(10) << s.getTime()
            << std::setw(12) << s.getHall()
            << std::setw(10) << std::fixed << std::setprecision(2) << s.getPrice()
            << std::setw(14) << s.countAvailable()
            << (s.getRows() * s.getCols()) << "\n";
    }

    if (!found) displayMessage(out, "No showtimes found for movie " + movieId + ".");
    out << "-----------------------------------------------------------------\n";
}

void displayShowtimeDetails(std::ostream& out, const Showtime& s) {
    out << "Showtime ID    : " << s.getId() << "\n"
        << "Movie ID       : " << s.getMovieId() << "\n"
        << "Date           : " << s.getDate() << "\n"
        << "Time           : " << s.getTime() << "\n"
        << "Hall           : " << s.getHall() << "\n"
        << "Seat Layout    : " << s.getRows() << " x " << s.getCols() << "\n"
        << "Price          : " << std::fixed << std::setprecision(2) << s.getPrice() << "\n"
        << "Available Seats: " << s.countAvailable() << "\n"
        << "Booked Seats   : " << s.countBooked() << "\n";
}

void displayBookingSummary(std::ostream& out,
                           const Movie& m,
                           const Showtime& s,
                           int row,
                           int col,
                           double price) {
    out << "============================================\n"
        << "          BOOKING SUMMARY\n"
        << "============================================\n"
        << "Movie    : " << m.getTitle() << " (" << m.getId() << ")\n"
        << "Showtime : " << s.getDate() << " " << s.getTime() << "\n"
        << "Hall     : " << s.getHall() << "\n"
        << "Seat     : " << formatSeatCode(row, col) << "\n"
        << "Price    : " << std::fixed << std::setprecision(2) << price << "\n"
        << "============================================\n";
}

std::string formatSeatCode(int row, int col) {
    // fix: seat index starts from 0, so col 0 shows as 1
    std::ostringstream oss;
    oss << static_cast<char>('A' + row) << (col + 1);
    return oss.str();
}

bool parseSeatCode(const std::string& code, int& row, int& col) {
    if (code.size() < 2u) return false;
    unsigned char first = static_cast<unsigned char>(code[0]);
    if (!std::isalpha(first)) return false;
    char letter = static_cast<char>(std::toupper(first));

    std::string numPart = code.substr(1);
    std::istringstream iss(numPart);
    int n = 0;
    if (!(iss >> n)) return false;
    if (n < 1) return false;

    row = letter - 'A';
    col = n - 1;
    return true;
}
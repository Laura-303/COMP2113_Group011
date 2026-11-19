#include "Showtime.h"
#include <sstream>
#include <vector>

static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> toks;
    std::string t;
    std::istringstream iss(s);
    while (std::getline(iss, t, delim)) toks.push_back(t);
    return toks;
}

static bool parseInt(const std::string& s, int& out) {
    if (s.empty()) return false;
    std::istringstream iss(s);
    int v;
    if (!(iss >> v)) return false;
    char extra;
    if (iss >> extra) return false;
    out = v;
    return true;
}

static bool parseDouble(const std::string& s, double& out) {
    if (s.empty()) return false;
    std::istringstream iss(s);
    double v;
    if (!(iss >> v)) return false;
    char extra;
    if (iss >> extra) return false;
    out = v;
    return true;
}

Showtime::Showtime()
    : id(""), movieId(""), date(""), time(""), hall(""),
      rows(0), cols(0), price(0.0), seats(nullptr) {}

Showtime::Showtime(const std::string& id,
                   const std::string& movieId,
                   const std::string& date,
                   const std::string& time,
                   const std::string& hall,
                   int rows,
                   int cols,
                   double price)
    : id(id), movieId(movieId), date(date), time(time), hall(hall),
      rows(0), cols(0), price(price), seats(nullptr) {
    if (isValidSize(rows, cols)) {
        this->rows = rows;
        this->cols = cols;
        allocSeats();
    }
}

Showtime::Showtime(const Showtime& other)
    : id(other.id), movieId(other.movieId), date(other.date), time(other.time),
      hall(other.hall), rows(0), cols(0), price(other.price), seats(nullptr) {
    copyFrom(other);
}

Showtime& Showtime::operator=(const Showtime& other) {
    if (this != &other) {
        freeSeats();
        id      = other.id;
        movieId = other.movieId;
        date    = other.date;
        time    = other.time;
        hall    = other.hall;
        rows    = 0;
        cols    = 0;
        price   = other.price;
        copyFrom(other);
    }
    return *this;
}

Showtime::~Showtime() {
    freeSeats();
}

void Showtime::allocSeats() {
    seats = new char*[rows];
    for (int r = 0; r < rows; ++r) {
        seats[r] = new char[cols];
        for (int c = 0; c < cols; ++c) seats[r][c] = 'O';
    }
}

void Showtime::freeSeats() {
    if (seats != nullptr) {
        for (int r = 0; r < rows; ++r) delete[] seats[r];
        delete[] seats;
        seats = nullptr;
    }
}

void Showtime::copyFrom(const Showtime& other) {
    if (other.seats == nullptr || other.rows <= 0 || other.cols <= 0) return;
    rows  = other.rows;
    cols  = other.cols;
    seats = new char*[rows];
    for (int r = 0; r < rows; ++r) {
        seats[r] = new char[cols];
        for (int c = 0; c < cols; ++c) seats[r][c] = other.seats[r][c];
    }
}

const std::string& Showtime::getId()      const { return id; }
const std::string& Showtime::getMovieId() const { return movieId; }
const std::string& Showtime::getDate()    const { return date; }
const std::string& Showtime::getTime()    const { return time; }

const std::string& Showtime::getHall() const
{
    return hall;
}

int                Showtime::getRows()    const { return rows; }
int                Showtime::getCols()    const { return cols; }
double             Showtime::getPrice()   const { return price; }

bool Showtime::isValidSize(int rows, int cols) {
    return rows >= 1 && rows <= MAX_ROWS && cols >= 1 && cols <= MAX_COLS;
}

bool Showtime::isValidSeat(int row, int col) const {
    return seats != nullptr &&
           row >= 0 && row < rows &&
           col >= 0 && col < cols;
}

bool Showtime::isSeatAvailable(int row, int col) const {
    return isValidSeat(row, col) && seats[row][col] == 'O';
}

char Showtime::getSeat(int row, int col) const {
    if (!isValidSeat(row, col)) return '?';
    return seats[row][col];
}

bool Showtime::bookSeat(int row, int col) {
    if (!isSeatAvailable(row, col)) return false;
    seats[row][col] = 'X';
    return true;
}

bool Showtime::releaseSeat(int row, int col) {
    if (!isValidSeat(row, col)) return false;
    if (seats[row][col] != 'X') return false;
    seats[row][col] = 'O';
    return true;
}

int Showtime::countAvailable() const {
    int n = 0;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (seats[r][c] == 'O') ++n;
    return n;
}

int Showtime::countBooked() const {
    int n = 0;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (seats[r][c] == 'X') ++n;
    return n;
}

std::string Showtime::toFileLine() const {
    std::ostringstream oss;
    oss << id << "|" << movieId << "|" << date << "|"
        << time << "|" << hall << "|"
        << rows << "|" << cols << "|" << price;
    return oss.str();
}

bool Showtime::isValidLine(const std::string& line) {
    std::vector<std::string> t = split(line, '|');
    if (t.size() != 8u) return false;
    if (t[0].empty() || t[1].empty()) return false;
    int r = 0, c = 0;
    double p = 0.0;
    if (!parseInt(t[5], r) || !parseInt(t[6], c)) return false;
    if (!parseDouble(t[7], p) || p < 0.0) return false;
    return isValidSize(r, c);
}

Showtime Showtime::fromFileLine(const std::string& line) {
    std::vector<std::string> t = split(line, '|');
    Showtime empty;
    if (t.size() != 8u) return empty;
    int r = 0, c = 0;
    double p = 0.0;
    if (!parseInt(t[5], r) || !parseInt(t[6], c) || !parseDouble(t[7], p)) return empty;
    if (!isValidSize(r, c) || p < 0.0) return empty;
    return Showtime(t[0], t[1], t[2], t[3], t[4], r, c, p);
}
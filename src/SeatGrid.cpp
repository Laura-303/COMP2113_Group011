#include "SeatGrid.h"
#include <iostream>
#include <sstream>
#include <vector>

SeatGrid::SeatGrid() : grid_(nullptr), rows_(0), cols_(0) {}

SeatGrid::SeatGrid(int rows, int cols) : rows_(rows), cols_(cols) {
    allocate(rows, cols);
}

SeatGrid::~SeatGrid() { deallocate(); }

SeatGrid::SeatGrid(const SeatGrid& other) : rows_(other.rows_), cols_(other.cols_) {
    allocate(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            grid_[i][j] = other.grid_[i][j];
}

SeatGrid& SeatGrid::operator=(const SeatGrid& other) {
    if (this != &other) {
        deallocate();
        rows_ = other.rows_;
        cols_ = other.cols_;
        allocate(rows_, cols_);
        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                grid_[i][j] = other.grid_[i][j];
    }
    return *this;
}

SeatGrid::SeatGrid(SeatGrid&& other) noexcept : grid_(other.grid_), rows_(other.rows_), cols_(other.cols_) {
    other.grid_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
}

SeatGrid& SeatGrid::operator=(SeatGrid&& other) noexcept {
    if (this != &other) {
        deallocate();
        grid_ = other.grid_;
        rows_ = other.rows_;
        cols_ = other.cols_;
        other.grid_ = nullptr;
        other.rows_ = 0;
        other.cols_ = 0;
    }
    return *this;
}

void SeatGrid::allocate(int rows, int cols) {
    grid_ = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        grid_[i] = new char[cols];
        for (int j = 0; j < cols; ++j) grid_[i][j] = 'O';
    }
}

void SeatGrid::deallocate() {
    if (grid_) {
        for (int i = 0; i < rows_; ++i) delete[] grid_[i];
        delete[] grid_;
        grid_ = nullptr;
    }
}

bool SeatGrid::isValid(int r, int c) const {
    return r >= 0 && r < rows_ && c >= 0 && c < cols_;
}

bool SeatGrid::isAvailable(int r, int c) const {
    return isValid(r, c) && grid_[r][c] == 'O';
}

bool SeatGrid::book(int r, int c) {
    if (isAvailable(r, c)) {
        grid_[r][c] = 'X';
        return true;
    }
    return false;
}

bool SeatGrid::cancel(int r, int c) {
    if (isValid(r, c) && grid_[r][c] == 'X') {
        grid_[r][c] = 'O';
        return true;
    }
    return false;
}

void SeatGrid::display() const {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) std::cout << grid_[i][j] << " ";
        std::cout << "\n";
    }
}

int SeatGrid::availableCount() const {
    int count = 0;
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            if (grid_[i][j] == 'O') count++;
    return count;
}

int SeatGrid::rows() const { return rows_; }
int SeatGrid::cols() const { return cols_; }

std::string SeatGrid::serialize() const {
    std::string s;
    for (int i = 0; i < rows_; ++i) {
        if (i > 0) s += ";";
        s.append(grid_[i], cols_);
    }
    return s;
}

SeatGrid SeatGrid::deserialize(const std::string& s) {
    std::vector<std::string> rows;
    std::stringstream ss(s);
    std::string row;
    while (std::getline(ss, row, ';')) {
        rows.push_back(row);
    }
    if (rows.empty()) return SeatGrid(0, 0);
    
    int r = rows.size();
    int c = rows[0].length();
    SeatGrid grid(r, c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (j < rows[i].length()) {
                grid.grid_[i][j] = rows[i][j];
            }
        }
    }
    return grid;
}

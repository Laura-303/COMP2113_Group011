#ifndef SEATGRID_H
#define SEATGRID_H

#include <string>

class SeatGrid {
public:
    SeatGrid();
    SeatGrid(int rows, int cols);
    ~SeatGrid();

    SeatGrid(const SeatGrid& other);
    SeatGrid& operator=(const SeatGrid& other);
    SeatGrid(SeatGrid&& other) noexcept;
    SeatGrid& operator=(SeatGrid&& other) noexcept;

    bool isValid(int r, int c) const;
    bool isAvailable(int r, int c) const;
    bool book(int r, int c);
    bool cancel(int r, int c);

    void display() const;
    int availableCount() const;
    int rows() const;
    int cols() const;

    std::string serialize() const;
    static SeatGrid deserialize(const std::string& s);

private:
    char** grid_;
    int rows_;
    int cols_;

    void allocate(int rows, int cols);
    void deallocate();
};

#endif

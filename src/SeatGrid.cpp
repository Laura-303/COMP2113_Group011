#include "SeatGrid.h"
#include <iostream>
using namespace std;

char** createSeatGrid(int rows, int cols) {
    char** grid = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new char[cols];
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = 'O';
        }
    }
    return grid;
}

void displaySeatGrid(char** grid, int rows, int cols) {
    cout << "    ";
    for (int j = 0; j < cols; ++j) {
        cout.width(3);
        cout << (j + 1);
    }
    cout << endl << "   " << string(cols * 3 + 2, '-') << endl;

    for (int i = 0; i < rows; ++i) {
        char rowLabel = 'A' + i;
        cout << " " << rowLabel << " |";
        for (int j = 0; j < cols; ++j) {
            cout.width(3);
            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << "[O] Available   [X] Booked" << endl;
}

bool bookSeat(char** grid, int rows, int cols, char rowChar, int colNum) {
    int r = toupper(rowChar) - 'A';
    int c = colNum - 1;             

    if (grid[r][c] == 'X') {
        cout << "Sorry, seat " << (char)toupper(rowChar) << colNum << " is already booked." << endl;
        return false;
    }

    grid[r][c] = 'X';
    cout << "Success! Seat " << (char)toupper(rowChar) << colNum << " has been booked." << endl;
    return true;
}

void deleteSeatGrid(char** grid, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

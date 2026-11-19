#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "booking.h"
#include "movie.h"
#include "SeatGrid.h"
#include "showtime.h"
#include "display.h"
using namespace std;
struct Seat {
    char rolechar;
    int seatNumber;
};

struct Movie {
    string name;
    string time;
};

struct Customer {
    string name;
    string movieName;
    string time;
    int ticketNumber;
    Seat seat;
};

void movie();

void Booking(queue<Customer> &bookingQueue, const vector<Movie>& movies, vector<Seat>& StoredSeats) {
    bool booked = false;
    int seatSelected = 0;
    cout << "Please enter your name: ";
    cin >> bookingQueue.back().name;
    cout << "Please enter the movie name: ";
    cin >> bookingQueue.back().movieName;
    cout << "Please enter the show time: ";
    cin >> bookingQueue.back().time;
    cout << "Please enter your ticket number: ";
    cin >> bookingQueue.back().ticketNumber;
    if (!bookingQueue.empty()) {
        cout << "Booking for " << bookingQueue.front().name << " is being processed." << endl;
    }
    while (!booked) {
        for (int i = 0; i < movies.size(); ++i) {
            if (movies[i].name == bookingQueue.front().movieName && bookingQueue.front().time == movies[i].time) {
                movie();
                while (seatSelected < bookingQueue.front().ticketNumber) {
                    while (seatSelected < bookingQueue.front().ticketNumber) {
                        cout << "Please select your seat: " << endl;
                        cin >> bookingQueue.front().seat.rolechar >>bookingQueue.front().seat.seatNumber; 
                        if (bookingQueue.front().seat.rolechar < 'A' || bookingQueue.front().seat.rolechar > 'Z' || bookingQueue.front().seat.seatNumber < 1 || bookingQueue.front().seat.seatNumber > 10) {
                            cout << "Invalid seat selection. Please try again." << endl;
                        }
                        for (int k = 0; k < StoredSeats.size(); ++k) {
                            if (StoredSeats[k].rolechar == bookingQueue.front().seat.rolechar && StoredSeats[k].seatNumber == bookingQueue.front().seat.seatNumber) {
                                cout << "Seat already booked. Please select a different seat." << endl;
                                cin >> bookingQueue.front().seat.rolechar >> bookingQueue.front().seat.seatNumber;
                                return;
                            }
                            else {
                                cout << "Seat selected: " << bookingQueue.front().seat.rolechar << bookingQueue.front().seat.seatNumber << endl;
                                cout << "Confirm booking? (Y/N): ";
                                char confirm;
                                cin >> confirm;
                                if (confirm == 'Y' || confirm == 'y') {
                                    StoredSeats.push_back(bookingQueue.front().seat);
                                    cout << "Booking successful!" << endl;
                                    seatSelected++;
                                }
                                else {
                                    cout << "Booking cancelled. Please select a different seat." << endl;
                                    cin >> bookingQueue.front().seat.rolechar >> bookingQueue.front().seat.seatNumber;
                                }
                            }
                        }
                    }
                }
                cout << "All tickets booked successfully!" << endl;
                booked = true;
            }
            else {
                cout << "Movie not found. Please enter the movie name and time try again:" << endl;
                cin >> bookingQueue.back().movieName >> bookingQueue.back().time;
            }
        }
    }
    bookingQueue.pop();
    return;
}
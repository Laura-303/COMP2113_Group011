#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "booking.h"
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
    while (!booked) {
        for (int i = 0; i < movies.size(); ++i) {
            if (movies[i].name == bookingQueue.back().movieName && bookingQueue.back().time == movies[i].time) {
                MovieSeatSelection();
                while (seatSelected < bookingQueue.back().ticketNumber) {
                    for (int j = 0; j < bookingQueue.back().ticketNumber; ++k) {
                        cout << "Please select your seat: " << endl;
                        cin >> bookingQueue.back().seat.rolechar >>bookingQueue.back().seat.seatNumber; 
                        if (bookingQueue.back().seat.rolechar < 'A' || bookingQueue.back().seat.rolechar > 'Z' || bookingQueue.back().seat.seatNumber < 1 || bookingQueue.back().seat.seatNumber > 10) {
                            cout << "Invalid seat selection. Please try again." << endl;
                        }
                        for (int k = 0; k < StoredSeats.size(); ++k) {
                            if (StoredSeats[k].rolechar == bookingQueue.back().seat.rolechar && StoredSeats[k].seatNumber == bookingQueue.back().seat.seatNumber) {
                                cout << "Seat already booked. Please select a different seat." << endl;
                                cin >> bookingQueue.back().seat.rolechar >> bookingQueue.back().seat.seatNumber;
                                return;
                            }
                            else {
                                StoredSeats.push_back(bookingQueue.back().seat);
                                cout << "Booking successful!" << endl;
                                seatSelected++;
                            }
                        }
                    }
                }
                cout << "All tickets booked successfully!" << endl;
            }
            else {
                cout << "Movie not found. Please enter the movie name and time try again:" << endl;
                cin >> bookingQueue.back().movieName >> bookingQueue.back().time;
            }
        }
    }
}
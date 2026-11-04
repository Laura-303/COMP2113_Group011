# COMP2113 Group Project — Movie Ticket Booking System

## 1. Team
| Name | Student ID | GitHub username | Primary role |
|---|---|---|---|
| TBD | TBD | TBD | Integration / Build |
| TBD | TBD | TBD | Movies & Showtimes |
| TBD | TBD | TBD | SeatGrid / Non-syllabus feature |
| TBD | TBD | TBD | Bookings & Queue |
| TBD | TBD | TBD | UI / File I/O |
| TBD | TBD | TBD | QA / Testing / AI log |

## 2. Application Description and Core Functionality
Movie ticket booking system: browse movies and showtimes, view a dynamic
2D seat grid, select seats, enqueue bookings, process the booking queue,
and persist all state to text files across runs.

## 3. Mandatory Requirement Mapping
| Requirement | Where implemented |
|---|---|
| Non-syllabus C++ topic (RAII / Rule of Five / move semantics) | `include/SeatGrid.h`, `src/SeatGrid.cpp` |
| Data structures (`std::vector`, `std::queue`) | `src/BookingSystem.cpp` |
| Dynamic memory (`char**` seat grids) | `src/SeatGrid.cpp` |
| File I/O persistence | `src/BookingSystem.cpp` (`data/movies.txt`, `data/bookings.txt`) |
| Multi-file architecture | `include/` + `src/` + `main.cpp` |
| Modular menu system | `src/main.cpp`, `src/BookingSystem.cpp` |

## 4. Header-Only Libraries
None.

## 5. Compilation and Execution
    make
    ./main

Optional test script mode:

    ./main --script tests/case1_book_seats.txt

## 6. Video Demonstration
TBD

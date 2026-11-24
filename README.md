# COMP2113 Fall 2026 Group Project — Movie Ticket Booking System

## 1. Team
| Name | Student ID | GitHub username | Primary role |
|---|---|---|---|
| Laura | 3036406119 | Laura-303 | Integration lead (main.cpp, Makefile, BookingSystem) |
| Larina | [ID] | larina00 | Part A — Movie/Showtime model + display |
| Andy | 3036236136 | Cota2099 | Part A — movies.txt I/O + validation |
| Michael Li | 3036219657| MiChAeLi3290 | Part B — SeatGrid / RAII + LEARNING_MATERIALS |
| [Name] | [ID] | [username] | Part B — seat selection + serialization |
| Louis | [ID] | LT0831 | Part C — Booking model + queue logic |
| [Name] | [ID] | [username] | Part C — bookings.txt I/O + QA coordinator |

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

### 3.4 File I/O persistence Part A: `movies.txt` Architecture & Validation Design
### 3.4.1. File Schema (`data/movies.txt`)
To support movies, dynamic showtimes, and seat grids cleanly, we adopted a tagged-line structure:
- **Movie Entry**: `MOVIE|<MovieID>|<Title>|<DurationMin>|<Rating>`
- **Showtime Entry**: `SHOW|<ShowID>|<MovieID>|<Datetime>|<Hall>|<Price>|<Rows>|<Cols>`
- **Seat Status Entry**: `SEATS|<ShowID>|<SeatMatrix>` (e.g., `OOOOOOOO;XOOOXOOO;...`)
### 3.4.2. Robust Parsing & Validation Strategy (Fail-Fast Principle)
To prevent runtime crashes and memory corruption from malformed data files, Part A implements a strict validation pipeline before data is handed over to the booking system:
1. **Tag Identification**: Each line is first checked for a valid prefix (`MOVIE`, `SHOW`, `SEATS`).
2. **Delimiter Splitting**: Fields are tokenized securely using standard C++ string streams (`std::stringstream`).
3. **Whitespace Trimming**: Leading and trailing spaces around tokens are automatically stripped.
4. **Type & Character Validation**: 
   - Numerical fields (duration, price, rows, cols) are checked for invalid characters and out-of-range values.
   - Missing fields or structural mismatches trigger descriptive error messages during initialization.
### 3.4.3. Integration API
Part A provides a clean separation of concerns by encapsulating file I/O into structured data models and returning standard containers (e.g., `std::vector<Movie>`), allowing other modules to query data seamlessly without depending on raw file operations.

## 4. Header-Only Libraries
None.

## 5. Compilation and Execution
    make
    ./main

Optional test script mode:

    ./main --script tests/case1_book_seats.txt

## 6. Video Demonstration
TBD

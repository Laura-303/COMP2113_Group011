# Test Scripts

Run a case with:

    ./main --script tests/case1_book_seats.txt

## Command format
LIST
SHOW <movieId>
SEATS <showtimeId>
BOOK <showtimeId> <customer> <r,c;r,c>
PROCESS
STATUS <bookingId>
SAVE
EXIT

Expected output for case N lives in `tests/case<N>_expected.txt`.

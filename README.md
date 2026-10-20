# Campus Event & Help Desk System — DSA Mini Project

## Project overview
A menu-driven C++ program for viewing campus events, registering students, searching/cancelling registrations, sorting events, and handling help-desk requests.

## Data structures used
1. **Array (`std::array`)** — stores the fixed list of five campus events.
2. **Tuple (`std::tuple`)** — stores each event's ID, name, category, and fee.
3. **Singly linked list** — stores student registrations dynamically.
4. **Queue (`std::queue`)** — processes help-desk requests in FIFO order.
5. **Stack (`std::stack`)** — keeps registration IDs; the top gives the most recently created registration ID.

## Sorting algorithms
- **Bubble Sort** — sorts events by fee (ascending).
- **Insertion Sort** — sorts events alphabetically by name.
- **Selection Sort** — sorts events by event ID (ascending).

## Requirements
A C++ compiler with C++11 or later (for example, g++, MinGW, or the compiler in VS Code).

## Run on Windows (VS Code / MinGW)
1. Save `campus_event_dsa.cpp` in a folder.
2. Open that folder in VS Code.
3. Open Terminal → New Terminal.
4. Compile:
   ```bash
   g++ -std=c++11 campus_event_dsa.cpp -o campus_event_dsa
   ```
5. Run in PowerShell:
   ```powershell
   .\campus_event_dsa.exe
   ```
   Or in a terminal that uses Unix-style commands:
   ```bash
   ./campus_event_dsa
   ```

## Run on Linux / macOS
Open a terminal in the file's folder and run:
```bash
g++ -std=c++11 campus_event_dsa.cpp -o campus_event_dsa
./campus_event_dsa
```

## Suggested demonstration
1. Choose `1` to display events.
2. Choose `2`, enter `Rahul`, then event ID `101`.
3. Choose `2`, enter `Priya`, then event ID `103`.
4. Choose `3` to display registrations.
5. Choose `7`, `8`, and `9` to demonstrate all three sorting algorithms.
6. Choose `10` twice to add help requests, then `11` to show FIFO processing.
7. Choose `12` to view the most recent registration ID.
8. Choose `6` to count active registrations, then `0` to exit.

## Notes
- This is a console-based educational mini project; it does not store data after the program exits.
- For simple input, student names and help-desk requests are entered as one word.
- The stack records created registration IDs; cancelling a registration does not remove its ID from this history stack.

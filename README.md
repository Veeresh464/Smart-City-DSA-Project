# City Services Management System

This project is a comprehensive C-based system for managing city services, including **Railway Ticket Booking**, **Tourist Spot Information**, **Hospital Management**, and **Hotel Booking**. It demonstrates the use of data structures such as linked lists, hash tables, graphs, queues, and binary search trees.

## Features

### 1. Railway Ticket Booking
- Search trains by source and destination.
- Book tickets with seat availability check and waiting list management.
- Cancel booked tickets.
- View train details.

### 2. Tourist Spot Information
- View all tourist places.
- Find nearest tourist spots using Dijkstra's algorithm.
- Sort places by price or rating.
- Display detailed information about each spot.

### 3. Hospital Management
- Add, delete, search, and display hospitals using hash tables.
- Sort hospitals by rank.
- Find nearest hospitals and best routes using graph algorithms.
- Book and manage appointments using BST.
- View government and private hospitals.
- Check available beds.

### 4. Hotel Booking
- Add, delete, search, and display hotels using hash tables.
- Sort hotels by price or rating.
- Find nearest hotels using Dijkstra's algorithm.
- Book rooms and view hotel details.

## Data Structures Used

- **Linked Lists**: For train and ticket management.
- **Hash Tables**: For fast lookup of places, hospitals, and hotels.
- **Graphs**: For representing connections between places/hotels/hospitals.
- **Queues**: For BFS traversal and waiting list management.
- **Binary Search Trees**: For managing hospital appointments.

## How to Run

1. **Compile the code** using a C compiler (e.g., GCC).
2. **Prepare data files**:
    - `Trains.txt` (binary)
    - `touristPlaces.txt` (binary)
    - `file.txt` (binary for hotels)
    - `Places.txt`, `Hospital.txt`, `Hotel.txt` (text files for hash tables)
3. **Run the executable** and follow the menu-driven interface.

## File Structure

- `Test.c` : Main source code file.
- Data files: `Trains.txt`, `touristPlaces.txt`, `file.txt`, `Places.txt`, `Hospital.txt`, `Hotel.txt`.

## Usage

On running the program, you will be presented with a menu to choose between:
- Train booking
- Tourist spot information
- Hospital management
- Hotel booking

Each section provides further options for searching, booking, sorting, and managing records.

## Contributors

- Veeresh
- Manoj
- Rahul

## License

This project is for educational purposes.

# Online Movie Booking System (C++)

A beginner-friendly, menu-driven console application written in standard C++.

## Features
- Display available movies, show timings, ticket prices and seat availability
- Book one or more seats
- Prevent booking a seat that is already reserved
- Generate a booking ID and display a booking confirmation
- View bookings during the current program run
- Cancel a booking and release its seats

## Requirements
- C++ compiler that supports C++11 or later (C++17 recommended)
- Examples: GCC/G++, MinGW-w64, or a compatible IDE

## How to compile and run

### Windows (MinGW g++)
Open Command Prompt or the VS Code terminal in this folder:

```bash
g++ -std=c++17 -Wall -Wextra -o movie_booking main.cpp
movie_booking.exe
```

### Linux / macOS
```bash
g++ -std=c++17 -Wall -Wextra -o movie_booking main.cpp
./movie_booking
```

## How to use
1. Run the program.
2. Select **1** to view sample movies and shows.
3. Select **2** to book tickets, enter a show ID, customer name and seat numbers.
4. Select **3** to view bookings.
5. Select **4** to cancel a booking using its booking ID.
6. Select **5** to exit.

## Project structure
```text
Online_Movie_Booking_System/
├── main.cpp
├── README.md
└── .gitignore
```

## Important note
This is an educational console-based project. Bookings are stored in memory, so they are cleared when the program closes. It does not connect to a real cinema, payment gateway, database, or website. Do not enter real payment details.

## Concepts demonstrated
- Classes and objects
- Encapsulation
- Vectors and strings
- Loops and conditional statements
- Functions and constructors
- Input validation
- Basic booking and cancellation logic

## Possible future improvements
- Save bookings permanently using files or a database
- Add user registration and login
- Add movie search and date selection
- Add a graphical or web-based user interface
- Integrate a secure payment provider in a production system

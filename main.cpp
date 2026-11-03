#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;

class Show {
public:
    int showId;
    string movieName;
    string time;
    double ticketPrice;
    int totalSeats;
    vector<bool> bookedSeats;

    Show(int id, const string& movie, const string& showTime,
         double price, int seats)
        : showId(id), movieName(movie), time(showTime),
          ticketPrice(price), totalSeats(seats),
          bookedSeats(seats, false) {}

    int availableSeats() const {
        int available = 0;
        for (bool booked : bookedSeats) {
            if (!booked) available++;
        }
        return available;
    }

    void displaySeats() const {
        cout << "\nSeat layout (O = available, X = booked)\n";
        for (int i = 0; i < totalSeats; i++) {
            cout << setw(3) << (bookedSeats[i] ? "X" : "O");
            if ((i + 1) % 5 == 0) cout << '\n';
        }
        if (totalSeats % 5 != 0) cout << '\n';
        cout << "Seat numbers: 1 to " << totalSeats << "\n";
    }
};

class Booking {
public:
    int bookingId;
    string customerName;
    int showId;
    vector<int> seatNumbers;
    double totalAmount;

    Booking(int id, const string& name, int selectedShow,
            const vector<int>& seats, double amount)
        : bookingId(id), customerName(name), showId(selectedShow),
          seatNumbers(seats), totalAmount(amount) {}
};

class MovieBookingSystem {
private:
    vector<Show> shows;
    vector<Booking> bookings;
    int nextBookingId = 1001;

    int readInt(const string& prompt, int minValue, int maxValue) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value && value >= minValue && value <= maxValue) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            cout << "Invalid input. Enter a number from "
                 << minValue << " to " << maxValue << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void displayShows() const {
        cout << "\n========== AVAILABLE MOVIES ==========\n";
        cout << left << setw(8) << "Show ID"
             << setw(25) << "Movie"
             << setw(15) << "Show Time"
             << setw(12) << "Price"
             << "Available\n";
        cout << string(72, '-') << '\n';

        for (const Show& show : shows) {
            cout << left << setw(8) << show.showId
                 << setw(25) << show.movieName
                 << setw(15) << show.time
                 << "Rs. " << setw(7) << fixed << setprecision(2)
                 << show.ticketPrice
                 << show.availableSeats() << "/" << show.totalSeats << '\n';
        }
    }

    Show* findShow(int id) {
        for (Show& show : shows) {
            if (show.showId == id) return &show;
        }
        return nullptr;
    }

    void bookTickets() {
        displayShows();
        int id = readInt("\nEnter Show ID: ", 1, 9999);
        Show* show = findShow(id);

        if (show == nullptr) {
            cout << "Show not found.\n";
            return;
        }

        if (show->availableSeats() == 0) {
            cout << "Sorry, this show is sold out.\n";
            return;
        }

        string customerName;
        cout << "Enter customer name: ";
        getline(cin, customerName);

        if (customerName.empty()) {
            cout << "Name cannot be empty. Booking cancelled.\n";
            return;
        }

        show->displaySeats();
        int count = readInt("How many tickets do you want? ",
                            1, show->availableSeats());

        vector<int> selectedSeats;
        for (int i = 0; i < count; i++) {
            while (true) {
                int seat = readInt("Enter seat number: ", 1, show->totalSeats);
                int index = seat - 1;

                bool alreadySelected = false;
                for (int selected : selectedSeats) {
                    if (selected == seat) alreadySelected = true;
                }

                if (show->bookedSeats[index]) {
                    cout << "That seat is already booked. Choose another.\n";
                } else if (alreadySelected) {
                    cout << "You have already selected that seat.\n";
                } else {
                    selectedSeats.push_back(seat);
                    break;
                }
            }
        }

        double amount = count * show->ticketPrice;
        for (int seat : selectedSeats) {
            show->bookedSeats[seat - 1] = true;
        }

        int bookingId = nextBookingId++;
        bookings.emplace_back(bookingId, customerName, id,
                              selectedSeats, amount);

        cout << "\n========== BOOKING CONFIRMED ==========\n";
        cout << "Booking ID : " << bookingId << '\n';
        cout << "Customer   : " << customerName << '\n';
        cout << "Movie      : " << show->movieName << '\n';
        cout << "Show time  : " << show->time << '\n';
        cout << "Seats      : ";
        for (size_t i = 0; i < selectedSeats.size(); i++) {
            cout << selectedSeats[i];
            if (i + 1 < selectedSeats.size()) cout << ", ";
        }
        cout << "\nTickets    : " << count
             << "\nTotal      : Rs. " << fixed << setprecision(2)
             << amount << '\n';
        cout << "Please save your Booking ID.\n";
    }

    void viewBookings() const {
        cout << "\n========== BOOKING DETAILS ==========\n";
        if (bookings.empty()) {
            cout << "No bookings have been made yet.\n";
            return;
        }

        for (const Booking& booking : bookings) {
            cout << "\nBooking ID : " << booking.bookingId
                 << "\nCustomer   : " << booking.customerName
                 << "\nShow ID    : " << booking.showId
                 << "\nSeats      : ";
            for (int seat : booking.seatNumbers) cout << seat << " ";
            cout << "\nAmount     : Rs. " << fixed << setprecision(2)
                 << booking.totalAmount << '\n';
        }
    }

    void cancelBooking() {
        if (bookings.empty()) {
            cout << "There are no bookings to cancel.\n";
            return;
        }

        int id = readInt("Enter Booking ID to cancel: ", 1, 999999);
        for (auto it = bookings.begin(); it != bookings.end(); ++it) {
            if (it->bookingId == id) {
                Show* show = findShow(it->showId);
                if (show != nullptr) {
                    for (int seat : it->seatNumbers) {
                        show->bookedSeats[seat - 1] = false;
                    }
                }
                bookings.erase(it);
                cout << "Booking cancelled successfully.\n";
                return;
            }
        }
        cout << "Booking ID not found.\n";
    }

public:
    MovieBookingSystem() {
        // Sample data. You can change movie names, timings, prices and seats.
        shows.emplace_back(1, "The Space Journey", "10:00 AM", 180.00, 20);
        shows.emplace_back(2, "Mystery of Night", "02:00 PM", 220.00, 20);
        shows.emplace_back(3, "The Final Mission", "06:30 PM", 250.00, 20);
    }

    void run() {
        int choice;
        do {
            cout << "\n======================================\n";
            cout << "       ONLINE MOVIE BOOKING SYSTEM\n";
            cout << "======================================\n";
            cout << "1. View Movies and Shows\n";
            cout << "2. Book Tickets\n";
            cout << "3. View All Bookings\n";
            cout << "4. Cancel Booking\n";
            cout << "5. Exit\n";

            choice = readInt("Enter your choice: ", 1, 5);

            switch (choice) {
                case 1:
                    displayShows();
                    break;
                case 2:
                    bookTickets();
                    break;
                case 3:
                    viewBookings();
                    break;
                case 4:
                    cancelBooking();
                    break;
                case 5:
                    cout << "Thank you for using the Movie Booking System!\n";
                    break;
            }
        } while (choice != 5);
    }
};

int main() {
    MovieBookingSystem system;
    system.run();
    return 0;
}

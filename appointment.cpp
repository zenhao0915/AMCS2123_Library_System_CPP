#include "data.h"

void appointmentManagement(vector<Book> &books, const vector<User> &users, vector<RoomBooking> &roomBookings, User *currentUser) {
    while (true) {
        cout << "\n--- Appointment Management Sub-Menu ---" << endl;
        cout << "1. Reserve an Out-of-Stock Book" << endl;
        cout << "2. Book a Study Room" << endl;
        cout << "3. Cancel a Room Booking" << endl;
        cout << "4. View All Active Room Bookings" << endl;
        cout << "5. Return to Main Menu" << endl;
        cout << "Enter choice (1-5): ";

        int choice;
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[ERROR] Invalid choice! Try again." << endl;
            continue;
        }

        if (choice == 5) break;

        if (choice == 1) {
            cout << "\n[Reserve an Out-of-Stock Book]" << endl;
            cout << "Enter Book ID to reserve: ";
            string bID;
            cin >> bID;
            cin.ignore(10000, '\n');

            int bookIndex = -1;
            for (int i = 0; i < books.size(); i++) {
                if (books[i].bookID == bID) {
                    bookIndex = i;
                    break;
                }
            }

            if (bookIndex == -1) {
                cout << "[ERROR] Book ID not found!" << endl;
                continue;
            }

            if (books[bookIndex].stock > 0) {
                cout << "[ERROR] Book is currently in stock. Please use the Borrow module instead." << endl;
                continue;
            }

            if (books[bookIndex].isReserved) {
                cout << "[ERROR] Book is already reserved by another member!" << endl;
                continue;
            }

            books[bookIndex].isReserved = true;
            cout << "[SUCCESS] Book reserved successfully!" << endl;
        }
        else if (choice == 2) {
            cout << "\n[Book a Study Room]" << endl;
            RoomBooking newBooking;
            newBooking.userID = currentUser->userID;

            cout << "Enter Room ID (e.g., R01, R02): ";
            cin >> newBooking.roomID;
            cin.ignore(10000, '\n');

            cout << "Enter Date (DD-MM-YYYY): ";
            cin >> newBooking.date;
            cin.ignore(10000, '\n');

            while (true) {
                cout << "Select Time Slot (1: Morning, 2: Afternoon, 3: Evening): ";
                cin >> newBooking.timeSlot;
                if (cin.fail() || newBooking.timeSlot < 1 || newBooking.timeSlot > 3) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[ERROR] Invalid slot selection!" << endl;
                } else {
                    break;
                }
            }

            bool conflict = false;
            for (const auto &rb : roomBookings) {
                if (rb.roomID == newBooking.roomID && rb.date == newBooking.date && rb.timeSlot == newBooking.timeSlot) {
                    conflict = true;
                    break;
                }
            }

            if (conflict) {
                cout << "[ERROR] Room is already booked for this date and time slot!" << endl;
                continue;
            }

            roomBookings.push_back(newBooking);
            cout << "[SUCCESS] Study room booked successfully!" << endl;
        }
        else if (choice == 3) {
            cout << "\n[Cancel a Room Booking]" << endl;
            cout << "Enter User ID: ";
            string uID;
            cin >> uID;

            cout << "Enter Room ID: ";
            string rID;
            cin >> rID;

            cout << "Enter Date (DD-MM-YYYY): ";
            string bDate;
            cin >> bDate;

            int targetIndex = -1;
            for (int i = 0; i < roomBookings.size(); i++) {
                if (roomBookings[i].userID == uID && roomBookings[i].roomID == rID && roomBookings[i].date == bDate) {
                    targetIndex = i;
                    break;
                }
            }

            if (targetIndex == -1) {
                cout << "[ERROR] No matching room booking found!" << endl;
                continue;
            }

            roomBookings.erase(roomBookings.begin() + targetIndex);
            cout << "[SUCCESS] Room booking canceled successfully!" << endl;
        }
        else if (choice == 4) {
            cout << "\n[Active Room Bookings]" << endl;
            if (roomBookings.empty()) {
                cout << "No active room bookings found." << endl;
                continue;
            }
            cout << "--------------------------------------------------------" << endl;
            for (const auto &rb : roomBookings) {
                string slotName = (rb.timeSlot == 1) ? "Morning" : (rb.timeSlot == 2) ? "Afternoon" : "Evening";
                cout << "User: " << rb.userID << " | Room: " << rb.roomID
                     << " | Date: " << rb.date << " | Slot: " << slotName << endl;
            }
            cout << "--------------------------------------------------------" << endl;
        }
    }
}
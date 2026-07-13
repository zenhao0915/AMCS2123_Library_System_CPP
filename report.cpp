#include "data.h"

void reportingStatistics(vector<Book> &books, vector<User> &users, vector<RoomBooking> &roomBookings,
                         vector<Transaction> &transactions) {
    while (true) {
        cout << "\n--- Reporting and Statistics Sub-Menu ---" << endl;
        cout << "1. Books Inventory Report" << endl;
        cout << "2. User Membership Report" << endl;
        cout << "3. Financial Statistics Report" << endl;
        cout << "4. Room Booking Summary Report" << endl;
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
            int totalTitles = size(books);
            int totalStock = 0;
            int outOfStockCount = 0;

            for (const auto &b: books) {
                totalStock += b.stock;
                if (b.stock == 0) {
                    outOfStockCount++;
                }
            }

            cout << "\n========================================" << endl;
            cout << "        BOOKS INVENTORY REPORT          " << endl;
            cout << "========================================" << endl;
            cout << left << setw(30) << "Total Unique Book Titles:" << totalTitles << endl;
            cout << left << setw(30) << "Total Physical Copies:" << totalStock << endl;
            cout << left << setw(30) << "Out of Stock Titles:" << outOfStockCount << endl;
            cout << "========================================" << endl;
        } else if (choice == 2) {
            int totalUsers = size(users);
            int adminCount = 0;
            int activeBorrowers = 0;

            for (const auto &u: users) {
                if (u.isAdmin) adminCount++;
                if (u.borrowedCount > 0) activeBorrowers++;
            }

            cout << "\n========================================" << endl;
            cout << "         USER MEMBERSHIP REPORT         " << endl;
            cout << "========================================" << endl;
            cout << left << setw(30) << "Total Registered Members:" << totalUsers << endl;
            cout << left << setw(30) << "Administrator Accounts:" << adminCount << endl;
            cout << left << setw(30) << "Standard Member Accounts:" << (totalUsers - adminCount) << endl;
            cout << left << setw(30) << "Members with Active Borrows:" << activeBorrowers << endl;
            cout << "========================================" << endl;
        } else if (choice == 3) {
            double totalCollected = 0.0;
            double totalOutstanding = 0.0;
            int settledCount = 0;
            int unsettledCount = 0;

            for (const auto &tx: transactions) {
                if (tx.isSettled) {
                    totalCollected += tx.paidAmount;
                    settledCount++;
                } else {
                    totalOutstanding += (tx.fineAmount - tx.paidAmount);
                    unsettledCount++;
                }
            }

            cout << "\n========================================" << endl;
            cout << "       FINANCIAL STATISTICS REPORT      " << endl;
            cout << "========================================" << endl;
            cout << left << setw(30) << "Total Fines Collected:" << "RM " << fixed << setprecision(2) << totalCollected
                    << endl;
            cout << left << setw(30) << "Total Fines Outstanding:" << "RM " << fixed << setprecision(2) <<
                    totalOutstanding << endl;
            cout << left << setw(30) << "Settled Invoices:" << settledCount << endl;
            cout << left << setw(30) << "Unsettled Invoices:" << unsettledCount << endl;
            cout << "========================================" << endl;
        } else if (choice == 4) {
            const int totalBookings = size(roomBookings);
            int morningSlots = 0;
            int afternoonSlots = 0;
            int eveningSlots = 0;

            for (const auto &rb: roomBookings) {
                if (rb.timeSlot == 1) morningSlots++;
                else if (rb.timeSlot == 2) afternoonSlots++;
                else if (rb.timeSlot == 3) eveningSlots++;
            }
            string roomSpecs[3][3] = {
                {"Slot 1", "Morning Session",   "08:00 AM - 12:00 PM"},
                {"Slot 2", "Afternoon Session", "01:00 PM - 05:00 PM"},
                {"Slot 3", "Evening Session",   "06:00 PM - 10:00 PM"}
            };

            cout << "\n========================================" << endl;
            cout << "        ROOM BOOKING SUMMARY REPORT     " << endl;
            cout << "========================================" << endl;

            cout << "--- Library Room Operating Rules ---" << endl;
            cout << left << setw(10) << "ID" << setw(20) << "Session Name" << "Hours" << endl;
            for (int i = 0; i < 3; i++) {
                cout << left << setw(10) << roomSpecs[i][0]
                     << setw(20) << roomSpecs[i][1]
                     << roomSpecs[i][2] << endl;
            }
            cout << "----------------------------------------" << endl;

            cout << left << setw(30) << "Total Active Bookings:" << totalBookings << endl;
            cout << left << setw(30) << "Morning Slot Bookings:" << morningSlots << endl;
            cout << left << setw(30) << "Afternoon Slot Bookings:" << afternoonSlots << endl;
            cout << left << setw(30) << "Evening Slot Bookings:" << eveningSlots << endl;
            cout << "========================================" << endl;
        }
    }
}

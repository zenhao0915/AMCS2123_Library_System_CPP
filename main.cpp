#include "data.h"

string modules[] = {
    "Member Management",
    "Service Registration/Booking",
    "Appointment Management",
    "Billing",
    "Reporting and Statistics",
    "(Extra) Top 5 Hot Topics Book",
    "(Extra) Blacklist System",
    "Exit"
};

void printMenu() {
    cout << "\n\tMenu" << endl;
    for (int i = 0; i < 22; i++) cout << "=";
    cout << endl;
    for (int i = 0; i < size(modules); i++) {
        cout << i + 1 << ". " << modules[i] << endl;
    }
    cout << endl << "Enter Current Navigation(1-8): ";
}

int main() {
    int currentSelection;
    vector<User> users;
    vector<Book> books;
    vector<RoomBooking> roomBookings;
    vector<Transaction> transactions;

    loadUsers(users);
    loadBooks(books);

    while (true) {
        printMenu();
        cin >> currentSelection;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a valid number." << endl;
            continue;
        }
        if (currentSelection < 1 || currentSelection > size(modules)) {
            cout << "\nChoice out of range! Please enter a number between 1 and " << size(modules) << "." << endl;
            continue;
        }

        if (currentSelection == size(modules)) {
            saveUsers(users);
            saveBooks(books);
            break;
        }

        switch (currentSelection) {
            case 1:
                memberManagement(users);
                break;
            case 2:
                serviceRegistration(books, users);
                break;
            case 3:
                appointmentManagement(books, users, roomBookings);
                break;
            case 4:
                billingPayment(users, transactions);
                break;
            case 5:
                reportingStatistics(books, users, roomBookings, transactions);
                break;
            case 6:
                extraHotBooks(books);
                break;
            case 7:
                extraBlacklist(users, transactions);
                break;
            default: {
                break;
            }
        }
    }
    cout << "\nThank you for using Library Management System. Program End!" << endl;
    return 0;
}

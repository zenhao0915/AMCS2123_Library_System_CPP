#include "data.h"

string modules[] = {
    "Member Management",
    "Booking/Books View",
    "Appointment Management",
    "Billing",
    "Reporting and Statistics",
    "(Extra) Top 5 Hot Topics Book",
    "(Extra) Blacklist System",
    "Logout",
    "Exit"
};

void printMenu(const Session& session) {
    cout << "\n\tMenu" << endl;
    for (int i = 0; i < 22; i++) cout << "=";
    cout << endl;
    if (session.hasUserLoggedIn()) {
        for (int i = 0; i < size(modules); i++) {
            if (i + 1 == size(modules)) {
                cout << "0. " << modules[i] << endl;
                break;
            }
            cout << i + 1 << ". " << modules[i] << endl;
        }
        cout << endl << "Enter Current Navigation(0-8): ";
    } else {
        cout << "1. Register User" << endl;
        cout << "2. Login User" << endl;
        cout << "0. Exit" << endl;
        cout << endl << "Enter Current Navigation(0-2): ";
    }
}

int main() {
    int currentSelection;
    vector<User> users;
    vector<Book> books;
    vector<RoomBooking> roomBookings;
    vector<Transaction> transactions;
    Session session;

    loadUsers(users);
    loadBooks(books);

    while (true) {
        printMenu(session);
        cin >> currentSelection;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a valid number." << endl;
            continue;
        }
        int selectionRange;
        if (session.hasUserLoggedIn()) {
            selectionRange = size(modules);
        } else {
            selectionRange = 2;
        }
        if (currentSelection < 0 || currentSelection > selectionRange) {
            cout << "\nChoice out of range! Please enter a number between 1 and " << selectionRange << "." << endl;
            continue;
        }

        if (currentSelection == 0) {
            saveUsers(users, nullptr);
            saveBooks(books);
            break;
        }
        if (!session.hasUserLoggedIn()) {
            switch (currentSelection) {
                case 1: {
                    // Register
                    string userID;
                    string userName;
                    string userPassword;
                    cin.ignore(10000, '\n');
                    cout << "[REGISTER] Enter UserID: ";
                    getline(cin, userID);
                    cout << "[REGISTER] Enter UserName: ";
                    getline(cin, userName);
                    cout << "[REGISTER] Enter Password: ";
                    getline(cin, userPassword);
                    session.registerUser(users, userID, userName, userPassword);
                    break;
                }
                case 2: {
                    // Login
                    string userID;
                    string userPassword;
                    cin.ignore(10000, '\n');
                    cout << "[LOGIN] Enter UserID: ";
                    getline(cin, userID);
                    if (!Session::isUserExists(users, userID)) {
                        cout << "[ERROR] User " << userID << " does not exist." << endl;
                        break;
                    }
                    cout << "[LOGIN] Enter Password: ";
                    getline(cin, userPassword);
                    session.loginToUser(users, userID, userPassword);
                    break;
                }
                default: break;
            }
            continue;
        }
        User *currentUser = session.getCurrentUser();
        if (currentUser == nullptr) continue;
        switch (currentSelection) {
            case 1:
                memberManagement(users, currentUser);
                break;
            case 2:
                bookingService(books, users, currentUser);
                break;
            case 3:
                appointmentManagement(books, users, roomBookings, currentUser);
                break;
            case 4:
                billingPayment(users, transactions, currentUser);
                break;
            case 5:
                reportingStatistics(books, users, roomBookings, transactions, currentUser);
                break;
            case 6:
                extraHotBooks(books);
                break;
            case 7:
                extraBlacklist(users, transactions, currentUser);
                break;
            case 8: {
                session.logoutUser();
                break;
            }
            default: break;
        }
    }
    cout << "\nThank you for using Library Management System. Program End!" << endl;
    return 0;
}

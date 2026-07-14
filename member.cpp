#include "data.h"

void memberManagement(vector<User> &users, User *user) {
    while (true) {
        cout << "\n=== Member Management Sub-Menu ===" << endl;
        cout << "1. View Member Details" << endl;
        cout << "2. Update Member Profile" << endl;
        cout << "3. Return to Main Menu" << endl;
        cout << "Enter choice (1-3): ";

        int subChoice;
        cin >> subChoice;
        if (cin.fail() || subChoice < 1 || subChoice > 3) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[ERROR] Invalid choice! Try again." << endl;
            continue;
        }
        if (subChoice == 3) break;

        switch (subChoice) {
            case 1: {
                cout << "\n[View Member Details]" << endl;
                cout << "Enter User ID to search: ";
                string searchID;
                cin >> searchID;

                bool found = false;
                for (const auto &user: users) {
                    if (user.userID == searchID) {
                        cout << "\n-----------------------------------" << endl;
                        cout << "User ID        : " << user.userID << endl;
                        cout << "Name           : " << user.userName << endl;
                        cout << "Role           : " << (user.isAdmin ? "Admin" : "Standard Member") << endl;
                        cout << "BlackList      : " << (user.isBlacklisted ? "True" : "False") << endl;
                        cout << "Borrowed Books : " << user.borrowedCount << " items" << endl;
                        cout << "-----------------------------------" << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "[ERROR] Member not found!" << endl;
                break;
            }
            case 2: {
                cout << "\n[Update Member Profile]" << endl;
                cout << "Enter User ID to update: ";
                string searchID;
                cin >> searchID;

                string newName;
                while (true) {
                    cout << "Enter New Name (Current: " << user->userName << "): ";
                    getline(cin, newName);
                    if (!isValidName(newName)) {
                        cout << "[ERROR] Invalid name! Name cannot contain digits." << endl;
                    } else {
                        user->userName = newName;
                        saveUsers(users);
                        break;
                    }
                }
                cout << "[SUCCESS] Profile updated successfully!" << endl;
                break;
            }
            default: break;
        }
    }
}

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
                clearInputBuffer();
                bool found = false;
                for (const auto &u: users) {
                    if (u.userID == searchID) {
                        cout << "\n-----------------------------------" << endl;
                        cout << "User ID        : " << u.userID << endl;
                        cout << "Name           : " << u.userName << endl;
                        cout << "Role           : " << (u.isAdmin ? "Admin" : "Standard Member") << endl;
                        cout << "BlackList      : " << (u.isBlacklisted ? "True" : "False") << endl;
                        cout << "Borrowed Books : " << u.borrowedCount << " items" << endl;
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
                string newName, idToSearch;
                bool found = true;
                User *tempUser = nullptr;

                while (true) {
                    clearInputBuffer();
                    if (user->isAdmin) {
                        cout << "Search Member ID: ";
                        getline(cin, idToSearch);
                        if (Session::getUserByID(users, idToSearch) == nullptr) {
                            cout << "Member ID (" << idToSearch << ") not found!" << endl;
                            found = false;
                            break;
                        }
                        tempUser = Session::getUserByID(users, idToSearch);
                        cout << "Enter New Name (Current: " << tempUser->userName <<
                                "): ";
                    } else {
                        cout << "Enter New Name (Current: " << user->userName << "): ";
                    }
                    getline(cin, newName);
                    if (!Session::isValidName(newName)) {
                        cout << "[ERROR] Invalid name! Name cannot contain digits." << endl;
                    } else {
                        if (tempUser != nullptr) {
                            tempUser->userName = newName;
                        } else {
                            user->userName = newName;
                        }
                        saveUsers(users, user);
                        break;
                    }
                }
                if (!found) break;
                cout << "[SUCCESS] Profile updated successfully!" << endl;
                break;
            }
            default: break;
        }
    }
}

#include "data.h"

bool isValidName(const string &name) {
    if (name.empty()) return false;
    for (const char c: name) {
        if (isdigit(c)) return false;
    }
    return true;
}

bool isUserIdDuplicate(const string &id, const vector<User> &users) {
    for (const auto &user: users) {
        if (user.userID == id) return true;
    }
    return false;
}

void memberManagement(vector<User> &users) {
    while (true) {
        cout << "\n=== Member Management Sub-Menu ===" << endl;
        cout << "1. Register New Member\n2. View Member Details\n3. Update Member Profile\n4. Return to Main Menu" <<
                endl;
        cout << "Enter choice (1-4): ";

        int subChoice;
        cin >> subChoice;
        if (cin.fail() || subChoice < 1 || subChoice > 4) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[ERROR] Invalid choice! Try again." << endl;
            continue;
        }
        if (subChoice == 4) break;

        switch (subChoice) {
            case 1: {
                User newUser;
                cout << "\n[Register New Member]" << endl;

                while (true) {
                    cout << "Enter User ID: ";
                    cin >> newUser.userID;
                    if (isUserIdDuplicate(newUser.userID, users)) {
                        cout << "[ERROR] User ID already exists! Please use a unique ID." << endl;
                    } else {
                        break;
                    }
                }

                cin.ignore(10000, '\n');
                while (true) {
                    cout << "Enter User Name: ";
                    getline(cin, newUser.userName);
                    if (!isValidName(newUser.userName)) {
                        cout << "[ERROR] Invalid name! Name cannot contain digits." << endl;
                    } else {
                        break;
                    }
                }

                char adminChar;
                cout << "Is this user an Admin? (Y/N): ";
                cin >> adminChar;
                newUser.isAdmin = (adminChar == 'Y' || adminChar == 'y');

                newUser.borrowedCount = 0;
                newUser.isBlacklisted = false;

                users.push_back(newUser);
                cout << "[SUCCESS] Member registered successfully!" << endl;
                break;
            }
            case 2: {
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
            case 3: {
                cout << "\n[Update Member Profile]" << endl;
                cout << "Enter User ID to update: ";
                string searchID;
                cin >> searchID;

                bool found = false;
                for (auto &user: users) {
                    if (user.userID == searchID) {
                        found = true;
                        cin.ignore(10000, '\n');

                        string newName;
                        while (true) {
                            cout << "Enter New Name (Current: " << user.userName << "): ";
                            getline(cin, newName);
                            if (!isValidName(newName)) {
                                cout << "[ERROR] Invalid name! Name cannot contain digits." << endl;
                            } else {
                                user.userName = newName;
                                break;
                            }
                        }

                        char adminChar;
                        cout << "Change Admin status? (Y/N): ";
                        cin >> adminChar;
                        user.isAdmin = (adminChar == 'Y' || adminChar == 'y');

                        cout << "[SUCCESS] Profile updated successfully!" << endl;
                        break;
                    }
                }
                if (!found) cout << "[ERROR] Member not found!" << endl;
                break;
            }
            default: break;
        }
    }
}

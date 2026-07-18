#include "data.h"


void extraBlacklist(vector<User> &users, const vector<Transaction> &transactions, User *currentUser) {
    if (currentUser->hasPermission()) return;
    while (true) {
        cout << "\n--- Blacklist System Sub-Menu ---" << endl;
        cout << "1. Manually Blacklist a Member" << endl;
        cout << "2. Remove Member from Blacklist" << endl;
        cout << "3. View Blacklisted Members" << endl;
        cout << "4. Return to Main Menu" << endl;
        cout << "Enter choice (1-4): ";

        int choice;
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[ERROR] Invalid choice! Try again." << endl;
            continue;
        }

        if (choice == 4) break;

        if (choice == 1) {
            cout << "\n[Manual Blacklist]" << endl;
            cout << "Enter User ID: ";
            string uID;
            cin >> uID;

            int userIndex = -1;
            for (int i = 0; i < users.size(); i++) {
                if (users[i].userID == uID) {
                    userIndex = i;
                    break;
                }
            }

            if (userIndex == -1) {
                cout << "[ERROR] User ID not found!" << endl;
                continue;
            }

            if (users[userIndex].isBlacklisted) {
                cout << "[WARNING] Member is already blacklisted." << endl;
            } else {
                users[userIndex].isBlacklisted = true;
                cout << "[SUCCESS] Member " << users[userIndex].userName << " has been blacklisted." << endl;
            }
        }
        else if (choice == 2) {
            cout << "\n[Remove from Blacklist]" << endl;
            cout << "Enter User ID: ";
            string uID;
            cin >> uID;

            int userIndex = -1;
            for (int i = 0; i < users.size(); i++) {
                if (users[i].userID == uID) {
                    userIndex = i;
                    break;
                }
            }

            if (userIndex == -1) {
                cout << "[ERROR] User ID not found!" << endl;
                continue;
            }

            if (!users[userIndex].isBlacklisted) {
                cout << "[WARNING] Member is not blacklisted." << endl;
            } else {
                users[userIndex].isBlacklisted = false;
                cout << "[SUCCESS] Member " << users[userIndex].userName << " has been reinstated." << endl;
            }
        }
        else if (choice == 3) {
            cout << "\n========================================" << endl;
            cout << "        BLACKLISTED MEMBERS LIST        " << endl;
            cout << "========================================" << endl;

            bool empty = true;
            cout << left << setw(12) << "User ID" << "Name" << endl;
            cout << "----------------------------------------" << endl;

            for (const auto &u : users) {
                if (u.isBlacklisted) {
                    cout << left << setw(12) << u.userID << u.userName << endl;
                    empty = false;
                }
            }
            if (empty) {
                cout << "No blacklisted members found." << endl;
            }
            cout << "========================================" << endl;
        }
    }
}
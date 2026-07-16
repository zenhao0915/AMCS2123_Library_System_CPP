#pragma once
#include <iostream>
#include<iomanip>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <functional>
#include <cassert>

using namespace std;

struct Book {
    string bookID;
    string name;
    string author;
    int stock;
    int borrowCount;
    bool isReserved;
};

struct User {
    string userID;
    string userName;
    size_t passwordHash = 1;
    bool isAdmin = false;
    mutable int borrowedCount = 0;
    bool isBlacklisted = false;
    vector<string> booksBorrowed;

    User() = default;

    User(string id, string name, size_t pwdHash)
        : userID(std::move(id)), userName(std::move(name)), passwordHash(pwdHash) {
    }

    void borrowBook(const Book &book) {
        booksBorrowed.push_back(book.name);
        borrowedCount++;
    }

    bool hasPermission() const {
        if (!isAdmin) {
            cout << "[ERROR] User Has No Permisssion To Access!" << endl;
            return false;
        }
        return true;
    }
};

struct RoomBooking {
    string roomID;
    string userID;
    string date;
    int timeSlot;
};

struct Transaction {
    string txID;
    string userID;
    double fineAmount;
    double paidAmount;
    bool isSettled;
};

void memberManagement(vector<User> &users, User *user);

void bookingService(vector<Book> &books, vector<User> &users, User *currentUser);

void appointmentManagement(vector<Book> &books, const vector<User> &users, vector<RoomBooking> &roomBookings, User *currentUser);

void billingPayment(vector<User> &users, vector<Transaction> &transactions);

void reportingStatistics(vector<Book> &books, vector<User> &users, vector<RoomBooking> &roomBookings,
                         vector<Transaction> &transactions);

void extraHotBooks(vector<Book> &books);

void extraBlacklist(vector<User> &users, const vector<Transaction> &transactions);

void saveBooks(const vector<Book> &books);

void loadBooks(vector<Book> &books);

void saveUsers(vector<User> &users, const User *currentUser);

void loadUsers(vector<User> &users);

inline void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

class Session {
    User *currentUser = nullptr;

public:
    static bool isValidName(const string &name) {
        if (name.empty()) return false;
        for (const char c: name) {
            if (isdigit(c)) return false;
        }
        return true;
    }

    static bool isUserIdDuplicate(const string &id, const vector<User> &users) {
        for (const auto &user: users) {
            if (user.userID == id) return true;
        }
        return false;
    }

    static bool isUserNameDuplicate(const string &name, const vector<User> &users) {
        for (const auto &user: users) {
            if (user.userName == name) return true;
        }
        return false;
    }

    static bool isUserExists(const vector<User> &users, const string &userID) {
        bool exists = false;
        for (auto &user: users) {
            if (user.userID == userID) {
                exists = true;
                break;
            }
        }
        return exists;
    }

    static const User *getUserByID(const vector<User> &users, const string &userID) {
        for (auto &user: users) {
            if (user.userID == userID) {
                return &user;
            }
        }
        return nullptr;
    }

    void registerUser(vector<User> &users, const string &userID, const string &username,
                      const string &password) {
        constexpr hash<string> hasher;
        const User newUser(userID, username, hasher(password));
        if (isUserIdDuplicate(newUser.userID, users)) {
            cout << "[ERROR] User ID already exists! Please use an unique ID." << endl;
            return;
        }
        if (!isValidName(newUser.userName)) {
            cout << "[ERROR] Invalid name! Name cannot contain digits." << endl;
            return;
        }
        if (isUserNameDuplicate(newUser.userName, users)) {
            cout << "[ERROR] UserName already exists! Please use an unique username." << endl;
            return;
        }
        users.push_back(newUser);
        currentUser = &users[users.size() - 1];
        saveUsers(users, nullptr);
        loadUsers(users);
        cout << "[SUCCESSFUL] User Registration Is Successful!" << endl;
    }

    void loginToUser(vector<User> &users, const string &userID, const string &password) {
        for (auto &user: users) {
            if (user.userID != userID) continue;
            if (hash<string> string_hasher; user.passwordHash != string_hasher(password)) continue;
            currentUser = &user;
            break;
        }
        if (currentUser == nullptr) {
            cout << "[ERROR] User Login Failed!" << endl;
        } else {
            cout << "[SUCCESSFUL] User Logged In!" << endl;
        }
        loadUsers(users);
    }

    void logoutUser() {
        if (currentUser != nullptr) {
            currentUser = nullptr;
            cout << "User Have Been Logged Out!" << endl;
        } else {
            cout << "User Not Logged In!" << endl;
        }
    }

    [[nodiscard]] User *getCurrentUser() const {
        return currentUser;
    }

    [[nodiscard]] bool hasUserLoggedIn() const {
        return currentUser != nullptr;
    }
};

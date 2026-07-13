#pragma once
#include <iostream>
#include<iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>

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
    bool isAdmin = false;
    mutable int borrowedCount = 0;
    bool isBlacklisted = false;
    vector<string> booksBorrowed;

    void borrowBook(const Book &book) {
        booksBorrowed.push_back(book.name);
        borrowedCount++;
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

void memberManagement(vector<User> &users);
bool isValidName(const string &name);
bool isUserIdDuplicate(const string &id, const vector<User> &users);
void serviceRegistration(vector<Book> &books, vector<User> &users);
void appointmentManagement(vector<Book> &books, const vector<User> &users, vector<RoomBooking> &roomBookings);
void billingPayment(vector<User> &users, vector<Transaction> &transactions);
void reportingStatistics(vector<Book> &books, vector<User> &users, vector<RoomBooking> &roomBookings, vector<Transaction> &transactions);
void extraHotBooks(vector<Book> &books);
void extraBlacklist(vector<User> &users, const vector<Transaction> &transactions);

void saveBooks(const vector<Book> &books);
void loadBooks(vector<Book> &books);
void saveUsers(const vector<User> &users);
void loadUsers(vector<User> &users);

inline bool isUserExists(const vector<User> &users, const string &userID) {
    bool exists = false;
    for (auto & user : users) {
        if (user.userID == userID) {
            exists = true;
            break;
        }
    }
    return exists;
}

inline const User *getUserByID(const vector<User> &users, const string &userID) {
    for (auto & user : users) {
        if (user.userID == userID) {
            return &user;
        }
    }
    return nullptr;
}
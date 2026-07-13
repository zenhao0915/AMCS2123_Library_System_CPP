#include "data.h"

void saveBooks(const vector<Book> &books) {
    ofstream outFile("books.txt");
    if (!outFile) return;

    for (const auto &b : books) {
        outFile << b.bookID << "|"
                << b.name << "|"
                << b.author << "|"
                << b.stock << "|"
                << b.isReserved << "|"
                << b.borrowCount << "\n";
    }
    outFile.close();
}

void loadBooks(vector<Book> &books) {
    ifstream inFile("books.txt");
    if (!inFile) return;

    books.clear();
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        Book b;
        string stockStr, reservedStr, borrowStr;

        getline(ss, b.bookID, '|');
        getline(ss, b.name, '|');
        getline(ss, b.author, '|');
        getline(ss, stockStr, '|');
        getline(ss, reservedStr, '|');
        getline(ss, borrowStr, '|');

        b.stock = stoi(stockStr);
        b.isReserved = (reservedStr == "1");
        b.borrowCount = stoi(borrowStr);

        books.push_back(b);
    }
    inFile.close();
}

void saveUsers(const vector<User> &users) {
    ofstream outFile("users.txt");
    if (!outFile) return;

    for (const auto &u : users) {
        outFile << u.userID << "|"
                << u.userName << "|"
                << u.isAdmin << "|"
                << u.borrowedCount << "|"
                << u.isBlacklisted << "\n";
    }
    outFile.close();
}

void loadUsers(vector<User> &users) {
    ifstream inFile("users.txt");
    if (!inFile) return;

    users.clear();
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        User u;
        string adminStr, borrowStr, blacklistStr;

        getline(ss, u.userID, '|');
        getline(ss, u.userName, '|');
        getline(ss, adminStr, '|');
        getline(ss, borrowStr, '|');
        getline(ss, blacklistStr, '|');

        u.isAdmin = (adminStr == "1");
        u.borrowedCount = stoi(borrowStr);
        u.isBlacklisted = (blacklistStr == "1");

        users.push_back(u);
    }
    inFile.close();
}
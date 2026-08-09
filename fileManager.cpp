#include "data.h"

void saveBooks(const vector<Book> &books) {
    ofstream outFile("books.txt");
    if (!outFile || books.empty()) return;

    for (const auto &b: books) {
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
    bool isEmpty = false;
    {
        if (ifstream checkFile("books.txt"); !checkFile || checkFile.peek() == ifstream::traits_type::eof()) {
            isEmpty = true;
        }
    }
    if (isEmpty) {
        ofstream outFile("books.txt");
        if (outFile) {
            outFile << "sixseven|SixSeven67|sohai|67|0|0\n"
                    << "kapibala|Bara Story|Yun|10|0|0\n"
                    << "noparking|Tar Dick|TarShit|67|0|0\n";
            outFile.close();
        }
    }
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

void saveAppointments(const vector<RoomBooking> &roomBooking) {
    ofstream outFile("appointment.txt");
    if (!outFile || roomBooking.empty()) return;

    for (const auto &r: roomBooking) {
        outFile << r.roomID << "|"
                << r.userID << "|"
                << r.date << "|"
                << r.timeSlot << "\n";
    }
    outFile.close();
}

void loadAppointments(vector<RoomBooking> &booking) {
    ifstream inFile("appointment.txt");
    if (!inFile) return;

    booking.clear();
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        RoomBooking b;
        string timeSlot;

        getline(ss, b.roomID, '|');
        getline(ss, b.userID, '|');
        getline(ss, b.date, '|');
        getline(ss, timeSlot, '|');

        b.timeSlot = stoi(timeSlot);
        booking.push_back(b);
    }
    inFile.close();
}

void saveUsers(vector<User> &users, const User *currentUser) {
    ofstream outFile("users.txt");
    if (!outFile) return;

    for (auto &u: users) {
        if (currentUser != nullptr && u.passwordHash == currentUser->passwordHash && u.userID == currentUser->userID) {
            u.userName = currentUser->userName;
        }
        string booksBorrowedStr;
        for (const auto &bookName: u.booksBorrowed) {
            booksBorrowedStr += bookName + ",";
        }
        outFile << u.userID << "|"
                << u.userName << "|"
                << u.passwordHash << "|"
                << u.isAdmin << "|"
                << u.borrowedCount << "|"
                << u.isBlacklisted << "|"
                << booksBorrowedStr << "\n";
    }
    outFile.close();
}

void loadUsers(vector<User> &users) {
    bool isEmpty = false;
    {
        if (ifstream checkFile("users.txt"); !checkFile || checkFile.peek() == ifstream::traits_type::eof()) {
            isEmpty = true;
        }
    }

    constexpr hash<string> hasher;
    if (isEmpty) {
        ofstream outFile("users.txt");
        if (outFile) {
            outFile << "admin|admin|" << hasher("admin") << "|1|0|0|\n";
            outFile.close();
        }
    }

    ifstream inFile("users.txt");
    if (!inFile) return;

    users.clear();
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        User u;
        string adminStr, borrowStr, blacklistStr, borrowedBooksStr, hashStr;

        getline(ss, u.userID, '|');
        getline(ss, u.userName, '|');
        getline(ss, hashStr, '|');
        getline(ss, adminStr, '|');
        getline(ss, borrowStr, '|');
        getline(ss, blacklistStr, '|');

        if (!hashStr.empty()) {
            u.passwordHash = stoull(hashStr);
        }
        u.isAdmin = (adminStr == "1");
        u.borrowedCount = stoi(borrowStr);
        u.isBlacklisted = (blacklistStr == "1");

        while (getline(ss, borrowedBooksStr, ',')) {
            u.booksBorrowed.push_back(borrowedBooksStr);
        }

        users.push_back(u);
    }
    inFile.close();
}

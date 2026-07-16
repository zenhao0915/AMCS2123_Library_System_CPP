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
    ifstream inFile("books.txt");
    if (!inFile) return;
    if (inFile.peek() == std::ifstream::traits_type::eof()) {
        // Check File Is Empty Pre Init Books
        if (ofstream outFile("books.txt"); outFile) {
            outFile << "sixseven|SixSeven67|sohai|67|0|0\nkapibala|Bara Story|Yun|10|0|0\nnoparking|Tar Dick|TarShit|67|0|0\n";
            outFile.flush();
            outFile.close();
        }
    }

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
    ifstream inFile("users.txt");
    if (!inFile) return;

    if (inFile.peek() == std::ifstream::traits_type::eof()) {
        // Check File Is Empty Pre Init Admin
        if (ofstream outFile("users.txt"); outFile) {
            outFile << "admin|admin|10289358105851308976|1|0|0|\n";
            // UserID, UserName, Password, isAdmin, BorrowedBooks, isBlackListed, BorrowedStr
            outFile.flush();
            outFile.close();
        }
    }

    users.clear();
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        User u;
        string adminStr, borrowStr, blacklistStr, borrowedBooksStr, hashStr;
        hash<string> pwd;

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

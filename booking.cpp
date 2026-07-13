#include "data.h"


void serviceRegistration(vector<Book> &books, vector<User> &users) {
    while (true) {
        cout << "\n=== Service Registration/Booking Sub-Menu ===" << endl;
        cout << "1. Borrow a Book" << endl;
        cout << "2. Return a Book" << endl;
        cout << "3. Add New Book to Inventory" << endl;
        cout << "4. View All Books" << endl;
        cout << "5. Return to Main Menu" << endl;
        cout << "Enter choice (1-5): ";

        int choice;
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[ERROR] Invalid choice! Try again." << endl;
            continue;
        }

        if (choice == 5) break;

        if (choice == 1) {
            cout << "\n[Borrow a Book]" << endl;
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
                cout << "[BLACKLIST] Already blacklisted!" << endl;
                break;
            }

            cout << "Enter Book ID: ";
            string bID;
            cin >> bID;

            int bookIndex = -1;
            for (int i = 0; i < books.size(); i++) {
                if (books[i].bookID == bID) {
                    bookIndex = i;
                    break;
                }
            }

            if (bookIndex == -1) {
                cout << "[ERROR] Book ID not found!" << endl;
                continue;
            }

            if (books[bookIndex].stock <= 0) {
                cout << "[ERROR] Book is out of stock!" << endl;
                continue;
            }

            books[bookIndex].stock--;
            users[userIndex].borrowedCount++;
            cout << "[SUCCESS] Book borrowed successfully!" << endl;
        }
        else if (choice == 2) {
            cout << "\n[Return a Book]" << endl;
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

            cout << "Enter Book ID: ";
            string bID;
            cin >> bID;

            int bookIndex = -1;
            for (int i = 0; i < books.size(); i++) {
                if (books[i].bookID == bID) {
                    bookIndex = i;
                    break;
                }
            }

            if (bookIndex == -1) {
                cout << "[ERROR] Book ID not found!" << endl;
                continue;
            }

            if (users[userIndex].borrowedCount <= 0) {
                cout << "[ERROR] This user has no borrowed books recorded!" << endl;
                continue;
            }

            books[bookIndex].stock++;
            users[userIndex].borrowedCount--;
            cout << "[SUCCESS] Book returned successfully!" << endl;
        }
        else if (choice == 3) {
            cout << "\n[Add New Book]" << endl;
            Book newBook;

            while (true) {
                cout << "Enter Book ID: ";
                cin >> newBook.bookID;
                bool dup = false;
                for (const auto &b : books) {
                    if (b.bookID == newBook.bookID) {
                        dup = true;
                        break;
                    }
                }
                if (dup) {
                    cout << "[ERROR] Book ID already exists!" << endl;
                } else {
                    break;
                }
            }

            cin.ignore(10000, '\n');
            cout << "Enter Book Name: ";
            getline(cin, newBook.name);
            cout << "Enter Author: ";
            getline(cin, newBook.author);

            while (true) {
                cout << "Enter Stock Quantity: ";
                cin >> newBook.stock;
                if (cin.fail() || newBook.stock < 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[ERROR] Invalid stock quantity!" << endl;
                } else {
                    break;
                }
            }

            newBook.isReserved = false;
            books.push_back(newBook);
            cout << "[SUCCESS] Book added to inventory!" << endl;
        }
        else if (choice == 4) {
            cout << "\n[View All Books]" << endl;
            if (books.empty()) {
                cout << "No books in inventory." << endl;
                continue;
            }
            cout << "--------------------------------------------------------" << endl;
            for (const auto &b : books) {
                cout << "ID: " << b.bookID << " | Name: " << b.name
                     << " | Author: " << b.author << " | Stock: " << b.stock << endl;
            }
            cout << "--------------------------------------------------------" << endl;
        }
    }
}
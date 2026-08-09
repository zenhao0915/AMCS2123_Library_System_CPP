#include "data.h"

void extraHotBooks(vector<Book> &books) {
    clearInputBuffer();

    cout << "\n========================================" << endl;
    cout << "     TOP 5 HOT TOPICS BOOK REPORT       " << endl;
    cout << "========================================" << endl;

    if (books.empty()) {
        cout << "No books available in the system." << endl;
        cout << "========================================" << endl;
        return;
    }

    vector<Book> sortedBooks = books;

    for (size_t i = 0; i < sortedBooks.size() - 1; i++) {
        for (size_t j = 0; j < sortedBooks.size() - i - 1; j++) {
            if (sortedBooks[j].borrowCount < sortedBooks[j + 1].borrowCount) {
                Book temp = sortedBooks[j];
                sortedBooks[j] = sortedBooks[j + 1];
                sortedBooks[j + 1] = temp;
            }
        }
    }

    const size_t displayCount = sortedBooks.size() < 5 ? sortedBooks.size() : 5;

    cout << left << setw(6) << "Rank" << setw(10) << "Book ID" << setw(20) << "Title" << "Borrows" << endl;
    cout << "----------------------------------------" << endl;

    for (size_t i = 0; i < displayCount; i++) {
        cout << left << setw(6) << (i + 1)
             << setw(10) << sortedBooks[i].bookID
             << setw(20) << sortedBooks[i].name
             << sortedBooks[i].borrowCount << endl;
    }
    cout << "========================================" << endl;
}
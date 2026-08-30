#include "data.h"

void billingPayment(vector<User> &users, vector<Transaction> &transactions, User *currentUser) {
    while (true) {
        cout << "\n--- Billing & Payment Processing Sub-Menu ---" << endl;
        cout << "1. Generate Overdue Fine" << endl;
        cout << "2. Process Fine Payment" << endl;
        cout << "3. View Member Outstanding Fines" << endl;
        cout << "4. Print Detailed Invoice/Receipt" << endl;
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
            if (!currentUser->hasPermission()) {
                cout << "[ERROR] Access denied! Administrator privilege required." << endl;
                continue;
            }

            cout << "\n[Generate Overdue Fine]" << endl;
            cout << "Enter User ID: ";
            string uID;
            cin >> uID;

            bool userExists = false;
            for (const auto &u : users) {
                if (u.userID == uID) {
                    userExists = true;
                    break;
                }
            }
            if (!userExists) {
                cout << "[ERROR] User ID not found!" << endl;
                continue;
            }

            int overdueDays;
            while (true) {
                cout << "Enter Overdue Days: ";
                cin >> overdueDays;
                if (cin.fail() || overdueDays <= 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[ERROR] Overdue days must be greater than 0!" << endl;
                } else {
                    break;
                }
            }

            Transaction tx;
            tx.txID = "TX" + to_string(transactions.size() + 1001);
            tx.userID = uID;
            tx.fineAmount = overdueDays * 0.50; 
            tx.paidAmount = 0.0;
            tx.isSettled = false;

            transactions.push_back(tx);
            saveTransactions(transactions);
            cout << "[SUCCESS] Fine generated! Invoice ID: " << tx.txID << " | Amount: RM " << fixed << setprecision(2) << tx.fineAmount << endl;
        }
        else if (choice == 2) {
            cout << "\n[Process Fine Payment]" << endl;
            cout << "Enter Invoice ID (TXXXXX): ";
            string tID;
            cin >> tID;

            int txIndex = -1;
            for (int i = 0; i < transactions.size(); i++) {
                if (transactions[i].txID == tID) {
                    txIndex = i;
                    break;
                }
            }

            if (txIndex == -1) {
                cout << "[ERROR] Invoice ID not found!" << endl;
                continue;
            }

            if (transactions[txIndex].isSettled) {
                cout << "[ERROR] This invoice is already fully paid!" << endl;
                continue;
            }

            double outstanding = transactions[txIndex].fineAmount - transactions[txIndex].paidAmount;
            cout << "Outstanding Amount: RM " << fixed << setprecision(2) << outstanding << endl;

            double payment;
            while (true) {
                cout << "Enter Payment Amount: ";
                cin >> payment;
                if (cin.fail() || payment <= 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[ERROR] Invalid payment amount!" << endl;
                } else if (payment < outstanding) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[ERROR] Insufficient payment! Minimum required: RM " << outstanding << endl;
                } else {
                    break;
                }
            }

            transactions[txIndex].paidAmount += payment;
            transactions[txIndex].isSettled = true;
            saveTransactions(transactions);
            double change = payment - outstanding;

            cout << "[SUCCESS] Payment processed successfully!" << endl;
            if (change > 0) {
                cout << "Change to Return: RM " << fixed << setprecision(2) << change << endl;
            }
        }
        else if (choice == 3) {
            cout << "\n[Outstanding Fines Summary]" << endl;
            cout << "Enter User ID: ";
            string uID;
            cin >> uID;

            double totalOutstanding = 0.0;
            cout << "--------------------------------------------------------" << endl;
            cout << left << setw(15) << "Invoice ID" << setw(20) << "Fine Amount (RM)" << "Status" << endl;
            cout << "--------------------------------------------------------" << endl;
            for (const auto &tx : transactions) {
                if (tx.userID == uID && !tx.isSettled) {
                    double due = tx.fineAmount - tx.paidAmount;
                    totalOutstanding += due;
                    cout << left << setw(15) << tx.txID << setw(20) << fixed << setprecision(2) << due << "UNPAID" << endl;
                }
            }
            cout << "--------------------------------------------------------" << endl;
            cout << "Total Outstanding Balance: RM " << fixed << setprecision(2) << totalOutstanding << endl;
            cout << "--------------------------------------------------------" << endl;
        }
        else if (choice == 4) {
            cout << "\n[Print Detailed Invoice/Receipt]" << endl;
            cout << "Enter Invoice ID: ";
            string tID;
            cin >> tID;

            bool found = false;
            for (const auto &tx : transactions) {
                if (tx.txID == tID) {
                    found = true;
                    cout << "\n========================================" << endl;
                    cout << "           OFFICIAL RECEIPT            " << endl;
                    cout << "========================================" << endl;
                    cout << left << setw(20) << "Transaction ID:" << tx.txID << endl;
                    cout << left << setw(20) << "Member ID:" << tx.userID << endl;
                    cout << "----------------------------------------" << endl;
                    cout << left << setw(25) << "Description" << "Amount" << endl;
                    cout << left << setw(25) << "Overdue Library Fine" << "RM " << fixed << setprecision(2) << tx.fineAmount << endl;
                    cout << "----------------------------------------" << endl;
                    cout << left << setw(25) << "Total Paid:" << "RM " << fixed << setprecision(2) << tx.paidAmount << endl;
                    if (tx.paidAmount > tx.fineAmount) {
                        cout << left << setw(25) << "Change To Return: RM " << fixed << setprecision(2) << (tx.paidAmount - tx.fineAmount) << endl;
                    }
                    cout << left << setw(25) << "Status:" << (tx.isSettled ? "FULLY SETTLED" : "PARTIAL/UNPAID") << endl;
                    cout << "========================================" << endl;
                    break;
                }
            }
            if (!found) cout << "[ERROR] Invoice ID not found!" << endl;
        }
    }
}
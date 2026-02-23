/*
* Name: Magda Hussein
 * Date: 02/22/2026
 * Program: Enhancing the Bank Account Management System
 * Assignment: C++ Lab: Inheritance & Composition
 */
#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include <iostream>
#include <vector>
#include <limits>
#include <memory>

using namespace std;

// Clears bad input from the input buffer
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Displays the menu options for the user
void showMenu() {
    cout << endl;
    cout << endl;
    cout << "=== BANK ACCOUNT MANAGEMENT WITH INHERITANCE ===" << endl;
    cout << "1. Create a new regular account" << endl;
    cout << "2. Create a new checking account (with fees)" << endl;
    cout << "3. Create a new savings account (with interest)" << endl;
    cout << "4. Display all accounts" << endl;
    cout << "5. Deposit money" << endl;
    cout << "6. Withdraw money (demonstrates polymorphism)" << endl;
    cout << "7. Calculate interest (savings accounts only)" << endl;
    cout << "8. Compare accounts (==, <, >)" << endl;
    cout << "9. Update account holder name" << endl;
    cout << "10. View transaction history" << endl;
    cout << "11. Test copy constructor/assignment" << endl;
    cout << "12. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to display all accounts (using polymorphism)
void displayAllAccounts(const vector<BankAccount*>& accounts) {
    if (accounts.empty()) {
        cout << "No accounts found." << endl;
        return;
    }

    cout << endl << "*** ALL ACCOUNTS ***" << endl;
    for (size_t i = 0; i < accounts.size(); i++) {
        cout << "Account " << (i + 1) << ":" << endl;
        BankAccount::printAccount(*accounts[i]);

        // Check if it's a checking account
        auto* checkPtr = dynamic_cast<CheckingAccount*>(accounts[i]);
        if (checkPtr != nullptr) {
            cout << "  Type: Checking Account" << endl;
            cout << "  Transaction Fee: $" << checkPtr->getTransactionFee() << endl;
        }

        // Check if it's a savings account
        auto* savePtr = dynamic_cast<SavingsAccount*>(accounts[i]);
        if (savePtr != nullptr) {
            cout << "  Type: Savings Account" << endl;
            cout << "  Interest Rate: " << (savePtr->getInterestRate() * 100) << "%" << endl;
        }
    }
}

int main() {
    vector<BankAccount*> accountList;  // Vector of base class pointers for polymorphism
    int userChoice;

    do {
        showMenu();
        cin >> userChoice;

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input. Please enter a number (1-12)." << endl;
            continue;
        }

        switch(userChoice) {
            // Create a new regular account
            case 1: {
                clearInput();
                cout << "=== CREATE NEW REGULAR ACCOUNT ===" << endl;

                auto* newAccount = new BankAccount(BankAccount::createAccountFromInput());
                accountList.push_back(newAccount);

                cout << "Regular account created successfully!" << endl;
                break;
            }

            // Create a new checking account
            case 2: {
                clearInput();
                cout << "=== CREATE NEW CHECKING ACCOUNT ===" << endl;

                auto* newAccount = new CheckingAccount(CheckingAccount::createCheckingFromInput());
                accountList.push_back(newAccount);

                cout << "Checking account created successfully!" << endl;
                break;
            }

            // Create a new savings account
            case 3: {
                clearInput();
                cout << "=== CREATE NEW SAVINGS ACCOUNT ===" << endl;

                auto* newAccount = new SavingsAccount(SavingsAccount::createSavingsFromInput());
                accountList.push_back(newAccount);

                cout << "Savings account created successfully!" << endl;
                break;
            }

            // Display all accounts
            case 4: {
                displayAllAccounts(accountList);
                break;
            }

            // Deposit money into an account
            case 5: {
                if (accountList.empty()) {
                    cout << "No accounts found. Create an account first." << endl;
                    break;
                }

                int accIndex;
                double depositAmount;

                cout << "Enter account number (1-" << accountList.size() << "): ";
                while (!(cin >> accIndex) || accIndex < 1 || accIndex > static_cast<int>(accountList.size())) {
                    cout << "Invalid account number. Enter (1-" << accountList.size() << "): ";
                    clearInput();
                }

                cout << "Enter deposit amount: ";
                while (!(cin >> depositAmount) || depositAmount <= 0) {
                    cout << "Invalid amount. Enter a positive number: ";
                    clearInput();
                }

                accountList[accIndex - 1]->deposit(depositAmount);
                break;
            }

            // Withdraw money (demonstrates polymorphic behavior)
            case 6: {
                if (accountList.empty()) {
                    cout << "No accounts found. Create an account first." << endl;
                    break;
                }

                int accIndex;
                double withdrawAmount;

                cout << "Enter account number (1-" << accountList.size() << "): ";
                while (!(cin >> accIndex) || accIndex < 1 || accIndex > static_cast<int>(accountList.size())) {
                    cout << "Invalid account number. Enter (1-" << accountList.size() << "): ";
                    clearInput();
                }

                cout << "Enter withdrawal amount: ";
                while (!(cin >> withdrawAmount) || withdrawAmount <= 0) {
                    cout << "Invalid amount. Enter a positive number: ";
                    clearInput();
                }

                // Polymorphic call - withdraw behaves differently based on account type
                accountList[accIndex - 1]->withdraw(withdrawAmount);

                cout << "Demonstrated polymorphic withdraw behavior!" << endl;
                break;
            }

            // Calculate interest for savings accounts
            case 7: {
                if (accountList.empty()) {
                    cout << "No accounts found. Create an account first." << endl;
                    break;
                }

                int accIndex;

                cout << "Enter account number (1-" << accountList.size() << "): ";
                while (!(cin >> accIndex) || accIndex < 1 || accIndex > static_cast<int>(accountList.size())) {
                    cout << "Invalid account number. Enter (1-" << accountList.size() << "): ";
                    clearInput();
                }

                // Try to cast to savings account
                auto* savePtr = dynamic_cast<SavingsAccount*>(accountList[accIndex - 1]);

                if (savePtr != nullptr) {
                    savePtr->calculateInterest();
                } else {
                    cout << "This is not a savings account. Cannot calculate interest." << endl;
                }
                break;
            }

            // Compare two accounts
            case 8: {
                if (accountList.size() < 2) {
                    cout << "Need at least 2 accounts to compare." << endl;
                    break;
                }

                int acc1, acc2;

                cout << "Enter first account number (1-" << accountList.size() << "): ";
                cin >> acc1;
                cout << "Enter second account number (1-" << accountList.size() << "): ";
                cin >> acc2;

                if (acc1 < 1 || acc1 > static_cast<int>(accountList.size()) ||
                    acc2 < 1 || acc2 > static_cast<int>(accountList.size())) {
                    cout << "Invalid account numbers." << endl;
                    break;
                }

                cout << "Comparison Results:" << endl;
                cout << "Accounts have same number? "
                     << (*accountList[acc1-1] == *accountList[acc2-1] ? "Yes" : "No") << endl;

                cout << "Account " << acc1 << " < Account " << acc2 << "? "
                     << (*accountList[acc1-1] < *accountList[acc2-1] ? "Yes" : "No") << endl;

                cout << "Account " << acc1 << " > Account " << acc2 << "? "
                     << (*accountList[acc1-1] > *accountList[acc2-1] ? "Yes" : "No") << endl;

                break;
            }

            // Update account holder name
            case 9: {
                if (accountList.empty()) {
                    cout << "No accounts found. Create an account first." << endl;
                    break;
                }

                int accIndex;
                string newName;

                cout << "Enter account number (1-" << accountList.size() << "): ";
                while (!(cin >> accIndex) || accIndex < 1 || accIndex > static_cast<int>(accountList.size())) {
                    cout << "Invalid account number. Enter (1-" << accountList.size() << "): ";
                    clearInput();
                }

                clearInput();
                cout << "Enter new account holder name: ";
                getline(cin, newName);

                accountList[accIndex - 1]->setAccountHolderName(newName);
                cout << "Name updated successfully!" << endl;
                break;
            }

            // View transaction history
            case 10: {
                if (accountList.empty()) {
                    cout << "No accounts found. Create an account first." << endl;
                    break;
                }

                int accIndex;
                cout << "Enter account number (1-" << accountList.size() << "): ";
                while (!(cin >> accIndex) || accIndex < 1 || accIndex > static_cast<int>(accountList.size())) {
                    cout << "Invalid account number. Enter (1-" << accountList.size() << "): ";
                    clearInput();
                }

                accountList[accIndex - 1]->printHistory();
                break;
            }

            // Test copy constructor and assignment operator
            case 11: {
                if (accountList.empty()) {
                    cout << "No accounts found. Create an account first." << endl;
                    break;
                }

                int accIndex;
                cout << "Enter account number to copy (1-" << accountList.size() << "): ";
                cin >> accIndex;

                if (accIndex < 1 || accIndex > static_cast<int>(accountList.size())) {
                    cout << "Invalid account number." << endl;
                    break;
                }

                // Test copy on a regular account for simplicity
                // For derived classes, we'd need specific copy constructors
                cout << "Copy tests work on regular BankAccount objects." << endl;
                cout << "For Checking and Savings, specialized copy constructors exist." << endl;

                // Create a copy using copy constructor
                BankAccount copiedAccount(*accountList[accIndex - 1]);
                cout << "Copied account using copy constructor:" << endl;
                BankAccount::printAccount(copiedAccount);

                break;
            }

            // Exit program (clean up memory)
            case 12: {
                cout << "Cleaning up memory..." << endl;

                // Delete all dynamically allocated objects
                for (BankAccount* account : accountList) {
                    delete account;
                }
                accountList.clear();

                cout << "Thank you for using Bank Account Management System!" << endl;
                break;
            }

            default: {
                cout << "Invalid choice. Please enter a number between 1 and 12." << endl;
                break;
            }
        }

    } while (userChoice != 12);

    return 0;
}
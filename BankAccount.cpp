#include "BankAccount.h"
#include <iostream>
#include <string>
#include <limits>
#include <utility>
#include <ctime>

using namespace std;

string getCurrentTimestamp() {
    time_t now = time(0);
    string dt = ctime(&now);
    if (!dt.empty() && dt[dt.length()-1] == '\n') {
        dt.erase(dt.length()-1);
    }
    return dt;
}

BankAccount::BankAccount() {
    accountNumber = "";
    accountHolderName = "";
    balance = 0.0;
}

BankAccount::BankAccount(string number, string name, double initialBalance) {
    accountNumber = std::move(number);
    accountHolderName = std::move(name);
    balance = initialBalance;
    if (initialBalance > 0) {
        transactionHistory.push_back(Transaction("Initial Deposit", initialBalance, getCurrentTimestamp()));
    }
}

BankAccount::BankAccount(const BankAccount& other) {
    accountNumber = other.accountNumber;
    accountHolderName = other.accountHolderName;
    balance = other.balance;
    transactionHistory = other.transactionHistory;
}

BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) {
        accountNumber = other.accountNumber;
        accountHolderName = other.accountHolderName;
        balance = other.balance;
        transactionHistory = other.transactionHistory;
    }
    return *this;
}

BankAccount::~BankAccount() {
}

string BankAccount::getAccountNumber() const {
    return accountNumber;
}

string BankAccount::getAccountHolderName() const {
    return accountHolderName;
}

double BankAccount::getBalance() const {
    return balance;
}

void BankAccount::setAccountHolderName(string newName) {
    accountHolderName = std::move(newName);
}

void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance = balance + amount;
        transactionHistory.push_back(Transaction("Deposit", amount, getCurrentTimestamp()));
        cout << "Deposit successful. New balance: " << balance << endl;
    } else {
        cout << "Invalid deposit amount." << endl;
    }
}

void BankAccount::withdraw(double amount) {
    if (amount <= 0) {
        cout << "Invalid withdrawal amount." << endl;
    } else if (amount > balance) {
        cout << "Insufficient funds. Withdrawal failed." << endl;
    } else {
        balance = balance - amount;
        transactionHistory.push_back(Transaction("Withdrawal", amount, getCurrentTimestamp()));
        cout << "Withdrawal successful. New balance: " << balance << endl;
    }
}

void BankAccount::printHistory() const {
    cout << "\n=== TRANSACTION HISTORY for Account " << accountNumber << " ===" << endl;

    if (transactionHistory.empty()) {
        cout << "No transactions yet." << endl;
    } else {
        cout << "--------------------------------------------------------" << endl;
        for (size_t i = 0; i < transactionHistory.size(); i++) {
            cout << "Transaction #" << (i + 1) << ":" << endl;
            cout << "  Type: " << transactionHistory[i].type << endl;
            cout << "  Amount: $" << transactionHistory[i].amount << endl;
            cout << "  Time: " << transactionHistory[i].timestamp << endl;
            cout << "--------------------------------------------------------" << endl;
        }
        cout << "End of history\n" << endl;
    }
}

BankAccount& BankAccount::operator+=(double amount) {
    if (amount > 0) {
        balance += amount;
        cout << "Operator +=: Added " << amount << ". New balance: " << balance << endl;
    } else {
        cout << "Operator +=: Invalid amount." << endl;
    }
    return *this;
}

BankAccount& BankAccount::operator-=(double amount) {
    if (amount <= 0) {
        cout << "Operator -=: Invalid amount." << endl;
    } else if (amount > balance) {
        cout << "Operator -=: Insufficient funds." << endl;
    } else {
        balance -= amount;
        cout << "Operator -=: Subtracted " << amount << ". New balance: " << balance << endl;
    }
    return *this;
}

bool BankAccount::operator==(const BankAccount& other) const {
    return accountNumber == other.accountNumber;
}

bool BankAccount::operator<(const BankAccount& other) const {
    return balance < other.balance;
}

bool BankAccount::operator>(const BankAccount& other) const {
    return balance > other.balance;
}

void BankAccount::printAccount(const BankAccount& account) {
    cout << "=== ACCOUNT DETAILS ===" << endl;
    cout << "Account Number: " << account.accountNumber << endl;
    cout << "Account Holder: " << account.accountHolderName << endl;
    cout << "Balance: $" << account.balance << endl;
    cout << "=======================" << endl;
}

BankAccount BankAccount::createAccountFromInput() {
    string accNumber, accName;
    double startBalance;

    cout << "Enter account number: ";
    getline(cin, accNumber);

    cout << "Enter account holder name: ";
    getline(cin, accName);

    cout << "Enter initial balance: ";
    while (!(cin >> startBalance) || startBalance < 0) {
        cout << "Invalid amount. Enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    return {accNumber, accName, startBalance};
}
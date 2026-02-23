#include "CheckingAccount.h"
#include <iostream>
#include <limits>

using namespace std;

CheckingAccount::CheckingAccount() : BankAccount() {
    transactionFee = 0.0;
}

CheckingAccount::CheckingAccount(string number, string name, double initialBalance, double fee)
    : BankAccount(number, name, initialBalance) {
    transactionFee = fee;
}

CheckingAccount::CheckingAccount(const CheckingAccount& other) : BankAccount(other) {
    transactionFee = other.transactionFee;
}

CheckingAccount& CheckingAccount::operator=(const CheckingAccount& other) {
    if (this != &other) {
        BankAccount::operator=(other);
        transactionFee = other.transactionFee;
    }
    return *this;
}

CheckingAccount::~CheckingAccount() {
}

double CheckingAccount::getTransactionFee() const {
    return transactionFee;
}

void CheckingAccount::setTransactionFee(double fee) {
    if (fee >= 0) {
        transactionFee = fee;
    } else {
        cout << "Transaction fee cannot be negative." << endl;
    }
}

void CheckingAccount::withdraw(double amount) {
    double totalAmount = amount + transactionFee;

    if (amount <= 0) {
        cout << "Invalid withdrawal amount." << endl;
    } else if (totalAmount > getBalance()) {
        cout << "Insufficient funds for withdrawal + fee. Need $" << totalAmount
             << " but balance is $" << getBalance() << endl;
    } else {
        BankAccount::withdraw(amount);
        cout << "Applying transaction fee of $" << transactionFee << endl;
        BankAccount::withdraw(transactionFee);
    }
}

CheckingAccount CheckingAccount::createCheckingFromInput() {
    string accNumber, accName;
    double startBalance, fee;
    
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
    
    cout << "Enter transaction fee: ";
    while (!(cin >> fee) || fee < 0) {
        cout << "Invalid fee. Enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    
    return CheckingAccount(accNumber, accName, startBalance, fee);
}
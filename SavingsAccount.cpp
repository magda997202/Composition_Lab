#include "SavingsAccount.h"
#include <iostream>
#include <limits>

using namespace std;

SavingsAccount::SavingsAccount() : BankAccount() {
    interestRate = 0.0;
}

SavingsAccount::SavingsAccount(string number, string name, double initialBalance, double rate)
    : BankAccount(number, name, initialBalance) {
    interestRate = rate;
}

SavingsAccount::SavingsAccount(const SavingsAccount& other) : BankAccount(other) {
    interestRate = other.interestRate;
}

SavingsAccount& SavingsAccount::operator=(const SavingsAccount& other) {
    if (this != &other) {
        BankAccount::operator=(other);
        interestRate = other.interestRate;
    }
    return *this;
}

SavingsAccount::~SavingsAccount() {
}

double SavingsAccount::getInterestRate() const {
    return interestRate;
}

void SavingsAccount::setInterestRate(double rate) {
    if (rate >= 0) {
        interestRate = rate;
    } else {
        cout << "Interest rate cannot be negative." << endl;
    }
}

void SavingsAccount::calculateInterest() {
    double interest = getBalance() * interestRate;

    if (interest > 0) {
        deposit(interest);
        cout << "Interest of $" << interest << " added at rate "
             << (interestRate * 100) << "%" << endl;
    } else {
        cout << "No interest added." << endl;
    }
}

SavingsAccount SavingsAccount::createSavingsFromInput() {
    string accNumber, accName;
    double startBalance, rate;

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

    cout << "Enter interest rate (as decimal, e.g., 0.05 for 5%): ";
    while (!(cin >> rate) || rate < 0) {
        cout << "Invalid rate. Enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    return SavingsAccount(accNumber, accName, startBalance, rate);
}
#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "BankAccount.h"
#include <string>

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount();
    SavingsAccount(std::string number, std::string name, double initialBalance, double rate);
    SavingsAccount(const SavingsAccount& other);
    SavingsAccount& operator=(const SavingsAccount& other);
    ~SavingsAccount();

    double getInterestRate() const;
    void setInterestRate(double rate);
    void calculateInterest();

    static SavingsAccount createSavingsFromInput();
};

#endif
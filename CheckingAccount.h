#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "BankAccount.h"
#include <string>

class CheckingAccount : public BankAccount {
private:
    double transactionFee;

public:
    CheckingAccount();
    CheckingAccount(std::string number, std::string name, double initialBalance, double fee);
    CheckingAccount(const CheckingAccount& other);
    CheckingAccount& operator=(const CheckingAccount& other);
    ~CheckingAccount();

    double getTransactionFee() const;
    void setTransactionFee(double fee);
    void withdraw(double amount) override;

    static CheckingAccount createCheckingFromInput();
};

#endif
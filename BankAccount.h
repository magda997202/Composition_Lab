#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

class BankAccount {
private:
    std::string accountNumber;
    std::string accountHolderName;
    double balance;
    std::vector<Transaction> transactionHistory;

public:
    BankAccount();
    BankAccount(std::string number, std::string name, double initialBalance);
    BankAccount(const BankAccount& other);
    BankAccount& operator=(const BankAccount& other);
    virtual ~BankAccount();

    std::string getAccountNumber() const;
    std::string getAccountHolderName() const;
    double getBalance() const;
    void setAccountHolderName(std::string newName);

    virtual void deposit(double amount);
    virtual void withdraw(double amount);
    void printHistory() const;

    BankAccount& operator+=(double amount);
    BankAccount& operator-=(double amount);
    bool operator==(const BankAccount& other) const;
    bool operator<(const BankAccount& other) const;
    bool operator>(const BankAccount& other) const;

    static void printAccount(const BankAccount& account);
    static BankAccount createAccountFromInput();
};

#endif
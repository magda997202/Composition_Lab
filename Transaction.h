#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
// New Struct Transaction
struct Transaction {
    std::string type;
    double amount;
    std::string timestamp;

    Transaction(std::string t, double a, std::string ts)
        : type(t), amount(a), timestamp(ts) {}
};

#endif
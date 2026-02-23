cmake_minimum_required(VERSION 4.0)
project(BankAccount)

set(CMAKE_CXX_STANDARD 20)

add_executable(BankAccount main.cpp
        BankAccount.cpp
        BankAccount.h
        CheckingAccount.cpp
        CheckingAccount.h
        SavingsAccount.cpp
        SavingsAccount.h
        Transaction.h)

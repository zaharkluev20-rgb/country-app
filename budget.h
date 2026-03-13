#pragma once
#include <iostream>
using namespace std;

class Budget {
private:
    long long money;
    double coefficient;

public:
    Budget();
    Budget(long long m, double coeff);
    Budget(const Budget& other);
    ~Budget();

    long long getMoney() const;
    double getCoefficient() const;
    void setMoney(long long m);
    void setCoefficient(double coeff);
    void changeBy(long long amount);
    void print() const;
};
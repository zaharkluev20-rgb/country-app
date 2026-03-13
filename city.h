#pragma once
#include <iostream>
#include <string>
using namespace std;

struct City {
    string name;
    int population;
    long long availableMoney;

    City();
    City(string n, int pop);
    City(string n, int pop, long long money);
    City(const City& other);
    ~City();

    void print() const;
};
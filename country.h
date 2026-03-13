#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "city.h"
#include "budget.h"
using namespace std;

class Country {
private:
    string name;
    string capital;
    double foundationDate;
    double area;
    int population;
    vector<City> cities;
    Budget budget;

public:
    Country();
    Country(string n, string c, double date, double a, int pop, vector<City> cityList);
    Country(const Country& other);
    ~Country();

    string getName() const;
    string getCapital() const;
    double getFoundationDate() const;
    double getArea() const;
    int getPopulation() const;
    Budget getBudget() const;
    vector<City> getCities() const;

    void setName(string n);
    void setCapital(string newCapital);
    void setFoundationDate(double date);
    void setArea(double a);
    void setPopulation(int pop);
    void setBudget(long long money, double coeff);

    void addTerritory(double extraArea);
    void changePopulation(int delta);
    void print() const;
    void printCities() const;
    void distributeBudget();
    void addBudget(long long amount);
    void addCity(const City& city);
    void removeCity(string cityName);

    // Методы findCity - возвращают указатель или 0
    City* findCity(string cityName);
    const City* findCity(string cityName) const;

    Country operator+(const Country& other) const;
    Country& operator+=(const Country& other);
    Country operator*(const Country& other) const;
};
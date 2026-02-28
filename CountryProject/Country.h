#pragma once

#include <string>
#include <vector>

class Country
{
private:
    std::string name;
    std::string capital;
    double area;
    std::vector<std::string> cities;

public:
    // Конструкторы
    Country();
    Country(std::string n, std::string c, double a, std::vector<std::string> cityList);
    Country(const Country& other);

    // Деструктор
    ~Country();

    // Геттеры
    std::string getName();
    std::string getCapital();
    double getArea();

    // Сеттеры и методы
    void setCapital(std::string newCapital);
    void addTerritory(double extraArea);
    void print();

    // Операторы
    Country operator+(const Country& other);
    Country& operator+=(const Country& other);
    Country operator*(const Country& other);
};

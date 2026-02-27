#include "Country.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Конструктор по умолчанию
Country::Country()
{
    name = "Неизвестно";
    capital = "Нет";
    area = 0;
}

// Конструктор с параметрами
Country::Country(string n, string c, double a, vector<string> cityList)
{
    name = n;
    capital = c;
    area = a;
    cities = cityList;
}

// Конструктор копирования
Country::Country(const Country& other)
{
    name = other.name;
    capital = other.capital;
    area = other.area;
    cities = other.cities;
}

// Деструктор
Country::~Country()
{
    cities.clear();
    cout << "Деструктор выполнился" << endl;
}

// Геттеры
string Country::getName() { return name; }
string Country::getCapital() { return capital; }
double Country::getArea() { return area; }

// Сеттер
void Country::setCapital(string newCapital)
{
    capital = newCapital;
    cities.push_back(newCapital);
}

// Присоединение территории
void Country::addTerritory(double extraArea)
{
    area += extraArea;
}

// Оператор +
Country Country::operator+(const Country& other)
{
    Country result;

    result.name = name + "-" + other.name;

    if (area < other.area)
        result.capital = other.capital;
    else
        result.capital = capital;

    result.area = area + other.area;

    result.cities = cities;
    for (int i = 0; i < other.cities.size(); i++)
        result.cities.push_back(other.cities[i]);

    return result;
}

// Оператор +=
Country& Country::operator+=(const Country& other)
{
    name = name + "-" + other.name;

    if (area < other.area)
        capital = other.capital;

    area += other.area;

    for (int i = 0; i < other.cities.size(); i++)
        cities.push_back(other.cities[i]);

    return *this;
}

// Оператор *
Country Country::operator*(const Country& other)
{
    Country result;

    result.name = "Путь " + name + " -> " + other.name;
    result.capital = "нет";

    if (area < other.area)
        result.area = area;
    else
        result.area = other.area;

    // случайное присоединение территории
    double extra = rand() % 5001;
    result.addTerritory(extra);

    result.cities.push_back(capital);
    result.cities.push_back(other.capital);

    if (cities.size() > 0)
        result.cities.push_back(cities[rand() % cities.size()]);

    if (other.cities.size() > 0)
        result.cities.push_back(other.cities[rand() % other.cities.size()]);

    return result;
}

void Country::print()
{
    cout << "\nНазвание: " << name << endl;
    cout << "Столица: " << capital << endl;
    cout << "Площадь: " << area << endl;

    cout << "Города: ";
    for (int i = 0; i < cities.size(); i++)
        cout << cities[i] << " ";
    cout << endl;
}
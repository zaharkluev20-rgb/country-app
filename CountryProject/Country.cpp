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
    cout << "Конструктор по умолчанию" << endl;
}

// Конструктор с параметрами
Country::Country(string n, string c, double a, vector<string> cityList)
{
    name = n;
    capital = c;
    area = a;
    cities = cityList;
    cout << "Конструктор с параметрами для " << name << endl;
}

// Конструктор копирования
Country::Country(const Country& other)
{
    name = other.name;
    capital = other.capital;
    area = other.area;
    cities = other.cities;
    cout << "Конструктор копирования для " << name << endl;
}

// Деструктор
Country::~Country()
{
    cities.clear();
    cout << "Деструктор для " << name << " выполнился" << endl;
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
    cout << "Территория увеличена на " << extraArea << ". Новая площадь: " << area << endl;
}

// Оператор + (ВСЕ города, повторы => "(новый)")
Country Country::operator+(const Country& other)
{
    Country result;
    result.name = name + "-" + other.name;

    if (area < other.area)
        result.capital = other.capital;
    else
        result.capital = capital;

    result.area = area + other.area;

    // Добавляем ВСЕ города из первой страны
    for (int i = 0; i < cities.size(); i++) {
        // Проверяем, есть ли уже такой город в результате
        bool found = false;
        for (int j = 0; j < result.cities.size(); j++) {
            if (result.cities[j] == cities[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            result.cities.push_back(cities[i]);
        }
        else {
            result.cities.push_back(cities[i] + " (новый)");
        }
    }

    // Добавляем ВСЕ города из второй страны
    for (int i = 0; i < other.cities.size(); i++) {
        // Проверяем, есть ли уже такой город в результате
        bool found = false;
        for (int j = 0; j < result.cities.size(); j++) {
            if (result.cities[j] == other.cities[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            result.cities.push_back(other.cities[i]);
        }
        else {
            result.cities.push_back(other.cities[i] + " (новый)");
        }
    }

    cout << "Оператор + выполнен" << endl;
    return result;
}

// Оператор += (ВСЕ города, повторы => "(новый)")
Country& Country::operator+=(const Country& other)
{
    name = name + "-" + other.name;

    if (area < other.area)
        capital = other.capital;

    area += other.area;

    int originalSize = cities.size();

    // Добавляем города из другой страны
    for (int i = 0; i < other.cities.size(); i++) {
        // Проверяем, есть ли уже такой город в текущем списке
        bool found = false;
        for (int j = 0; j < cities.size(); j++) {
            if (cities[j] == other.cities[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            cities.push_back(other.cities[i]);
        }
        else {
            cities.push_back(other.cities[i] + " (новый)");
        }
    }

    cout << "Оператор += выполнен" << endl;
    return *this;
}

// Оператор * (рандом без столиц)
Country Country::operator*(const Country& other)
{
    Country result;

    result.name = "Путь " + name + " -> " + other.name;
    result.capital = "нет";

    if (area < other.area)
        result.area = area;
    else
        result.area = other.area;

    double extra = rand() % 5001;
    result.addTerritory(extra);

    result.cities.push_back(capital);
    result.cities.push_back(other.capital);

    if (cities.size() > 1) {
        int index;
        do {
            index = rand() % cities.size();
        } while (cities[index] == capital);
        result.cities.push_back(cities[index]);
    }

    if (other.cities.size() > 1) {
        int index;
        do {
            index = rand() % other.cities.size();
        } while (other.cities[index] == other.capital);
        result.cities.push_back(other.cities[index]);
    }

    cout << "Оператор * выполнен" << endl;
    return result;
}

// Метод вывода
void Country::print()
{
    cout << "\nНазвание: " << name << endl;
    cout << "Столица: " << capital << endl;
    cout << "Площадь: " << area << " км²" << endl;
    cout << "Города: ";
    for (int i = 0; i < cities.size(); i++)
        cout << cities[i] << " ";
    cout << endl;
}
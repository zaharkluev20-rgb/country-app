#include "city.hpp"

City::City() : name(""), population(0), availableMoney(0)
{
    cout << "  Конструктор City по умолчанию" << endl;
}

City::City(string n, int pop) : name(n), population(pop), availableMoney(0)
{
    cout << "  Конструктор City с параметрами (название+население)" << endl;
}

City::City(string n, int pop, long long money) : name(n), population(pop), availableMoney(money)
{
    cout << "  Конструктор City с параметрами (полный)" << endl;
}

City::City(const City &other) : name(other.name), population(other.population), availableMoney(other.availableMoney)
{
    cout << "  Конструктор копирования City" << endl;
}

City::~City()
{
    cout << "  Деструктор City для города " << name << endl;
}

void City::print() const
{
    cout << "Город: " << name << ", Население: " << population
         << ", Доступно денег: " << availableMoney;
}

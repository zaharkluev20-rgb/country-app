#include "country.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// ==================== КОНСТРУКТОРЫ ====================

Country::Country()
{
    name = "Неизвестно";
    capital = "Нет";
    foundationDate = 0;
    area = 0;
    population = 0;
    cout << "Конструктор Country по умолчанию" << endl;
}

Country::Country(string n, string c, double date, double a, int pop, vector<City> cityList)
{
    name = n;
    capital = c;
    foundationDate = date;
    area = a;
    population = pop;
    cities = cityList;
    cout << "Конструктор Country с параметрами для " << name << endl;
}

Country::Country(const Country& other)
{
    name = other.name;
    capital = other.capital;
    foundationDate = other.foundationDate;
    area = other.area;
    population = other.population;
    cities = other.cities;
    budget = other.budget;
    cout << "Конструктор копирования Country для " << name << endl;
}

Country::~Country()
{
    cities.clear();
    cout << "Деструктор Country для " << name << " выполнился" << endl;
}

// ==================== ГЕТТЕРЫ ====================

string Country::getName() const { return name; }
string Country::getCapital() const { return capital; }
double Country::getFoundationDate() const { return foundationDate; }
double Country::getArea() const { return area; }
int Country::getPopulation() const { return population; }
Budget Country::getBudget() const { return budget; }
vector<City> Country::getCities() const { return cities; }

// ==================== СЕТТЕРЫ ====================

void Country::setName(string n) { name = n; }
void Country::setCapital(string newCapital) { capital = newCapital; }
void Country::setFoundationDate(double date) { foundationDate = date; }
void Country::setArea(double a) { area = a; }
void Country::setPopulation(int pop) { population = pop; }

void Country::setBudget(long long money, double coeff)
{
    budget = Budget(money, coeff);
}

// ==================== МЕТОДЫ ====================

void Country::addBudget(long long amount)
{
    budget.changeBy(amount);
    distributeBudget();
}

void Country::addTerritory(double extraArea)
{
    area += extraArea;
    cout << "Территория увеличена на " << extraArea << ". Новая площадь: " << area << endl;
}

void Country::changePopulation(int delta)
{
    population += delta;
    cout << "Население изменено на " << delta << ". Текущее население: " << population << endl;
}

void Country::printCities() const
{
    cout << "\n--- Города страны " << name << " ---\n";
    for (int i = 0; i < cities.size(); i++) {
        cities[i].print();
        cout << endl;
    }
}

void Country::distributeBudget()
{
    if (cities.empty()) {
        cout << "Нет городов для распределения бюджета!" << endl;
        return;
    }

    long long totalBudget = budget.getMoney();
    double priority = budget.getCoefficient();

    cout << "\n--- РАСПРЕДЕЛЕНИЕ БЮДЖЕТА ---" << endl;
    cout << "Всего бюджет: " << totalBudget << ", Приоритет столицы: x" << priority << endl;

    int capitalIndex = -1;
    for (int i = 0; i < cities.size(); i++) {
        if (cities[i].name == capital) {
            capitalIndex = i;
            break;
        }
    }

    if (capitalIndex == -1) {
        cout << "Столица не найдена в списке городов!" << endl;
        return;
    }

    double totalConditionalPopulation = 0;

    cout << "\nРасчет условного населения:" << endl;
    for (int i = 0; i < cities.size(); i++) {
        if (cities[i].name == capital) {
            double conditional = cities[i].population * priority;
            totalConditionalPopulation += conditional;
            cout << "  " << cities[i].name << " (столица): " << cities[i].population
                << " * " << priority << " = " << conditional << " условных жителей" << endl;
        }
        else {
            totalConditionalPopulation += cities[i].population;
            cout << "  " << cities[i].name << ": " << cities[i].population << " условных жителей" << endl;
        }
    }

    cout << "Всего условных жителей: " << totalConditionalPopulation << endl;

    if (totalConditionalPopulation == 0) {
        cout << "Общее население равно 0!" << endl;
        return;
    }

    cout << "\nВыделение средств:" << endl;
    for (int i = 0; i < cities.size(); i++) {
        double conditionalPopulation;
        if (cities[i].name == capital) {
            conditionalPopulation = cities[i].population * priority;
        }
        else {
            conditionalPopulation = cities[i].population;
        }

        long long cityBudget = (conditionalPopulation / totalConditionalPopulation) * totalBudget;
        cities[i].availableMoney += cityBudget;

        double percent = (conditionalPopulation / totalConditionalPopulation) * 100;
        cout << "  " << cities[i].name << " получает " << cityBudget
            << " (" << conditionalPopulation << " условных жителей, " << percent << "%)" << endl;
    }

    cout << "Бюджет распределен." << endl;
}

// ==================== МЕТОДЫ ДЛЯ РАБОТЫ С ГОРОДАМИ ====================

// findCity - возвращает указатель или 0 (не nullptr, не NULL)
City* Country::findCity(string cityName)
{
    for (int i = 0; i < cities.size(); i++) {
        if (cities[i].name == cityName) {
            return &cities[i];
        }
    }
    return 0;  // возвращаем 0 если не нашли
}

const City* Country::findCity(string cityName) const
{
    for (int i = 0; i < cities.size(); i++) {
        if (cities[i].name == cityName) {
            return &cities[i];
        }
    }
    return 0;  // возвращаем 0 если не нашли
}

void Country::removeCity(string cityName)
{
    for (int i = 0; i < cities.size(); i++) {
        if (cities[i].name == cityName) {
            cities.erase(cities.begin() + i);
            cout << "Город " << cityName << " удален" << endl;
            return;
        }
    }
    cout << "Город " << cityName << " не найден" << endl;
}

void Country::addCity(const City& city)
{
    cities.push_back(city);
    cout << "Город " << city.name << " добавлен" << endl;
}

// ==================== ОПЕРАТОРЫ ====================

Country Country::operator+(const Country& other) const
{
    Country result;
    result.name = name + "-" + other.name;

    if (area < other.area)
        result.capital = other.capital;
    else
        result.capital = capital;

    result.area = area + other.area;
    result.foundationDate = min(foundationDate, other.foundationDate);
    result.population = population + other.population;
    result.setBudget(budget.getMoney() + other.budget.getMoney(),
        max(budget.getCoefficient(), other.budget.getCoefficient()));

    result.cities = cities;

    for (int i = 0; i < result.cities.size(); i++) {
        for (int j = i + 1; j < result.cities.size(); j++) {
            if (result.cities[i].name == result.cities[j].name) {
                result.cities[j].name = result.cities[j].name + " (повтор)";
            }
        }
    }

    for (int i = 0; i < other.cities.size(); i++) {
        bool found = false;
        for (int j = 0; j < result.cities.size(); j++) {
            if (result.cities[j].name == other.cities[i].name) {
                found = true;
                break;
            }
        }

        if (found) {
            City newCity = other.cities[i];
            newCity.name = other.cities[i].name + " (новый)";
            result.cities.push_back(newCity);
        }
        else {
            result.cities.push_back(other.cities[i]);
        }
    }

    cout << "Оператор + выполнен" << endl;
    return result;
}

Country& Country::operator+=(const Country& other)
{
    name = name + "-" + other.name;

    if (area < other.area)
        capital = other.capital;

    area += other.area;
    foundationDate = min(foundationDate, other.foundationDate);
    population += other.population;
    setBudget(budget.getMoney() + other.budget.getMoney(),
        max(budget.getCoefficient(), other.budget.getCoefficient()));

    for (int i = 0; i < cities.size(); i++) {
        for (int j = i + 1; j < cities.size(); j++) {
            if (cities[i].name == cities[j].name) {
                cities[j].name = cities[j].name + " (повтор)";
            }
        }
    }

    for (int i = 0; i < other.cities.size(); i++) {
        bool found = false;
        for (int j = 0; j < cities.size(); j++) {
            if (cities[j].name == other.cities[i].name) {
                found = true;
                break;
            }
        }

        if (found) {
            City newCity = other.cities[i];
            newCity.name = other.cities[i].name + " (новый)";
            cities.push_back(newCity);
        }
        else {
            cities.push_back(other.cities[i]);
        }
    }

    cout << "Оператор += выполнен" << endl;
    return *this;
}

Country Country::operator*(const Country& other) const
{
    Country result;

    result.name = "Путь " + name + " -> " + other.name;
    result.capital = "нет";
    result.foundationDate = (foundationDate + other.foundationDate) / 2;
    result.area = min(area, other.area);
    result.population = (population + other.population) / 2;
    result.setBudget((budget.getMoney() + other.budget.getMoney()) / 2,
        (budget.getCoefficient() + other.budget.getCoefficient()) / 2);

    // Используем findCity с проверкой на 0
    const City* capital1 = findCity(capital);
    if (capital1 != 0) {  // проверка на 0, не на nullptr
        result.cities.push_back(*capital1);
    }
    else {
        result.cities.push_back(City(capital, 0));
    }

    const City* capital2 = other.findCity(other.capital);
    if (capital2 != 0) {
        result.cities.push_back(*capital2);
    }
    else {
        result.cities.push_back(City(other.capital, 0));
    }

    if (cities.size() > 1) {
        int index;
        do {
            index = rand() % cities.size();
        } while (cities[index].name == capital);
        result.cities.push_back(cities[index]);
    }

    if (other.cities.size() > 1) {
        int index;
        do {
            index = rand() % other.cities.size();
        } while (other.cities[index].name == other.capital);
        result.cities.push_back(other.cities[index]);
    }

    cout << "Оператор * выполнен" << endl;
    return result;
}

void Country::print() const
{
    cout << "\n========== ИНФОРМАЦИЯ О СТРАНЕ ==========" << endl;
    cout << "Название: " << name << endl;
    cout << "Столица: " << capital << endl;
    cout << "Дата основания: " << foundationDate << " год" << endl;
    cout << "Площадь: " << area << " км" << char(178) << endl;
    cout << "Население: " << population << " человек" << endl;
    budget.print();
    cout << "Города (" << cities.size() << "):" << endl;
    for (int i = 0; i < cities.size(); i++) {
        cout << "  - ";
        cities[i].print();
        cout << endl;
    }
    cout << "==========================================" << endl;
}
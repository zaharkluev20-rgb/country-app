#include "country.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <clocale>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    vector<Country> countries;

    cout << "\n=== СОЗДАНИЕ СТРАН И ГОРОДОВ ===\n" << endl;

    vector<City> germanCities;
    germanCities.push_back(City("Берлин", 3645000));
    germanCities.push_back(City("Гамбург", 1841000));
    germanCities.push_back(City("Мюнхен", 1472000));
    germanCities.push_back(City("Кёльн", 1086000));
    germanCities.push_back(City("Франкфурт", 753000));

    vector<City> frenchCities;
    frenchCities.push_back(City("Париж", 2148000));
    frenchCities.push_back(City("Марсель", 861635));
    frenchCities.push_back(City("Лион", 513275));
    frenchCities.push_back(City("Тулуза", 479553));
    frenchCities.push_back(City("Ницца", 342637));

    vector<City> japaneseCities;
    japaneseCities.push_back(City("Токио", 13960000));
    japaneseCities.push_back(City("Осака", 2691000));
    japaneseCities.push_back(City("Киото", 1475000));
    japaneseCities.push_back(City("Нагоя", 2320000));
    japaneseCities.push_back(City("Саппоро", 1950000));

    vector<City> italianCities;
    italianCities.push_back(City("Рим", 2873000));
    italianCities.push_back(City("Милан", 1352000));
    italianCities.push_back(City("Неаполь", 967000));
    italianCities.push_back(City("Турин", 870000));
    italianCities.push_back(City("Палермо", 668000));

    vector<City> spainCities;
    spainCities.push_back(City("Мадрид", 3266000));
    spainCities.push_back(City("Барселона", 1620000));
    spainCities.push_back(City("Валенсия", 794000));
    spainCities.push_back(City("Севилья", 688000));
    spainCities.push_back(City("Сарагоса", 675000));

    vector<City> ukCities;
    ukCities.push_back(City("Лондон", 8982000));
    ukCities.push_back(City("Бирмингем", 1141000));
    ukCities.push_back(City("Манчестер", 553000));
    ukCities.push_back(City("Ливерпуль", 498000));
    ukCities.push_back(City("Лидс", 789000));

    countries.push_back(Country("Германия", "Берлин", 1871, 357022, 83100000, germanCities));
    countries.push_back(Country("Франция", "Париж", 843, 551695, 67390000, frenchCities));
    countries.push_back(Country("Япония", "Токио", 660, 377975, 125800000, japaneseCities));
    countries.push_back(Country("Италия", "Рим", 1861, 301340, 60360000, italianCities));
    countries.push_back(Country("Испания", "Мадрид", 1492, 505990, 47350000, spainCities));
    countries.push_back(Country("Великобритания", "Лондон", 1707, 243610, 67800000, ukCities));

    cout << "\n=== УСТАНОВКА НАЧАЛЬНЫХ БЮДЖЕТОВ ===\n" << endl;
    for (int i = 0; i < countries.size(); i++) {
        long long randomMoney = 500000 + (rand() % 2500000);
        double randomCoeff = 1.1 + (rand() % 10) / 10.0;
        countries[i].setBudget(randomMoney, randomCoeff);
        cout << "Страна " << i + 1 << " (" << countries[i].getName() << "): бюджет "
            << randomMoney << ", коэффициент " << randomCoeff << endl;
    }

    int choice;
    do {
        cout << "\n========== МЕНЮ ==========" << endl;
        cout << "1 - Оператор + (рандомные 2 страны)" << endl;
        cout << "2 - Оператор += (рандомные 2 страны)" << endl;
        cout << "3 - Оператор * (рандомные 2 страны)" << endl;
        cout << "4 - Распределить бюджет (рандомная страна)" << endl;
        cout << "5 - Изменить бюджет случайно (рандомная страна)" << endl;
        cout << "6 - Показать все страны" << endl;
        cout << "7 - Присоединить территорию (рандомная страна)" << endl;
        cout << "8 - Изменить население (рандомная страна)" << endl;
        cout << "9 - Установить бюджет (рандомная страна, ручной ввод)" << endl;
        cout << "10 - Добавить бюджет рандомно (рандомная страна)" << endl;
        cout << "11 - Показать города (рандомная страна)" << endl;
        cout << "0 - Выход" << endl;
        cout << "===========================" << endl;
        cout << "Выбор: ";
        cin >> choice;

        if (choice == 1) {
            int i1 = rand() % countries.size();
            int i2 = rand() % countries.size();
            while (i1 == i2) i2 = rand() % countries.size();

            cout << "\n=== РАНДОМНО ВЫБРАНЫ СТРАНЫ ===" << endl;
            cout << "1) " << countries[i1].getName() << endl;
            cout << "2) " << countries[i2].getName() << endl;

            Country result = countries[i1] + countries[i2];
            result.print();
        }
        else if (choice == 2) {
            int i1 = rand() % countries.size();
            int i2 = rand() % countries.size();
            while (i1 == i2) i2 = rand() % countries.size();

            cout << "\n=== РАНДОМНО ВЫБРАНЫ СТРАНЫ ===" << endl;
            cout << "1) " << countries[i1].getName() << endl;
            cout << "2) " << countries[i2].getName() << endl;

            countries[i1] += countries[i2];
            cout << "\nРЕЗУЛЬТАТ (первая страна):" << endl;
            countries[i1].print();
        }
        else if (choice == 3) {
            int i1 = rand() % countries.size();
            int i2 = rand() % countries.size();
            while (i1 == i2) i2 = rand() % countries.size();

            cout << "\n=== РАНДОМНО ВЫБРАНЫ СТРАНЫ ===" << endl;
            cout << "1) " << countries[i1].getName() << endl;
            cout << "2) " << countries[i2].getName() << endl;

            Country result = countries[i1] * countries[i2];
            result.print();
        }
        else if (choice == 4) {
            int randomIndex = rand() % countries.size();
            cout << "\n=== РАНДОМНО ВЫБРАНА СТРАНА: " << countries[randomIndex].getName() << " ===" << endl;
            countries[randomIndex].distributeBudget();
        }
        else if (choice == 5) {
            int randomIndex = rand() % countries.size();
            cout << "\n=== РАНДОМНО ВЫБРАНА СТРАНА: " << countries[randomIndex].getName() << " ===" << endl;
            long long amount = (rand() % 400001) - 200000;
            cout << "Случайное изменение бюджета: " << amount << endl;
            countries[randomIndex].addBudget(amount);
        }
        else if (choice == 6) {
            for (int i = 0; i < countries.size(); i++) {
                cout << "\nСтрана #" << i + 1 << ":";
                countries[i].print();
            }
        }
        else if (choice == 8) {
            int randomIndex = rand() % countries.size();
            cout << "\n=== РАНДОМНО ВЫБРАНА СТРАНА: " << countries[randomIndex].getName() << " ===" << endl;
            double extraArea = 1000 + (rand() % 49000);
            cout << "Присоединение территории: +" << extraArea << " км" << char(178) << endl;
            countries[randomIndex].addTerritory(extraArea);
        }
        else if (choice == 9) {
            int randomIndex = rand() % countries.size();
            cout << "\n=== РАНДОМНО ВЫБРАНА СТРАНА: " << countries[randomIndex].getName() << " ===" << endl;
            int delta = (rand() % 2000001) - 1000000;
            cout << "Изменение населения: " << delta << " человек" << endl;
            countries[randomIndex].changePopulation(delta);
        }
        else if (choice == 10) {
            int randomIndex = rand() % countries.size();
            cout << "\n=== РАНДОМНО ВЫБРАНА СТРАНА: " << countries[randomIndex].getName() << " ===" << endl;
            long long money;
            double coeff;
            cout << "Введите бюджет страны: ";
            cin >> money;
            cout << "Введите коэффициент для столицы (например 1.5): ";
            cin >> coeff;
            countries[randomIndex].setBudget(money, coeff);
            countries[randomIndex].distributeBudget();
            cout << "Бюджет назначен и распределён по городам." << endl;
        }
        else if (choice == 11) {
            int randomIndex = rand() % countries.size();
            cout << "\n=== РАНДОМНО ВЫБРАНА СТРАНА: " << countries[randomIndex].getName() << " ===" << endl;
            long long addMoney = 100000 + (rand() % 400000);
            cout << "Добавление к бюджету: +" << addMoney << endl;
            countries[randomIndex].addBudget(addMoney);
            cout << "Бюджет добавлен и распределён по городам." << endl;
        }
        else if (choice == 12) {
            int randomIndex = rand() % countries.size();
            cout << "\n=== РАНДОМНО ВЫБРАНА СТРАНА: " << countries[randomIndex].getName() << " ===" << endl;
            countries[randomIndex].printCities();
        }
        else if (choice == 0) {
            cout << "\nПрограмма завершена." << endl;
        }
        else {
            cout << "\nНеверный выбор! Попробуйте снова." << endl;
        }
    } while (choice != 0);

    return 0;
}
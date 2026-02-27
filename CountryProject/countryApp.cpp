#include "Country.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <clocale>
#include <cstdlib>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    vector<Country> countries;

    countries.push_back(Country("Германия", "Берлин", 357022, { "Берлин", "Гамбург", "Мюнхен" }));
    countries.push_back(Country("Франция", "Париж", 551695, { "Париж", "Марсель", "Лион" }));
    countries.push_back(Country("Япония", "Токио", 377975, { "Токио", "Осака", "Киото" }));
    countries.push_back(Country("Италия", "Рим", 301340, { "Рим", "Милан", "Неаполь" }));

    int choice;

    do
    {
        cout << "\n=== МЕНЮ ===\n";
        cout << "1 - Оператор +\n";
        cout << "2 - Оператор +=\n";
        cout << "3 - Оператор *\n";
        cout << "0 - Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        if (choice >= 1 && choice <= 3)
        {
            int i1 = rand() % countries.size();
            int i2 = rand() % countries.size();

            while (i1 == i2)
                i2 = rand() % countries.size();

            cout << "\nВыбраны страны:\n";
            countries[i1].print();
            countries[i2].print();

            if (choice == 1)
            {
                Country result = countries[i1] + countries[i2];
                cout << "\n--- РЕЗУЛЬТАТ СЛОЖЕНИЯ (+) ---";
                result.print();
            }
            else if (choice == 2)
            {
                countries[i1] += countries[i2];
                cout << "\n--- РЕЗУЛЬТАТ СЛОЖЕНИЯ С ПРИСВОЕНИЕМ (+=) ---";
                countries[i1].print();
            }
            else if (choice == 3)
            {
                Country result = countries[i1] * countries[i2];
                cout << "\n--- РЕЗУЛЬТАТ УМНОЖЕНИЯ (*) ---";
                result.print();
            }
        }

    } while (choice != 0);

    cout << "\nПрограмма завершена.\n";
    return 0;
}
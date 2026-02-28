#include "Country.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <clocale>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    vector<Country> countries;

    // Создание стран
    countries.push_back(Country("Германия", "Берлин", 357022, { "Берлин", "Гамбург", "Мюнхен" }));
    countries.push_back(Country("Франция", "Париж", 551695, { "Париж", "Марсель", "Лион" }));
    countries.push_back(Country("Япония", "Токио", 377975, { "Токио", "Осака", "Киото" }));
    countries.push_back(Country("Италия", "Рим", 301340, { "Рим", "Милан", "Неаполь" }));

    cout << "\n=== СОЗДАННЫЕ СТРАНЫ ===" << endl;
    for (int i = 0; i < countries.size(); i++) {
        cout << "\nСтрана #" << i + 1 << ":";
        countries[i].print();
    }

    int choice;

    do
    {
        cout << "\n========== МЕНЮ ==========" << endl;
        cout << "1 - Оператор + (объединение)" << endl;
        cout << "2 - Оператор += (присоединение)" << endl;
        cout << "3 - Оператор * (рандомное путешествие)" << endl;
        cout << "4 - Показать все страны" << endl;
        cout << "0 - Выход" << endl;
        cout << "===========================" << endl;
        cout << "Выбор: ";
        cin >> choice;

        if (choice == 4)
        {
            for (int i = 0; i < countries.size(); i++)
            {
                cout << "\nСтрана #" << i + 1 << ":";
                countries[i].print();
            }
        }
        else if (choice >= 1 && choice <= 3)
        {
            // Выбираем две разные страны
            int i1 = rand() % countries.size();
            int i2 = rand() % countries.size();
            while (i1 == i2)
                i2 = rand() % countries.size();

            cout << "\nВЫБРАНЫ СТРАНЫ:" << endl;
            cout << "1) ";
            countries[i1].print();
            cout << "2) ";
            countries[i2].print();

            if (choice == 1)
            {
                cout << "\n--- РЕЗУЛЬТАТ ОПЕРАТОРА + ---" << endl;
                Country result = countries[i1] + countries[i2];
                result.print();
            }
            else if (choice == 2)
            {
                cout << "\n--- РЕЗУЛЬТАТ ОПЕРАТОРА += ---" << endl;
                countries[i1] += countries[i2];
                cout << "\nРЕЗУЛЬТАТ (первая страна):" << endl;
                countries[i1].print();
            }
            else if (choice == 3)
            {
                cout << "\n--- РЕЗУЛЬТАТ ОПЕРАТОРА * ---" << endl;
                Country result = countries[i1] * countries[i2];
                result.print();
            }
        }

    } while (choice != 0);

    cout << "\nПрограмма завершена." << endl;

    return 0;
}
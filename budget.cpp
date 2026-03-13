#include "budget.h"

Budget::Budget() : money(0), coefficient(1.0) {
    cout << "Конструктор Budget по умолчанию" << endl;
}

Budget::Budget(long long m, double coeff) : money(m), coefficient(coeff) {
    cout << "Конструктор Budget с параметрами" << endl;
}

Budget::Budget(const Budget& other) : money(other.money), coefficient(other.coefficient) {
    cout << "Конструктор копирования Budget" << endl;
}

Budget::~Budget() {
    cout << "Деструктор Budget" << endl;
}

long long Budget::getMoney() const { return money; }
double Budget::getCoefficient() const { return coefficient; }
void Budget::setMoney(long long m) { money = m; }
void Budget::setCoefficient(double coeff) { coefficient = coeff; }

void Budget::changeBy(long long amount) {
    money += amount;
    cout << "Бюджет изменен на " << amount << ". Текущий бюджет: " << money << endl;
}

void Budget::print() const {
    cout << "\n--- Информация о бюджете ---\n";
    cout << "Всего денег: " << money << "\n";
    cout << "Коэффициент столицы: " << coefficient << "\n";
}
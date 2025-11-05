#include <iostream>
#include <cmath>

int main() {
    using namespace std;

    int func_number;

    cout << "Выберете функцию по номеру (sh(x): 1, x^2: 2 , e^x: 3): ";
    if (!(cin >> func_number)) {
        cout << "Ошибка: Требуется числовое значение" << endl;
        return 1;
    }

    double x, y;

    cout << "Введите значение x: ";
    if (!(cin >> x)) {
        cout << "Ошибка: Требуется числовое значение" << endl;
        return 1;
    }

    cout << "Введите значение y: ";
    if (!(cin >> y)) {
        cout << "Ошибка: Требуется числовое значение" << endl;
        return 1;
    }

    double func_value;

    switch (func_number) {
        case 1: {
            // Функция sh(x)
            func_value = sinh(x);
            break;
        }
        case 2: {
            // Функция x^2
            func_value = pow(x, 2);
            break;
        }
        case 3: {
            // Функция e^x
            func_value = exp(x);
            break;
        }
    }

    double res;
    int selected_branch;

    // Расчет резульата в зависимости от значения y * f(x)
    if (func_value * y == 10) {
        res = log(x) - pow(func_value, 2);
        selected_branch = 1;
    } else if (func_value * y < 10) {
        res = 2 * y - 10 * sin(x);
        selected_branch = 2;
    } else {
        res = pow(y, 2) + pow(func_value, 2);
        selected_branch = 3;
    }

    cout << "Результат: " << res << endl;
    cout << "Выбранная ветка: " << selected_branch << endl;
}
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

    int selected_branch;
    double x, y, result;

    switch (func_number) {
        // Функция гиперболического синуса
        case 1: {
            cout << "Введите значение x: ";
            if (!(cin >> x)) {
                cout << "Ошибка: Требуется числовое значение" << endl;
                return 1;
            }

            cout << "Введите значение y: ";
            if (!(cin >> x)) {
                cout << "Ошибка: Требуется числовое значение" << endl;
                return 1;
            }

            double condition_val = y * sinh(x);

            if (condition_val == 10) {
                result = log(x) - pow(sinh(x), 2);
                selected_branch = 1;
            } else if (condition_val < 10) {
                result = 2 * y - 10 * sin(x);
                selected_branch = 2;
            } else {
                result = pow(y, 2) + pow(sinh(x), 2);
                selected_branch = 3;
            }

            break;
        }

        // Функция возведения числа в квадрат
        case 2: {
            cout << "Введите значение x: ";
            if (!(cin >> x)) {
                cout << "Ошибка: Требуется числовое значение" << endl;
                return 1;
            }

            cout << "Введите значение y: ";
            if (!(cin >> x)) {
                cout << "Ошибка: Требуется числовое значение" << endl;
                return 1;
            }

            double condition_val = y * pow(x, 2);

            if (condition_val == 10) {
                result = log(x) - pow(x, 4);
                selected_branch = 1;
            } else if (condition_val < 10) {
                result = 2 * y - 10 * sin(x);
                selected_branch = 2;
            } else {
                result = pow(y, 2) + pow(x, 4);
                selected_branch = 3;
            }

            break;
        }

        // Экспоненциальная функция
        case 3: {
            cout << "Введите значение x: ";
            if (!(cin >> x)) {
                cout << "Ошибка: Требуется числовое значение" << endl;
                return 1;
            }

            cout << "Введите значение y: ";
            if (!(cin >> x)) {
                cout << "Ошибка: Требуется числовое значение" << endl;
                return 1;
            }

            double condition_val = y * exp(x);

            if (condition_val == 10) {
                result = log(x) - pow(exp(x), 2);
                selected_branch = 1;
            } else if (condition_val < 10) {
                result = 2 * y - 10 * sin(x);
                selected_branch = 2;
            } else {
                result = pow(y, 2) + pow(exp(x), 2);
                selected_branch = 3;
            }

            break;
        }

        default: {
            cout << "Ошибка: Некорректный номер функции" << endl;
            return 1;
        }
    }

    cout << "Результат: " << result << endl;
    cout << "Выполняемая ветвь: " << selected_branch << endl;

    return 0;
}
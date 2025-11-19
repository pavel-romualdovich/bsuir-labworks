#include <iostream>
#include "math_functions.h"

const int STEPS = 10;

int main() {
    using namespace std;

    double left_border;

    cout << "Введите начальное значение: ";
    if (!(cin >> left_border)) {
        cout << "Ошибка: Требуется числовое значение" << endl;
        return 1;
    }

    double right_border = -0.1;

    cout << "Введите конечное значение: ";
    if (!(cin >> right_border)) {
        cout << "Ошибка: Требуется числовое значение" << endl;
        return 1;
    }

    double step = (right_border - left_border) / STEPS;

    cout << "=============================================" << endl;
    cout << "Таблица значений cos(x)^3 и ряда Тейлора s(x)" << endl;
    cout << "=============================================" << endl;
    cout << "     x     |     cos(x)^3     |     s(x)     " << endl;
    cout << "---------------------------------------------" << endl;

    for (int i = 0; i <= STEPS; i++) {
        double x = left_border + step * i;

        cout << x << "     |     " << pow(cos(x), 3) << "     |     ";
        cout << get_taylor_cos_cubed(x) << endl;
    }

    return 0;
}
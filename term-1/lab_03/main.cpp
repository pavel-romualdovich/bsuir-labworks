#include <iostream>
#include <iomanip>
#include <cmath>

double EPS = 10e-15;

int main () {
    using namespace std;

    double left_border;

    cout << "Введите начальное значение: ";
    if (!(cin >> left_border)) {
        cout << "Ошибка: Требуется числовое значение" << endl;
        return 0;
    }

    double right_border;

    cout << "Введите конечное значение: ";
    if (!(cin >> right_border)) {
        cout << "Ошибка: Требуется числовое значение" << endl;
        return 1;
    }

    int row_size = 140;
    double step = (right_border - left_border) / 10;

    cout << "============================================" << endl;
    cout << "Таблица значений xcos(x) и ряда Тейлора s(x)" << endl;
    cout << "============================================" << endl;
    cout << "     x     |     xcos(x)     |     s(x)     " << endl;
    cout << "--------------------------------------------" << endl;

    for (int i = 0; i < 11; i++) {
        double x = left_border + i * step;
        double x_cosx = x * cos(x);

        abs(x) < EPS? cout << 0: cout << x; // Проверка на число, близкое к нулю
        cout << "     |     " << setw(10);
        abs(x_cosx) < EPS? cout << 0: cout << x_cosx; // Проверка на число, близкое к нулю
        cout << "     |     " << setw(10);

        double taylor_value = x;
        double tmp = x;

        // Расчет значения ряда Тейлора
        for (int n = 1; n <= row_size; n++) {
            tmp = -tmp * pow(x, 2) / (2 * n * (2 * n - 1));
            taylor_value += tmp;
        }

        abs(taylor_value) < EPS? cout << 0: cout << taylor_value; // Проверка на число, близкое к нулю
        cout << endl;
    }

    return 0;
}
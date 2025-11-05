#include <iostream>
#include <iomanip>
#include <cmath>

double EPS = 10e-15;
int TABLE_ROWS = 10;

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
    double step = (right_border - left_border) / TABLE_ROWS;

    cout << "\n";
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║ Таблица значений xcos(x) и ряда Тейлора s(x) ║" << endl;
    cout << "╠══════════════╦═════════════════╦═════════════╣" << endl;
    cout << "║      x       ║     xcos(x)     ║     s(x)    ║" << endl;
    cout << "╠══════════════╬═════════════════╬═════════════╣" << endl;

    for (int i = 0; i < TABLE_ROWS; i++) {
        double x = left_border + step * i;
        double x_cosx = x * cos(x);

        cout << "║ ";

        if (abs(x) < EPS) {
            cout << setw(12) << "0";
        } else {
            cout << setw(12) << fixed << setprecision(6) << x;
        }
        cout << " ║ ";

        // Вывод x*cos(x)
        if (abs(x_cosx) < EPS) {
            cout << setw(15) << "0";
        } else {
            cout << setw(15) << fixed << setprecision(6) << x_cosx;
        }
        cout << " ║ ";

        double taylor_value = x;
        double tmp = x;

        // Расчет значения ряда Тейлора
        for (int n = 1; n <= row_size; n++) {
            tmp = -tmp * pow(x, 2) / (2 * n * (2 * n - 1));
            taylor_value += tmp;
        }

        // Вывод ряда Тейлора
        if (abs(taylor_value) < EPS) {
            cout << setw(11) << "0";
        } else {
            cout << setw(11) << fixed << setprecision(6) << taylor_value;
        }
        cout << " ║" << endl;
    }

    cout << "╚══════════════╩═════════════════╩═════════════╝" << endl;
    cout << endl;

    return 0;
}
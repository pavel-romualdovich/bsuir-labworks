#include <iostream>

const int MAX_ARR_SIZE = 1005;

int main() {
    using namespace std;

    int n, m;

    cout << "Введите количество строк матрицы (от 1 до 1000): ";
    if (!(cin >> n)) {
        cout << "Ошибка: Требуется числовое значение" << endl;
        return 1;
    }

    if (n < 1 || n > 1000) {
        cout << "Ошибка: Требуется корректное количество элементов" << endl;
        return 1;
    }

    cout << "Введите количество столбцов матрицы (от 1 до 1000): ";
    if (!(cin >> m)) {
        cout << "Ошибка: Требуется чиcловое значение" << endl;
        return 1;
    }

    if (m < 1 || m > 1000) {
        cout << "Ошибка: Требуется корректное количество элементов" << endl;
        return 1;
    }

    int arr[MAX_ARR_SIZE][MAX_ARR_SIZE];

    cout << "Введите матрицу, содержащую " << n << " строк и "
         << m << " столбцов:" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!(cin >> arr[i][j])) {
                cout << "Ошибка: Требуется числовое значение" << endl;
                return 1;
            }
        }
    }

    int res = 0;

    for (int i = 0; i < n; i++) {
        // Подсчет суммы элементов строки матрицы
        int line_sum = 0;

        for (int j = 0; j < m; j++) {
            line_sum += arr[i][j];
        }

        // Подсчет "особых" элементов
        for (int j = 0; j < m; j++) {
            if (arr[i][j] < line_sum - arr[i][j]) {
                res++;
            }
        }
    }

    cout << "Количество «особых» элементов матрицы: " << res << endl;

    return 0;
}
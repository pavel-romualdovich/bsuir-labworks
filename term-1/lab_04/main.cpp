#include <iostream>

const int MAX_ARR_SIZE = 1005;

int main() {
    using namespace std;

    int els_count;

    cout << "Введите количество элементов (от 1 до 1000): ";
    if (!(cin >> els_count)) {
        cout << "Ошибка: Требуется числовое значение" << endl;
        return 1;
    }

    if (els_count < 1 || els_count > 1000) {
        cout << "Ошибка: Требуется корректное количество элементов" << endl;
        return 1;
    }

    int arr[MAX_ARR_SIZE];

    cout << "Введите элементы, количество которых равно " << els_count << ": ";
    for (int i = 0; i < els_count; i++) {
        if (!(cin >> arr[i])) {
            cout << "Ошибка: Требуется числовое значение" << endl;
            return 1;
        }
    }

    // Поиск максимума в массиве
    int max_val = arr[0];
    int max_val_id = 0;

    for (int i = 1; i < els_count; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
            max_val_id = i;
        }
    }

    // Замещение элементов, меньших макимального
    for (int i = 0, j = max_val_id; j < els_count; i++, j++) arr[i] = arr[j];

    // Вывод массива
    for (int i = 0; i < els_count - max_val_id; i++) cout << arr[i] << ' ';
    cout << endl;

    return 0;
}
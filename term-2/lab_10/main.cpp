#include <iostream>

int get_increment_sum(int, int);
int get_increment_sum_recursive(int, int);

int main() {
    using namespace std;

    int first_num, second_num;

    cout << "Введите 2 целых числа для сложения: ";
    cin >> first_num >> second_num;

    cout << "Результат работы нерекурсивной функции суммы: "
         << get_increment_sum(first_num, second_num) << endl;
    cout << "Результат работы рекурсивной функции суммы: "
         << get_increment_sum_recursive(first_num, second_num) << endl;

    return 0;
}

int get_increment_sum(int first_number, int second_number) {
    int sum = first_number;

    if (second_number > 0) {
        for (int i = 0; i < second_number; i++) sum++;
    } else {
        for (int i = second_number; i < 0; i++) sum--;
    }

    return sum;
}

int get_increment_sum_recursive(int first_number, int second_number) {
    if (second_number == 0) return first_number;
    if (second_number > 0) {
        return get_increment_sum_recursive(first_number + 1, second_number - 1);
    } else {
        return get_increment_sum_recursive(first_number - 1, second_number + 1);
    }
}
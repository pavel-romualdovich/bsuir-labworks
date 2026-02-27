#include "input.hpp"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>

const int MAX_COUNT = 1000;

void print_command_list() {
    using namespace std;

    cout << "Список команд:\n"
         << "  " << INPUT_CARS_DATA << " - добавить записи автомобилей\n"
         << "  " << OUTPUT_CARS_DATA << " - вывести все записи\n"
         << "  " << EXIT << " - завершить работу программы\n\n";
}

int parse_command_number() {
    using namespace std;

    int command_number;

    cout << "Введите команду (0 для списка команд)\n> ";
    cin >> command_number;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << endl;

    return command_number;
}

void output_cars_data(Car *cars, int count) {
    using namespace std;

    if (count == 0) {
        cout << "  записи отсутствуют\n\n";
        return;
    }

    int destination_number = parse_destination_number();

    switch (destination_number) {
        case TEXT_FILE:
            cout << "  ✗ данная функция пока не реализована\n\n";
            break;
        case TERMINAL:
            print_cars_data(cars, count);
            break;
        default:
            cout << "  ✗ неверный номер устройства вывода\n\n";
    }
}

void print_cars_data(Car *cars, int count) {
    using namespace std;

    cout << "┌─────┬────────────────────┬────────────┬──────┬────────────┬────────────┐\n"
         << "│  №  │       Марка        │  № кузова  │ Год  │ Объем (л)  │ Скорость   │\n"
         << "├─────┼────────────────────┼────────────┼──────┼────────────┼────────────┤\n";

    for (int i = 0; i < count; i++) {
        cout << "│ " << left
             << setw(3) << i + 1 << " │ "
             << setw(18) << cars[i].brand << " │ "
             << setw(10) << cars[i].body_number << " │ "
             << setw(4) << cars[i].year << " │ "
             << setw(10) << fixed << setprecision(1) << cars[i].engine_volume << " │ "
             << setw(10) << cars[i].max_speed << " │\n";

        if (i < count - 1) {
            cout << "├─────┼────────────────────┼────────────┼──────┼────────────┼────────────┤\n";
        }
    }

    cout << "└─────┴────────────────────┴────────────┴──────┴────────────┴────────────┘\n"
         << "Всего записей: " << count << "\n\n";
}

int parse_destination_number() {
    using namespace std;

    int destination_number;
    cout << "Выберите устройство вывода:\n"
         << "  " << TEXT_FILE << " - текстовый файл\n"
         << "  " << TERMINAL << " - терминал (на экран)\n"
         << "> ";
    cin >> destination_number;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << endl;

    return destination_number;
}

void input_cars_data(Car **cars, int *count) {
    using namespace std;

    int source_number;
    source_number = parse_source_number();

    switch (source_number) {
        case TEXT_FILE:
            cout << "  ✗ данная функция пока не реализована\n\n";
            break;
        case TERMINAL:
            input_cars_data_from_terminal(cars, count);
            break;
        default:
            cout << "  ✗ неверный номер устройства ввода\n\n";
    }
}

void input_cars_data_from_terminal(Car **cars, int *count) {
    using namespace std;

    int additional_count;

    cout << "Добавление записей: " << *count << "/" << MAX_COUNT;

    cout << "\nВведите количество записей для добавления\n> ";
    cin >> additional_count;

    while (cin.fail() || additional_count < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  ✗ неверный ввод: требуется положительное число\n> ";
        cin >> additional_count;
    }

    while (*count + additional_count > MAX_COUNT) {
        cout << "  ✗ неверный ввод: максимум можно добавить "
             << MAX_COUNT - *count << "\n>";
        cin >> additional_count;

        while (cin.fail() || additional_count < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  ✗ неверный ввод: требуется положительное число\n>";
            cin >> additional_count;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Car *temp = (Car *)realloc(*cars, (*count + additional_count) * sizeof(Car));
    if (temp == nullptr) {
        cout << "\n  ✗ ошибка: не удалось выделить память\n"
             << "  данные не будут добавлены\n\n";
        return;
    }
    *cars = temp;

    for (int i = 0; i < additional_count; i++) {
        cout << "\n--- №" << *count + i + 1 << " ---\n";
        Car car = input_car_data_from_terminal();
        (*cars)[*count + i] = car;
    }

    *count += additional_count;

    cout << "\n  ✓ добавлено " << additional_count << " записей\n"
         << "  всего записей: " << *count << "\n\n";
}

Car input_car_data_from_terminal() {
    using namespace std;

    Car car;

    cout << "  марка автомобиля\n> ";
    cin.getline(car.brand, 50);

    cout << "  номер кузова\n> ";
    cin.getline(car.body_number, 20);

    cout << "  год выпуска\n> ";
    cin >> car.year;

    while (cin.fail() || car.year < 1900 || car.year > 2025) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  ✗ неверный ввод: допустимый диапазон 1900-2025\n> ";
        cin >> car.year;
    }

    cout << "  объем двигателя (л)\n> ";
    cin >> car.engine_volume;

    while (cin.fail() || car.engine_volume <= 0 || car.engine_volume > 20) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  ✗ неверный ввод: допустимый диапазон 0.1-20.0\n> ";
        cin >> car.engine_volume;
    }

    cout << "  максимальная скорость (км/ч)\n> ";
    cin >> car.max_speed;

    while (cin.fail() || car.max_speed <= 0 || car.max_speed > 500) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  ✗ некорректный ввод: допустимый диапазон 0-500 ";
        cin >> car.max_speed;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return car;
}

int parse_source_number() {
    using namespace std;

    int source_number;
    cout << "Выберите источник ввода:\n"
         << "  " << TEXT_FILE << " - текстовый файл\n"
         << "  " << TERMINAL << " - терминал (с клавиатуры)\n"
         << "> ";
    cin >> source_number;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << endl;

    return source_number;
}
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>

#include "input.hpp"

#include "search_algs.hpp"

const int MAX_COUNT = 1000;

void print_command_list() {
    using namespace std;

    cout << "Список команд:\n"
         << "  " << INPUT_CARS_DATA << " - добавить записи автомобилей\n"
         << "  " << OUTPUT_CARS_DATA << " - вывести все записи\n"
         << "  " << SORT_CARS_DATA << " - отсортировать записи по ключу\n"
         << "  " << SEARCH_CAR_DATA << " - найти конкретную запись\n"
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

void output_cars_data(CarCollection *collection) {
    using namespace std;

    if (collection->count == 0) {
        cout << "  записи отсутствуют\n\n";
        return;
    }

    int destination_number = parse_destination_number();

    switch (destination_number) {
        case TEXT_FILE:
            cout << "  ✗ данная функция пока не реализована\n\n";
            break;
        case TERMINAL:
            print_cars_data(collection);
            break;
        default:
            cout << "  ✗ неверный номер устройства вывода\n\n";
    }
}

void print_cars_data(CarCollection *collection) {
    using namespace std;

    cout << "┌─────┬────────────────────┬────────────┬──────┬────────────┬────────────┐\n"
         << "│  №  │       Марка        │  № кузова  │ Год  │ Объем (л)  │ Скорость   │\n"
         << "├─────┼────────────────────┼────────────┼──────┼────────────┼────────────┤\n";

    for (int i = 0; i < collection->count; i++) {
        cout << "│ " << left
             << setw(3) << i + 1 << " │ "
             << setw(18) << collection->data[i].brand << " │ "
             << setw(10) << collection->data[i].body_number << " │ "
             << setw(4) << collection->data[i].year << " │ "
             << setw(10) << fixed << setprecision(1) << collection->data[i].engine_volume << " │ "
             << setw(10) << collection->data[i].max_speed << " │\n";

        if (i < collection->count - 1) {
            cout << "├─────┼────────────────────┼────────────┼──────┼────────────┼────────────┤\n";
        }
    }

    cout << "└─────┴────────────────────┴────────────┴──────┴────────────┴────────────┘\n"
         << "Всего записей: " << collection->count << "\n\n";

    if (collection->sorted_by != NOT_SORTED) {
        cout << "Коллекция отсортирована по: ";
        switch (collection->sorted_by) {
            case BY_YEAR:
                cout << "году выпуска";
                break;
            case BY_ENGINE_VOLUME:
                cout << "объему двигателя";
                break;
            case BY_MAX_SPEED:
                cout << "максимальной скорости";
                break;
            default:
                break;
        }
        cout << "\n\n";
    }
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

void input_cars_data(CarCollection *collection) {
    using namespace std;

    int source_number = parse_source_number();

    switch (source_number) {
        case TEXT_FILE:
            cout << "  ✗ данная функция пока не реализована\n\n";
            break;
        case TERMINAL:
            input_cars_data_from_terminal(collection);
            break;
        default:
            cout << "  ✗ неверный номер устройства ввода\n\n";
    }
}

void input_cars_data_from_terminal(CarCollection *collection) {
    using namespace std;

    int additional_count;

    cout << "Добавление записей: " << collection->count << "/" << MAX_COUNT;

    cout << "\nВведите количество записей для добавления\n> ";
    cin >> additional_count;

    while (cin.fail() || additional_count < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  ✗ неверный ввод: требуется положительное число\n> ";
        cin >> additional_count;
    }

    while (collection->count + additional_count > MAX_COUNT) {
        cout << "  ✗ неверный ввод: максимум можно добавить "
             << MAX_COUNT - collection->count << "\n>";
        cin >> additional_count;

        while (cin.fail() || additional_count < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  ✗ неверный ввод: требуется положительное число\n>";
            cin >> additional_count;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Car *temp = (Car *)realloc(collection->data, (collection->count + additional_count) * sizeof(Car));
    if (temp == nullptr) {
        cout << "\n  ✗ ошибка: не удалось выделить память\n"
             << "  данные не будут добавлены\n\n";
        return;
    }
    collection->data = temp;

    for (int i = 0; i < additional_count; i++) {
        cout << "\n---------------------- №"
             << collection->count + i + 1
             << " ----------------------\n";
        Car car = input_car_data_from_terminal();
        collection->data[collection->count + i] = car;
    }

    collection->count += additional_count;
    collection->sorted_by = NOT_SORTED;

    cout << "\n  ✓ добавлено " << additional_count << " записей\n"
         << "  всего записей: " << collection->count << "\n\n";
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
        cout << "  ✗ неверный ввод: допустимый диапазон 0-500\n> ";
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

int parse_sort_key() {
    using namespace std;

    int sort_key;
    cout << "Выберите поле сортировки:\n"
         << "  " << BY_YEAR << " - год выпуска\n"
         << "  " << BY_ENGINE_VOLUME << " - объем двигателя\n"
         << "  " << BY_MAX_SPEED << " - максимальная скорость\n"
         << "> ";
    cin >> sort_key;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << endl;

    return sort_key;
}

void output_car_data(Car car) {
    using namespace std;

    cout << "\n┌──────────────────────────────────────────────────────────────────┐\n"
         << "│ Найденная запись:                                                  │\n"
         << "├──────────────────────────────────────────────────────────────────┤\n"
         << "│ Марка: " << left << setw(50) << car.brand << "│\n"
         << "│ Номер кузова: " << setw(47) << car.body_number << "│\n"
         << "│ Год выпуска: " << setw(47) << car.year << "│\n"
         << "│ Объем двигателя: " << fixed << setprecision(1) << setw(44) << car.engine_volume << " л │\n"
         << "│ Максимальная скорость: " << setw(39) << car.max_speed << " км/ч │\n"
         << "└──────────────────────────────────────────────────────────────────┘\n\n";
}

int parse_search_field() {
    using namespace std;

    cout << "Выберите поле для поиска:\n";
    cout << "  " << SEARCH_BY_YEAR << " - по году выпуска\n";
    cout << "  " << SEARCH_BY_ENGINE_VOLUME << " - по объему двигателя\n";
    cout << "  " << SEARCH_BY_MAX_SPEED << " - по максимальной скорости\n";
    cout << "> ";

    int search_field;
    cin >> search_field;

    return search_field;
}

double parse_search_key(int field) {
    using namespace std;

    double value;

    switch (field) {
        case SEARCH_BY_YEAR:
            cout << "Введите год выпуска для поиска\n> ";
            break;
        case SEARCH_BY_ENGINE_VOLUME:
            cout << "Введите объем двигателя для поиска\n> ";
            break;
        case SEARCH_BY_MAX_SPEED:
            cout << "Введите максимальную скорость для поиска\n> ";
            break;
    }

    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  ✗ неверный ввод: требуется числовое значение\n> ";
    }

    return value;
}
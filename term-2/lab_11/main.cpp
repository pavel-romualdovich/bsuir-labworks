#include <iostream>

#include "car.hpp"
#include "input.hpp"
#include "sort_algs.hpp"

int main() {
    Car *cars = nullptr;
    int count = 0;

    while (1) {
        int command_number;
        command_number = parse_command_number();

        switch (command_number) {
            case PRINT_COMMAND_LIST:
                print_command_list();
                break;
            case INPUT_CARS_DATA:
                input_cars_data(&cars, &count);
                break;
            case OUTPUT_CARS_DATA:
                output_cars_data(cars,count);
                break;
            case SORT_CARS_DATA:
                sort_cars_data(cars, count);
                break;
            case EXIT:
                free(cars);
                return 0;
            default:
                std::cout << "\n  ✗ неверный номер команды";
        }
    }
}
#include <iostream>

#include "car.hpp"
#include "input.hpp"
#include "sort_algs.hpp"
#include "search_algs.hpp"

int main() {
    CarCollection collection = {nullptr, 0, NOT_SORTED};

    while (1) {
        int command_number = parse_command_number();

        switch (command_number) {
            case PRINT_COMMAND_LIST:
                print_command_list();
                break;
            case INPUT_CARS_DATA:
                input_cars_data(&collection);
                break;
            case OUTPUT_CARS_DATA:
                output_cars_data(&collection);
                break;
            case SORT_CARS_DATA:
                sort_cars_data(&collection);
                break;
            case SEARCH_CAR_DATA:
                search_car_data(&collection);
                break;
            case EXIT:
                free(collection.data);
                return 0;
            default:
                std::cout << "\n  ✗ неверный номер команды";
        }
    }
}
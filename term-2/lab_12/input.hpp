#pragma once

#include "car.hpp"

enum IODevice {
    TERMINAL = 1,
    TEXT_FILE
};

enum Command {
    PRINT_COMMAND_LIST = 0,
    INPUT_CARS_DATA,
    OUTPUT_CARS_DATA,
    SORT_CARS_DATA,
    SEARCH_CAR_DATA,
    EXIT
};

const int YEAR = 1;
const int ENGINE_VOLUME = 2;
const int MAX_SPEED = 3;

int parse_command_number();
int parse_destination_number();
int parse_source_number();
int parse_sort_key();
double parse_search_key(int field);
int parse_search_field();

void input_cars_data(CarCollection *);
void output_cars_data(CarCollection *);
void output_car_data(Car);
void print_command_list();
void print_cars_data(CarCollection *);
void input_cars_data_from_terminal(CarCollection *);
Car input_car_data_from_terminal();
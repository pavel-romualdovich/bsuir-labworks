#pragma once

#include "car.hpp"

enum IODevice{
    TERMINAL,
    TEXT_FILE
};

enum Command {
    PRINT_COMMAND_LIST = 0,
    INPUT_CARS_DATA,
    OUTPUT_CARS_DATA,
    EXIT
};

int parse_command_number();
int parse_destination_number();
void input_cars_data(Car **, int *);
void output_cars_data(Car *, int);
void print_command_list();
void print_cars_data(Car *, int);
int parse_source_number();
void input_cars_data_from_terminal(Car **, int *);
Car input_car_data_from_terminal();
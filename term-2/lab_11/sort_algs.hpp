#pragma once

#include "car.hpp"

enum SortType {
    QUICK_SORT,
    SELECTION_SORT
};

void sort_cars_data(Car *, int);
void sort_cars_data_by(Car *, int, int(Car, Car));
void selection_sort(Car *, int, int(Car, Car));
void quick_sort(Car *, int, int, int(Car, Car));
int cmp_cars_by_max_speed(Car, Car);
int cmp_cars_by_year(Car, Car);
int cmp_cars_by_engine_volume(Car, Car);
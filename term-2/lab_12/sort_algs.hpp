#pragma once

#include "car.hpp"

enum SortAlgorythm {
    QUICK_SORT,
    SELECTION_SORT
};

void sort_cars_data(CarCollection *);
void sort_cars_data_by(CarCollection *, int cmp(Car, Car));
void selection_sort(Car *, int, int cmp(Car, Car));
void quick_sort(Car *, int, int, int cmp(Car, Car));
int cmp_cars_by_max_speed(Car, Car);
int cmp_cars_by_year(Car, Car);
int cmp_cars_by_engine_volume(Car, Car);
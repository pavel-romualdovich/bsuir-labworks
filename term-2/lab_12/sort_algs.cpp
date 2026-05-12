#include "sort_algs.hpp"

#include <iostream>
#include <cstdlib>
#include "car.hpp"
#include "input.hpp"

const SortAlgorythm SORT_ALGORYTHM = QUICK_SORT;

void sort_cars_data(CarCollection *collection) {
    using namespace std;

    int sort_key = parse_sort_key();

    switch (sort_key) {
        case BY_MAX_SPEED:
            sort_cars_data_by(collection, cmp_cars_by_max_speed);
            collection->sorted_by = BY_MAX_SPEED;
            break;
        case BY_ENGINE_VOLUME:
            sort_cars_data_by(collection, cmp_cars_by_engine_volume);
            collection->sorted_by = BY_ENGINE_VOLUME;
            break;
        case BY_YEAR:
            sort_cars_data_by(collection, cmp_cars_by_year);
            collection->sorted_by = BY_YEAR;
            break;
        default:
            cout << "\n  ✗ нет такого поля сортировки\n\n";
            return;
    }

    cout << "\n  ✓ успешно отсортировано\n\n";
}

int cmp_cars_by_max_speed(Car car1, Car car2) {
    return car1.max_speed - car2.max_speed;
}

int cmp_cars_by_engine_volume(Car car1, Car car2) {
    if (car1.engine_volume < car2.engine_volume) return -1;
    if (car1.engine_volume > car2.engine_volume) return 1;
    return 0;
}

int cmp_cars_by_year(Car car1, Car car2) {
    return car1.year - car2.year;
}

void sort_cars_data_by(CarCollection *collection, int cmp(Car, Car)) {
    switch (SORT_ALGORYTHM) {
        case QUICK_SORT:
            quick_sort(collection->data, 0, collection->count - 1, cmp);
            break;
        case SELECTION_SORT:
            selection_sort(collection->data, collection->count, cmp);
            break;
    }
}

void _swap_cars(Car *car1, Car *car2) {
    Car tmp = *car1;
    *car1 = *car2;
    *car2 = tmp;
}

int _split(Car *cars, int start, int end, int cmp(Car, Car)) {
    int left = start;
    int right = end;
    int pivot_idx = rand() % (end - start + 1) + start;
    Car pivot_val = cars[pivot_idx];

    while (right >= left) {
        while (cmp(pivot_val, cars[left]) > 0) left++;
        while (cmp(cars[right], pivot_val) > 0) right--;

        if (right >= left) {
            _swap_cars(&cars[left], &cars[right]);
            left++;
            right--;
        }
    }

    return left;
}

void quick_sort(Car *cars, int start, int end, int cmp(Car, Car)) {
    if (end <= start) return;

    int pivot_idx = _split(cars, start, end, cmp);

    quick_sort(cars, start, pivot_idx - 1, cmp);
    quick_sort(cars, pivot_idx + 1, end, cmp);
}

void selection_sort(Car *cars, int count, int cmp(Car, Car)) {
    for (int i = 0; i < count - 1; i++) {
        int min_idx = i;

        for (int j = i + 1; j < count; j++) {
            if (cmp(cars[min_idx], cars[j]) > 0) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            _swap_cars(&cars[min_idx], &cars[i]);
        }
    }
}
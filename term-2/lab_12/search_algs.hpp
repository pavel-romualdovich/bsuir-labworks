#pragma once

#include "car.hpp"

enum SearchAlgorithm {
    LIN_WITH_BARRIER_SEARCH = 1,
    BINARY_SEARCH = 2
};

enum SearchField {
    SEARCH_BY_YEAR = 1,
    SEARCH_BY_ENGINE_VOLUME = 2,
    SEARCH_BY_MAX_SPEED = 3
};

struct SearchResult {
    Car data;
    bool is_searched;
};

void search_car_data(CarCollection *);
SearchResult search_car_data_by(CarCollection *, int, double, int *);
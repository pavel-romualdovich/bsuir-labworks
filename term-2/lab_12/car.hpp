#pragma once

enum SortField {
    NOT_SORTED = 0,
    BY_YEAR,
    BY_ENGINE_VOLUME,
    BY_MAX_SPEED
};

struct Car {
    char brand[50];
    char body_number[50];
    int year;
    double engine_volume;
    int max_speed;
};

struct CarCollection {
    Car *data;
    int count;
    SortField sorted_by;
};
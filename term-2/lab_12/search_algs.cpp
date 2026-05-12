#include <iostream>
#include <cstring>
#include <limits>
#include <cmath>
#include <cstdlib>

#include "search_algs.hpp"

#include "input.hpp"


SearchResult lin_with_barrier_search(CarCollection *collection, double search_value, int field) {
    SearchResult result;
    result.is_searched = false;

    Car *temp_data = (Car*)malloc((collection->count + 1) * sizeof(Car));
    memcpy(temp_data, collection->data, collection->count * sizeof(Car));

    switch (field) {
        case SEARCH_BY_YEAR:
            temp_data[collection->count].year = (int)(search_value);
            break;
        case SEARCH_BY_ENGINE_VOLUME:
            temp_data[collection->count].engine_volume = search_value;
            break;
        case SEARCH_BY_MAX_SPEED:
            temp_data[collection->count].max_speed = (int)(search_value);
            break;
    }

    int i = 0;

    switch (field) {
        case SEARCH_BY_YEAR: {
            int int_value = (int)(search_value);
            while (temp_data[i].year != int_value) {
                i++;
            }
            break;
        }
        case SEARCH_BY_ENGINE_VOLUME:
            while (fabs(temp_data[i].engine_volume - search_value) >= 0.0001) {
                i++;
            }
            break;
        case SEARCH_BY_MAX_SPEED: {
            int int_value = (int)(search_value);
            while (temp_data[i].max_speed != int_value) {
                i++;
            }
            break;
        }
    }

    if (i < collection->count) {
        result.is_searched = true;
        result.data = temp_data[i];
    }

    free(temp_data);
    return result;
}

SearchResult binary_search(CarCollection *collection, double search_value, int field) {
    SearchResult search_result;
    search_result.is_searched = false;

    int left = 0;
    int right = collection->count - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        bool equal = false;
        bool less = false;

        switch (field) {
            case SEARCH_BY_YEAR: {
                int int_value = (int)(search_value);
                if (collection->data[mid].year == int_value) {
                    equal = true;
                } else if (collection->data[mid].year < int_value) {
                    less = true;
                }
                break;
            }

            case SEARCH_BY_ENGINE_VOLUME:
                if (fabs(collection->data[mid].engine_volume - search_value) < 0.0001) {
                    equal = true;
                } else if (collection->data[mid].engine_volume < search_value) {
                    less = true;
                }
                break;

            case SEARCH_BY_MAX_SPEED: {
                int int_value = (int)(search_value);
                if (collection->data[mid].max_speed == int_value) {
                    equal = true;
                } else if (collection->data[mid].max_speed < int_value) {
                    less = true;
                }
                break;
            }
        }

        if (equal) {
            search_result.data = collection->data[mid];
            search_result.is_searched = true;
            break;
        } else if (less) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return search_result;
}

SearchResult search_car_data_by(CarCollection *collection, int search_field, double search_value, int *search_algorithm) {
    if (!collection || !collection->data || collection->count == 0) {
        return SearchResult{(Car(), false)};
    }

    if (collection->sorted_by == search_field) {
        *search_algorithm = BINARY_SEARCH;
        return binary_search(collection, search_value, search_field);
    } else {
        *search_algorithm = LIN_WITH_BARRIER_SEARCH;
        return lin_with_barrier_search(collection, search_value, search_field);
    }
}

void search_car_data(CarCollection *collection) {
    using namespace std;

    if (!collection || collection->count == 0) {
        cout << "  записи отсутствуют\n\n";
        return;
    }

    int search_field = parse_search_field();
    double search_value = parse_search_key(search_field);
    int search_algorithm;

    SearchResult search_result = search_car_data_by(
        collection,
        search_field,
        search_value,
        &search_algorithm
    );

    if (search_result.is_searched) {
        output_car_data(search_result.data);

        cout << "  использованный алгоритм: ";
        switch (search_algorithm) {
            case LIN_WITH_BARRIER_SEARCH:
                cout << "линейный поиск с барьером\n\n";
                break;
            case BINARY_SEARCH:
                cout << "бинарный поиск\n\n";
                break;
        }
    } else {
        cout << "\n  запись не найдена\n\n";
    }
}
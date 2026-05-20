#include <iostream>

struct Car {
    char brand[50];
    int body_number;
    int year;
    double engine_volume;
    int max_speed;
};

struct CarSearchResult {
    Car value;
    bool is_find;
};

struct HashTableNode {
    Car value;
    HashTableNode *next;
};

struct HashTable {
    int size;
    HashTableNode **indices;
};

HashTable *init_hash_table(int size) {
    HashTable *hash_table = new HashTable;

    if (size < 1) {
        return nullptr;
    }
    hash_table->size = size;

    hash_table->indices = new HashTableNode*[size];
    for (int i = 0; i < size; i++) {
        hash_table->indices[i] = nullptr;
    }

    return hash_table;
}

void delete_hash_table(HashTable *hash_table) {
    for (int i = 0; i < hash_table->size; i++) {
        HashTableNode *current_node;
        HashTableNode *next_node = hash_table->indices[i];

        while (next_node) {
            current_node = next_node;
            next_node = current_node->next;
            delete current_node;
        }
    }
    delete[] hash_table->indices;
    delete hash_table;
}

int get_index(int key, HashTable *hash_table) {
    return key % hash_table->size;
}

void add_value(Car value, HashTable *hash_table) {
    int index = get_index(value.body_number, hash_table);

    HashTableNode *new_node = new HashTableNode;
    new_node->value = value;

    if (!hash_table->indices[index]) {
        new_node->next = nullptr;
    } else {
        new_node->next = hash_table->indices[index];
    }
    hash_table->indices[index] = new_node;
}

void delete_value(int body_number, HashTable *hash_table) {
    int index = get_index(body_number, hash_table);

    HashTableNode *current_node = hash_table->indices[index];
    HashTableNode *prev_node = nullptr;

    while (current_node != nullptr) {
        if (current_node->value.body_number == body_number) {
            break;
        }
        prev_node = current_node;
        current_node = current_node->next;
    }

    if (!current_node) {
        return;
    }

    if (prev_node) {
        prev_node->next = current_node->next;
    } else {
        hash_table->indices[index] = current_node->next;
    }

    delete current_node;
}

CarSearchResult search_value(int body_number, HashTable *hash_table) {
    int index = get_index(body_number, hash_table);

    CarSearchResult result;
    result.is_find = false;

    HashTableNode *current_node = hash_table->indices[index];

    while (current_node != nullptr) {
        if (current_node->value.body_number == body_number) {
            break;
        }
        current_node = current_node->next;
    }

    if (current_node) {
        result.value = current_node->value;
        result.is_find = true;
    }

    return result;
}

void print_hash_table(HashTable *hash_table) {
    for (int i = 0; i < hash_table->size; i++) {
        std::cout << i << ": ";
        HashTableNode *current_node = hash_table->indices[i];
        if (!current_node) {
            std::cout << "Empty" << std::endl;
        } else {
            while (current_node) {
                std::cout << current_node->value.body_number << ' ';
                current_node = current_node->next;
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    HashTable *hash_table = init_hash_table(13);

    Car car1 = {
        "BMW",
        1210,
        2010,
        10,
        200
    };

    Car car2 = {
        "Audi",
        3567,
        2015,
        15,
        250
    };

    add_value(car1, hash_table);
    add_value(car2, hash_table);

    print_hash_table(hash_table);

    CarSearchResult search_result = search_value(3567, hash_table);
    if (!search_result.is_find) {
        std::cout << "Не найдено" << std::endl;
    } else {
        std::cout << "Найден автомобиль " << search_result.value.brand << std::endl;
    }

    delete_hash_table(hash_table);

    return 0;
}
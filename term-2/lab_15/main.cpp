#include <iostream>

struct Node {
    int value;
    Node *next;
    Node *prev;
};

struct DoublyLinkedList {
    Node *head;
    Node *tail;
    int size;
};

DoublyLinkedList *init_doubly_linked_list() {
    DoublyLinkedList *doubly_linked_list = new DoublyLinkedList;
    if (doubly_linked_list == nullptr) {
        return nullptr;
    }

    doubly_linked_list->head = nullptr;
    doubly_linked_list->tail = nullptr;
    doubly_linked_list->size = 0;

    return doubly_linked_list;
}

void add_value_to_end_of_list(int value, DoublyLinkedList *list) {
    Node *new_node = new Node{value, nullptr, nullptr};

    if (list->head == nullptr) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }

    list->size++;
}

void add_value_to_begin_of_list(int value, DoublyLinkedList *list) {
    Node *new_node = new Node{value, nullptr, nullptr};

    if (list->head == nullptr) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }

    list->size++;
}

void delete_first_value_from_list(DoublyLinkedList *list) {
    if (list->head == nullptr) {
        return;
    }

    Node *node_to_delete = list->head;

    if (list->head == list->tail) {
        list->head = nullptr;
        list->tail = nullptr;
    } else {
        list->head = list->head->next;
        list->head->prev = nullptr;
    }

    delete node_to_delete;
    list->size--;
}

void delete_specific_node(Node *node, DoublyLinkedList *list) {
    if (node == nullptr) return;

    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    delete node;
    list->size--;
}

void delete_list(DoublyLinkedList *list) {
    Node *node;
    Node *next_node = list->head;

    while (next_node != nullptr) {
        node = next_node;
        next_node = node->next;
        delete node;
    }

    delete list;
}

int get_first_value_from_list(DoublyLinkedList *list) {
    if (list->head == nullptr) {
        return -1;
    }
    return list->head->value;
}

int get_size(DoublyLinkedList *list) {
    return list->size;
}

void print_list(DoublyLinkedList *list) {
    Node *current = list->head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
}

int main() {
    using namespace std;

    DoublyLinkedList* list1 = init_doubly_linked_list();
    DoublyLinkedList* list2 = init_doubly_linked_list();

    int size;

    cout << "Введите количество чисел: ";
    cin >> size;

    if (size < 1) {
        delete_list(list1);
        delete_list(list2);
        return 0;
    }

    cout << "Введите " << size << " чисел: ";

    for (int i = 0; i < size; i++) {
        int value;
        cin >> value;
        add_value_to_end_of_list(value, list1);
    }

    while (get_size(list1) != 0) {
        int count = 0;
        int cur_value = get_first_value_from_list(list1);

        Node *current = list1->head;
        while (current != nullptr) {
            if (current->value == cur_value) {
                count++;
            }
            current = current->next;
        }

        if (count >= 2) {
            add_value_to_end_of_list(cur_value, list2);

            current = list1->head;
            while (current != nullptr) {
                Node *next_node = current->next;
                if (current->value == cur_value) {
                    delete_specific_node(current, list1);
                }
                current = next_node;
            }
        } else {
            delete_first_value_from_list(list1);
        }
    }

    cout << "Результат: ";
    print_list(list2);
    cout << endl;

    delete_list(list1);
    delete_list(list2);

    return 0;
}
#include <iostream>
#include <climits>

struct Node {
    int value;
    Node *next;
};

struct Stack {
    int size;
    Node *head;
};

void push(int value, Stack *stack) {
    Node *new_node = new Node;
    new_node->value = value;
    new_node->next = stack->head;
    stack->head = new_node;
    stack->size++;
}

bool is_empty(Stack *stack) {
    return stack->size == 0;
}

int pop(Stack *stack) {
    if (is_empty(stack)) {
        return -1;
    }

    Node *head_node = stack->head;
    int head_value = head_node->value;
    stack->head = head_node->next;
    delete head_node;
    stack->size--;
    return head_value;
}

Stack* init_stack() {
    Stack *stack = new Stack;
    stack->head = nullptr;
    stack->size = 0;
    return stack;
}

void delete_stack(Stack *stack) {
    Node *cur_node = stack->head;
    Node *next_node;

    while (!is_empty(stack)) {
        pop(stack);
    }

    delete stack;
}

void print_stack(Stack *stack) {
    if (is_empty(stack)) {
        return;
    }

    Node *cur_node = stack->head;
    for (int i = 0; i < stack->size; i++) {
        std::cout << cur_node->value << ' ';
        cur_node = cur_node->next;
    }
}

int main() {
    using namespace std;

    int size;
    cout << "Введите количество чисел: ";
    cin >> size;

    if (size <= 0) {
        return 0;
    }

    Stack *stack = init_stack();

    int value;
    cout << "Введите " << size << " чисел: ";
    for (int i = 0; i < size; i++) {
        cin >> value;
        push(value, stack);
    }

    Node *max_node = nullptr;
    Node *prev_max_node = nullptr;
    Node *min_node = nullptr;
    Node *prev_min_node = nullptr;

    int max_value = INT_MIN;
    int min_value = INT_MAX;

    Node *cur_node = stack->head;
    Node *prev_node = nullptr;

    for (int i = 0; i < size; i++) {
        if (cur_node->value > max_value) {
            max_value = cur_node->value;
            max_node = cur_node;
            prev_max_node = prev_node;
        }
        if (cur_node->value < min_value) {
            min_value = cur_node->value;
            min_node = cur_node;
            prev_min_node = prev_node;
        }

        prev_node = cur_node;
        cur_node = cur_node->next;
    }

    if (min_value == max_value) {
        print_stack(stack);
        delete_stack(stack);
        return 0;
    }

    if (max_node->next == min_node) {
        if (prev_max_node) {
            prev_max_node->next = min_node;
        } else {
            stack->head = min_node;
        }

        max_node->next = min_node->next;
        min_node->next = max_node;
    }
    else if (min_node->next == max_node) {
        if (prev_min_node) {
            prev_min_node->next = max_node;
        } else {
            stack->head = max_node;
        }

        min_node->next = max_node->next;
        max_node->next = min_node;
    }
    else {
        if (prev_max_node) {
            prev_max_node->next = min_node;
        } else {
            stack->head = min_node;
        }

        if (prev_min_node) {
            prev_min_node->next = max_node;
        } else {
            stack->head = max_node;
        }

        Node *tmp = max_node->next;
        max_node->next = min_node->next;
        min_node->next = tmp;
    }

    print_stack(stack);
    delete_stack(stack);

    return 0;
}
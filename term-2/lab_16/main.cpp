#include <iostream>

struct Node {
    int value;
    Node *left;
    Node *right;
    int height;
};

struct AVLTree {
    Node *root;
};

AVLTree *init_avl_tree() {
    AVLTree *tree = new AVLTree;
    tree->root = nullptr;
    return tree;
}

Node *init_node(int value) {
    Node *node = new Node;

    node->left = nullptr;
    node->right = nullptr;
    node->value = value;
    node->height = 0;

    return node;
}

void delete_node(Node *node) {
    if (!node) {
        return;
    }
    delete_node(node->left);
    delete_node(node->right);
    delete node;
}

void delete_avl_tree(AVLTree *tree) {
    delete_node(tree->root);
    delete tree;
}

int get_height(Node *node) {
    return node ? node->height : -1;
}

int get_balance(Node *node) {
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

void update_height(Node *node) {
    if (node) {
        int left_height = get_height(node->left);
        int right_height = get_height(node->right);
        int max_height = left_height > right_height ? left_height : right_height;
        node->height = 1 + max_height;
    }
}

Node *rotate_right(Node *current_root) {
    Node *new_root = current_root->left;

    Node *inner_subtree = new_root->right;

    new_root->right = current_root;
    current_root->left = inner_subtree;

    update_height(current_root);
    update_height(new_root);

    return new_root;
}

Node *rotate_left(Node *current_root) {
    Node *new_root = current_root->right;

    Node *inner_subtree = new_root->left;

    new_root->left = current_root;
    current_root->right = inner_subtree;

    update_height(current_root);
    update_height(new_root);

    return new_root;
}

Node *add_value(Node *node, int value) {
    if (!node) {
        return init_node(value);
    }

    if (value < node->value) {
        node->left = add_value(node->left, value);
    } else if (value > node->value) {
        node->right = add_value(node->right, value);
    } else {
        return node;
    }

    update_height(node);

    int balance = get_balance(node);

    // LL
    if (balance > 1 && value < node->left->value) {
        return rotate_right(node);
    }

    // RR
    if (balance < -1 && value > node->right->value) {
        return rotate_left(node);
    }

    // LR
    if (balance > 1 && value > node->left->value) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // RL
    if (balance < -1 && value < node->right->value) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

Node *find_value(AVLTree *tree, int target) {
    Node *current = tree->root;

    while (current != nullptr) {
        if (target == current->value) {
            return current;
        }

        if (target < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return nullptr;
}

Node *get_min_value_node(Node *node) {
    if (!node) return nullptr;

    Node *current = node;
    while (current->left != nullptr) {
        current = current->left;
    }

    return current;
}

Node *remove_value(Node *node, int value) {
    if (!node) {
        return node;
    }

    if (value < node->value) {
        node->left = remove_value(node->left, value);
    } else if (value > node->value) {
        node->right = remove_value(node->right, value);
    } else {
        if (!node->left || !node->right) {
            Node *temp = node->left ? node->left : node->right;

            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node *temp = get_min_value_node(node->right);

            node->value = temp->value;

            node->right = remove_value(node->right, temp->value);
        }
    }

    if (!node) {
        return node;
    }

    update_height(node);

    int balance = get_balance(node);

    // LL
    if (balance > 1 && get_balance(node->left) >= 0) {
        return rotate_right(node);
    }

    // LR
    if (balance > 1 && get_balance(node->left) < 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    // RR
    if (balance < -1 && get_balance(node->right) <= 0) {
        return rotate_left(node);
    }

    // RL
    if (balance < -1 && get_balance(node->right) > 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

// Root -> Left -> Right
void print_pre_order(Node *node) {
    if (!node) return;

    std::cout << node->value << " "; // Root
    print_pre_order(node->left);     // Left
    print_pre_order(node->right);    // Right
}

// Left -> Root -> Right
void print_in_order(Node *node) {
    if (!node) return;

    print_in_order(node->left);      // Left
    std::cout << node->value << " "; // Root
    print_in_order(node->right);     // Right
}

// Left -> Right -> Root
void print_post_order(Node *node) {
    if (!node) return;

    print_post_order(node->left);     // Left
    print_post_order(node->right);    // Right
    std::cout << node->value << " ";  // Root
}

Node *remove_single_left_children(Node *node) {
    if (!node) return nullptr;

    node->left = remove_single_left_children(node->left);
    node->right = remove_single_left_children(node->right);

    if (node->left != nullptr && node->right == nullptr) {
        node = remove_value(node, node->value);
    }

    return node;
}

int main() {
    AVLTree *tree = init_avl_tree();

    int values[] = {50, 30, 70, 20, 40, 10};
    for (int v : values) {
        tree->root = add_value(tree->root, v);
    }

    std::cout << "Pre-order: ";
    print_pre_order(tree->root);
    std::cout << "\nIn-order: ";
    print_in_order(tree->root);
    std::cout << "\nPost-order: ";
    print_post_order(tree->root);
    std::cout << "\n";

    tree->root = remove_single_left_children(tree->root);
    std::cout << "After removing nodes with single left child:\n";
    std::cout << "Pre-order: ";
    print_pre_order(tree->root);
    std::cout << "\nIn-order: ";
    print_in_order(tree->root);
    std::cout << "\nPost-order: ";
    print_post_order(tree->root);
    std::cout << "\n";

    delete_avl_tree(tree);

    return 0;
}
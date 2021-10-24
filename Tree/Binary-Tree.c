// This is an example for Binary Tree
// 2021/10/20

#include <stdio.h>
#include <stdlib.h>

typedef struct binaryTreeNode {
    void* element;
    struct binaryTreeNode* left;
    struct binaryTreeNode* right;
} BinaryTreeNode;

// user should declare their own comapre function
// return 1 if el1 is less than el2
typedef int (*Less_func)(void* el1, void* el2);

typedef struct binaryTree {
    BinaryTreeNode* root;
    Less_func less;
    void (*add)(struct binaryTree* this, void* element);
} BinaryTree;

void binaryTree_add(BinaryTree* this, void* element) {
    BinaryTreeNode* node = malloc(sizeof(BinaryTreeNode));
    node->element = element;
    node->left = NULL;
    node->right = NULL;

    // `this` has root
    if (this->root) {
        BinaryTreeNode* previous = NULL;
        BinaryTreeNode* current = NULL;
        for (current = this->root; current;) {
            // if new node is smaller than current node
            previous = current;
            if (this->less(element, current->element)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        // if new node is smaller than its parent node
        if (previous && this->less(element, previous->element)) {
            previous->left = node;
        } else {
            previous->right = node;
        }
    } else {
        // `this` does not have root
        this->root = node;
    }
}

// build an empty binary tree
BinaryTree* __BinaryTree__(Less_func less) {
    BinaryTree* new = malloc(sizeof(BinaryTree));
    new->root = NULL;
    new->less = less;
    new->add = binaryTree_add;
    return new;
}

// ----------------------------------------

struct person {
    char name[32];
    int tall;
};

int personLessFunc(void* p1, void* p2) {
    return ((struct person*)p1)->tall < ((struct person*)p2)->tall;
}

void inorder(BinaryTreeNode* root) {
    if (root) {
        inorder(root->left);
        struct person* element = (struct person*)(root->element);
        printf("(%s, %d) -> ", element->name, element->tall);
        inorder(root->right);
    }
}

int main() {
    // Prepare data
    struct person list[] = {{"Honoka", 157}, {"Umi", 159},  {"Kotori", 159},
                            {"Eli", 162},    {"Nico", 154}, {"Nozomi", 159},
                            {"Hanayo", 156}, {"Rin", 155},  {"Maki", 161}};
    int list_len = sizeof(list) / sizeof(list[0]);

    // Create binary tree
    BinaryTree* tree = __BinaryTree__(personLessFunc);

    // Put data into the tree
    int i;
    for (i = 0; i < list_len; i++) {
        tree->add(tree, list + i);
    }

    // see the tree
    inorder(tree->root);
    printf("Null\n");

    return 0;
}
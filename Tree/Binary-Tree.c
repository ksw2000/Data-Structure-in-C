// This is an example for Binary Tree
// 2021/10/20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct binaryTreeNode {
    void* element;
    struct binaryTreeNode* left;
    struct binaryTreeNode* right;
} BinaryTreeNode;

// user should declare their own comapre function
// return negative if el1 is less than el2
// return 0 if el1 is equal to el2
// return positive if el1 is greater than el2
typedef int (*Compare_func)(void* el1, void* el2);

typedef struct binaryTree {
    BinaryTreeNode* root;
    Compare_func cmp;
    void (*add)(struct binaryTree* this, void* element);
    void (*delete)(struct binaryTree* this, void* target);
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
            if (this->cmp(element, current->element) < 0) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        // if new node is smaller than its parent node
        if (previous && this->cmp(element, previous->element) < 0) {
            previous->left = node;
        } else {
            previous->right = node;
        }
    } else {
        // `this` does not have root
        this->root = node;
    }
}

void binaryTree_delete(BinaryTree* this, void* target) {
    // find the node and its parent need to be deleted
    // and its parent
    BinaryTreeNode* current = NULL;
    BinaryTreeNode* parent = NULL;
    for (current = this->root;
         current && this->cmp(target, current->element);) {
        parent = current;
        current = this->cmp(target, current->element) < 0 ? current->left
                                                          : current->right;
    }

    if (!current) {
        fprintf(stderr, "binaryTree_delete() target node is not in tree\n");
        exit(EXIT_FAILURE);
    }

    if (current->right) {
        // find successor: the smallest value in right subtree
        BinaryTreeNode* successor;
        BinaryTreeNode* successor_parent = current;
        for (successor = current->right; successor->left;) {
            successor_parent = successor;
            successor = successor->left;
        }

        // replace current node to successor node
        current->element = successor->element;
        free(successor);

        // let the pointer point to the successor be NULL;
        if (successor_parent->left == successor) {
            successor_parent->left = successor->right;
        } else {
            successor_parent->right = successor->right;
        }
        return;
    }

    if (!parent) {
        this->root = current->left;
    } else if (parent->left == current) {
        parent->left = current->left;
    } else if (parent->right == current) {
        parent->right = current->left;
    }

    free(current);
    return;
}

// build an empty binary tree
BinaryTree* __BinaryTree__(Compare_func cmp) {
    BinaryTree* new = malloc(sizeof(BinaryTree));
    new->root = NULL;
    new->cmp = cmp;
    new->add = binaryTree_add;
    new->delete = binaryTree_delete;
    return new;
}

// ----------------------------------------

struct person {
    char name[32];
    int tall;
};

int personCmpFunc(void* p1, void* p2) {
    if (((struct person*)p1)->tall < ((struct person*)p2)->tall)
        return -1;
    if (((struct person*)p1)->tall > ((struct person*)p2)->tall)
        return 1;
    if (!strcmp(((struct person*)p1)->name, ((struct person*)p2)->name))
        return 0;
    return 1;
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
    BinaryTree* tree = __BinaryTree__(personCmpFunc);

    // Put data into the tree
    int i;
    for (i = 0; i < list_len; i++) {
        tree->add(tree, list + i);
    }

    // See the tree
    inorder(tree->root);
    printf("Null\n");

    printf("\n\n");

    // Delete
    for (i = 0; i < list_len; i++) {
        printf("delete %s\n", list[i].name);
        tree->delete (tree, list+i);
        inorder(tree->root);
        printf("Null\n");
    }

    return 0;
}
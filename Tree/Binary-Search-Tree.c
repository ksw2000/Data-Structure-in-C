// This is an example for Binary Search Tree
// 2021/10/20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bstNode {
    void* element;
    struct bstNode* left;
    struct bstNode* right;
} BstNode;

// user should declare their own comapre function
// return negative if el1 is less than el2
// return 0 if el1 is equal to el2
// return positive if el1 is greater than el2
typedef int (*Compare_func)(void* el1, void* el2);

typedef struct binaryTree {
    BstNode* root;
    Compare_func cmp;
    void (*add)(struct binaryTree* this, void* element);
    void (*delete)(struct binaryTree* this, void* target);
} BinaryTree;

void binaryTree_add(BinaryTree* this, void* element) {
    // create new node
    BstNode* node = calloc(1, sizeof(BstNode));
    node->element = element;

    // `parent` is the pointer of the `left` or `right`
    // in the parent node of the new node
    // i.e. the pointer of the pointer that points to `current`
    //
    // for example
    //          parent
    //        /        \
    //      left      right
    //      /
    // new node (NULL)
    //
    // current = node (NULL before added)
    // parent = &left
    // *parent = current

    BstNode** parent = &this->root;
    BstNode* current = this->root;

    while(current){
        // if new node is smaller than current node
        // set `parent` to the pointer of the left of current
        parent = (this->cmp(element, current->element) < 0) ? &current->left
                                                            : &current->right;
        current = *parent;
    }

    *parent = node;
}

void binaryTree_delete(BinaryTree* this, void* target) {
    // find the node should be deleted and
    // the pointer of the pointer points to it

    BstNode** parent = &this->root;
    BstNode* current = this->root;

    while (current && this->cmp(target, current->element)) {
        parent = this->cmp(target, current->element) < 0 ? &current->left
                                                         : &current->right;
        current = *parent;
    }

    // if not found
    if (!current) {
        fprintf(stderr, "binaryTree_delete() target node is not in tree\n");
        exit(EXIT_FAILURE);
    }

    if (!current->right || !current->left) {
        *parent = (current->left) ? current->left : current->right;
        free(current);
    } else {
        // find successor: the smallest value in right subtree
        // successor_parent is the pointer of the pointer that points to
        // `successor`

        BstNode** successor_parent = &current->right;
        BstNode* successor = current->right;
        for (; successor->left; successor = *successor_parent) {
            successor_parent = &successor->left;
        }

        // replace current node to successor node
        current->element = successor->element;
        // connect the successor's parent to the successor's right subtree
        *successor_parent = successor->right;

        free(successor);
    }
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

void inorder(BstNode* root) {
    if (root) {
        inorder(root->left);
        struct person* element = (struct person*)(root->element);
        printf("(%s, %d) -> ", element->name, element->tall);
        inorder(root->right);
    }
}

int main() {
    // Prepare data
    struct person list[] = {
        {"Hanamaru", 152}, {"Rina", 149},   {"Nico", 154},    {"Hanayo", 156},
        {"Kanata", 158},   {"Maki", 161},   {"Chisato", 155}, {"Karin", 167},
        {"Kotori", 159},   {"Honoka", 157}, {"Riko", 160},    {"Eli", 162},
        {"Mari", 163},
    };
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
    printf("Null\n\n");

    // Delete
    for (i = 0; i < list_len; i++) {
        printf("delete %s\n", list[i].name);
        tree->delete (tree, list + i);
        inorder(tree->root);
        printf("Null\n");
    }

    return 0;
}
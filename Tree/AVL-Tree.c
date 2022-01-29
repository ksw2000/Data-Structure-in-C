// This is an example for AVL tree
// Use stack instead of recursive
//
// avl_insert: 2021/10/24
// avl_delete: 2022/01/30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode {
    void* element;
    struct treeNode* left;
    struct treeNode* right;
    int height;
} TreeNode;

typedef struct stack {
    TreeNode*** list;
    unsigned int cap;
    int top;
} Stack;

Stack* stack_create() {
    Stack* new = malloc(sizeof(Stack));
    new->cap = 8;
    new->top = -1;
    new->list = malloc(sizeof(TreeNode**) * new->cap);
}

// the function is used to record the path when traversing
void stack_push(Stack* this, TreeNode** element) {
    this->top++;
    if (this->top == this->cap) {
        this->cap = this->cap << 1;
        TreeNode*** newList = malloc(sizeof(TreeNode**) * this->cap);
        memcpy(newList, this->list, this->top * sizeof(TreeNode**));
    }
    this->list[this->top] = element;
}

TreeNode** stack_pop(Stack* this) {
    return this->list[this->top--];
}

// return 0 if stack is not empty
int stack_empty(Stack* this) {
    return this->top == -1;
}

// make stack be empty
void stack_init(Stack* this) {
    this->top = -1;
}

// implement your own comapre function
// return negative if el1 is less than el2
// return 0 if el1 is equal to el2
// return positive if el1 is greater than el2
typedef int (*Compare_func)(void* el1, void* el2);

typedef struct avlTree {
    TreeNode* root;
    Compare_func cmp;
    void (*insert)(struct avlTree* this, void* element);
    void (*delete)(struct avlTree* this, void* element);
    Stack* stack;
} AVLTree;

void treeNode_updateHeight(TreeNode* this) {
    if (this) {
        int left = this->left ? this->left->height : 0;
        int right = this->right ? this->right->height : 0;
        this->height = left > right ? left + 1 : right + 1;
    }
}

int treeNode_balanceFactor(TreeNode* this) {
    if (this) {
        int left = this->left ? this->left->height : 0;
        int right = this->right ? this->right->height : 0;
        return left - right;
    }
    return 0;
}

void treeNode_rightRotation(TreeNode** this) {
    if (!this)
        return;
    TreeNode* node = *this;
    TreeNode* left = node->left;
    if (left) {
        node->left = left->right;
        left->right = node;
        treeNode_updateHeight(node);
        treeNode_updateHeight(left);
    }
    *this = left;
}

void treeNode_leftRotation(TreeNode** this) {
    if (!this)
        return;
    TreeNode* node = *this;
    TreeNode* right = node->right;
    if (right) {
        node->right = right->left;
        right->left = node;
        treeNode_updateHeight(node);
        treeNode_updateHeight(right);
    }
    *this = right;
}

void treeNode_reBalance(TreeNode** this) {
    if (!this)
        return;
    TreeNode* node = *this;
    int bf = treeNode_balanceFactor(node);

    // left child overweights
    if (bf > 1) {
        if (node->left && node->left->left) {
            // LL Type
            treeNode_rightRotation(this);
        } else {
            // LR Type
            treeNode_leftRotation(&node->left);
            treeNode_rightRotation(this);
        }
    } else if (bf < -1) {
        if (node->right && node->right->right) {
            // RR Type
            treeNode_leftRotation(this);
        } else {
            // RL Type
            treeNode_rightRotation(&node->right);
            treeNode_leftRotation(this);
        }
    }
}

void avlTree_insert(AVLTree* this, void* element) {
    // create new node
    TreeNode* node = malloc(sizeof(TreeNode));
    node->element = element;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    // if this avl tree does not have any nodes.
    if (!this->root) {
        this->root = node;
        return;
    }

    // find the node where we can add new node.
    // when finding, record the path at the same time

    TreeNode* current = NULL;
    stack_init(this->stack);
    stack_push(this->stack, &this->root);
    for (current = this->root; current;) {
        // find path and push node to stack
        if (this->cmp(element, current->element) < 0) {
            stack_push(this->stack, &current->left);
            current = current->left;
        } else {
            stack_push(this->stack, &current->right);
            current = current->right;
        }
    }

    // `super_current` is the pointer of the left or right
    // in the parent node of `current`
    //
    // for example
    //          parent
    //        /        \
    //      left      right
    //      /
    //    node
    //
    // current = node
    // super_current = &left
    // *super_current = current

    TreeNode** super_current = stack_pop(this->stack);

    // insert into node
    *super_current = node;

    // rebalance other nodes
    // super_current is used to just a temporary variable in the while block
    while (!stack_empty(this->stack)) {
        super_current = stack_pop(this->stack);
        treeNode_updateHeight(*super_current);
        treeNode_reBalance(super_current);
    }
}

// reference:
// https://blog.csdn.net/qq_21388535/article/details/105601270
void avlTree_delete(AVLTree* this, void* element) {
    // find the node we want do delete
    // when finding, record the path at the same time

    TreeNode* current = NULL;
    stack_init(this->stack);
    stack_push(this->stack, &this->root);
    for (current = this->root; current;) {
        if (this->cmp(element, current->element) < 0) {
            stack_push(this->stack, &current->left);
            current = current->left;
        } else if (this->cmp(element, current->element) > 0) {
            stack_push(this->stack, &current->right);
            current = current->right;
        } else {
            // found!
            break;
        }
    }

    // if not found
    if (!current) {
        fprintf(stderr, "delete node is not in the tree");
        exit(EXIT_FAILURE);
    }

    // `super_current` is the pointer of the left or right
    // in the parent node of current
    // same usage in function avlTree_insert()
    TreeNode** super_current = stack_pop(this->stack);

    if (!current->right || !current->left) {
        *super_current = (current->right) ? current->right : current->left;
        free(current);
    } else {
        // find successor: the smallest value in right subtree
        // when finding successor, record the path
        stack_push(this->stack, super_current);
        stack_push(this->stack, &current->right);

        TreeNode* successor;
        for (successor = current->right; successor->left;) {
            stack_push(this->stack, &successor->left);
            successor = successor->left;
        }

        TreeNode** super_successor = stack_pop(this->stack);

        // replace current node to successor node
        current->element = successor->element;
        *super_successor = successor->right;

        free(successor);
    }

    // rebalance other nodes
    // super_current is used to just a temporary variable in the while block
    while (!stack_empty(this->stack)) {
        super_current = stack_pop(this->stack);
        treeNode_updateHeight(*super_current);
        treeNode_reBalance(super_current);
    }
    return;
}

// build an empty binary tree
AVLTree* avlTree_create(Compare_func cmp) {
    AVLTree* new = malloc(sizeof(AVLTree));
    new->root = NULL;
    new->cmp = cmp;
    new->insert = avlTree_insert;
    new->delete = avlTree_delete;
    new->stack = stack_create();
    return new;
}

// ----------------------------------------

struct person {
    char name[32];
    int tall;
};

int personCmpFunc(void* el1, void* el2) {
    return (((struct person*)el1)->tall - ((struct person*)el2)->tall);
}

void print_detail(TreeNode* root) {
    if (root) {
        print_detail(root->left);
        struct person* element = (struct person*)(root->element);
        printf("(%s, %d) height: %d\n", element->name, element->tall,
               root->height);
        if (root->left) {
            element = (struct person*)(root->left->element);
            printf("    left: (%s, %d)\n", element->name, element->tall);
        } else {
            printf("    left: NULL\n", element->name, element->tall);
        }
        if (root->right) {
            element = (struct person*)(root->right->element);
            printf("    right: (%s, %d)\n", element->name, element->tall);
        } else {
            printf("    right: NULL\n");
        }
        print_detail(root->right);
    }
}

void print(TreeNode* root) {
    if (root) {
        print(root->left);
        struct person* element = (struct person*)(root->element);
        printf("(%s, %d) -> ", element->name, element->tall);
        print(root->right);
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
    AVLTree* tree = avlTree_create(personCmpFunc);

    // Put data into the tree
    int i;
    for (i = 0; i < list_len; i++) {
        tree->insert(tree, list + i);
    }

    // see the tree
    print_detail(tree->root);
    print(tree->root);

    // Delete
    for (i = 0; i < list_len; i++) {
        printf("delete %s\n", list[i].name);
        tree->delete (tree, list + i);
        print(tree->root);
        printf("Null\n");
    }
    return 0;
}
// This is an example for AVL tree
// 2021/10/24

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode {
    void* element;
    struct treeNode* left;
    struct treeNode* right;
    int height;
} TreeNode;

// implement your own comapre function
// return 1 if el1 is less than el2
typedef int (*Less_func)(void* el1, void* el2);

typedef struct avlTree {
    TreeNode* root;
    Less_func less;
    void (*insert)(struct avlTree* this, void* element);
    // traverse
    TreeNode*** stack;
    unsigned int stack_len;
    unsigned int stack_logLen;
    int stack_top;
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
    TreeNode* node = malloc(sizeof(TreeNode));
    node->element = element;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    // `this` has root
    if (this->root) {
        TreeNode* current = NULL;

        // push root node
        this->stack[++this->stack_top] = &this->root;
        for (current = this->root; current;) {
            // use a stack which is implemented by arrary list for saving path
            this->stack_top++;
            if (this->stack_top == this->stack_len) {
                TreeNode*** newList =
                    malloc(sizeof(TreeNode**) << (this->stack_logLen + 1));
                memcpy(newList, this->stack,
                       this->stack_len * sizeof(TreeNode**));
                this->stack_len = this->stack_len << 1;
                this->stack_logLen = this->stack_logLen + 1;
            }

            // find path and push node to stack
            if (this->less(element, current->element)) {
                this->stack[this->stack_top] = &current->left;
                current = current->left;
            } else {
                this->stack[this->stack_top] = &current->right;
                current = current->right;
            }
        }

        // pop stack to updateHeight() and reBlance()
        // skip the first popped node
        this->stack_top--;

        TreeNode** visit;

        // insert into node
        if (this->stack_top != -1) {
            visit = this->stack[this->stack_top--];
            if (*visit && this->less(element, (*visit)->element)) {
                (*visit)->left = node;
            } else {
                (*visit)->right = node;
            }
            treeNode_updateHeight(*visit);
            treeNode_reBalance(visit);
        }

        // other nodes
        while (this->stack_top != -1) {
            visit = this->stack[this->stack_top--];
            treeNode_updateHeight(*visit);
            treeNode_reBalance(visit);
        }
    } else {
        // `this` does not have root
        this->root = node;
    }
}

// build an empty binary tree
AVLTree* __AVLTree__(Less_func less) {
    AVLTree* new = malloc(sizeof(AVLTree));
    new->root = NULL;
    new->less = less;
    new->insert = avlTree_insert;
    new->stack = malloc(sizeof(TreeNode**) << 3);
    new->stack_len = 8;
    new->stack_logLen = 3;
    new->stack_top = -1;
    return new;
}

// ----------------------------------------

struct person {
    char name[32];
    int tall;
};

int personLessFunc(void* el1, void* el2) {
    return ((struct person*)el1)->tall < ((struct person*)el2)->tall;
}

void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
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
        inorder(root->right);
    }
}

int main() {
    // Prepare data
    struct person list[] = {
        {"Rina", 149},   {"Hanamaru", 152}, {"Nico", 154},   {"Chisato", 155},
        {"Hanayo", 156}, {"Honoka", 157},   {"Kanata", 158}, {"Kotori", 159},
        {"Riko", 160},   {"Maki", 161},     {"Eli", 162},    {"Mari", 163},
        {"Karin", 167}};
    int list_len = sizeof(list) / sizeof(list[0]);

    // Create binary tree
    AVLTree* tree = __AVLTree__(personLessFunc);

    // Put data into the tree
    int i;
    for (i = 0; i < list_len; i++) {
        tree->insert(tree, list + i);
    }

    // see the tree
    inorder(tree->root);

    // check
    printf("stack_len: %d\n", tree->stack_len);
    printf("stack_logLen: %d", tree->stack_logLen);

    return 0;
}
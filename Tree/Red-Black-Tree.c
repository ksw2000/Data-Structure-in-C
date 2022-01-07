// This is an example for Red Black tree
// 2021/11/29
// reference:
// https://josephjsf2.github.io/data/structure/and/algorithm/2020/04/28/red-black-tree-part-1.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { red, black } color_t;

typedef struct treeNode {
    void* element;
    struct treeNode* left;
    struct treeNode* right;
    struct treeNode* parent;
    color_t color;
} TreeNode;

// implement your own comapre function
// return 1 if el1 is less than el2
typedef int (*Less_func)(void* el1, void* el2);

typedef struct rbTree {
    TreeNode* root;
    Less_func less;
    void (*insert)(struct rbTree* this, void* element);
} RBTree;

// ...N    ..L.
// .L.. => ...N
// ...R    ..R.

// N = node
// L = tmpLeft
// R = tmpLeftRight

void treeNode_rightRotation(RBTree* tree, TreeNode* node) {
    TreeNode* tmpLeftRight = (node->left) ? node->left->right : node->left;
    TreeNode* tmpLeft = node->left;
    node->left = tmpLeftRight;
    if (tmpLeftRight) {
        tmpLeftRight->parent = node;
    }

    if (!node->parent) {
        tree->root = node;
    } else if (node->parent->left == node) {
        node->parent->left = tmpLeft;
    } else {
        node->parent->right = tmpLeft;
    }
    tmpLeft->parent = node->parent;
    tmpLeft->right = node;
    node->parent = tmpLeft;
}

// .N..    ..R.
// ..R. => .N..
// .L..    ..L.

// N = node
// L = tmpLeft
// R = tmpLeftRight
void treeNode_leftRotation(RBTree* tree, TreeNode* node) {
    TreeNode* tmpRightLeft = (node->right) ? node->right->left : node->right;
    TreeNode* tmpRight = node->right;
    node->right = tmpRightLeft;
    if (tmpRightLeft) {
        tmpRightLeft->parent = node;
    }

    if (!node->parent) {
        tree->root = tmpRight;
    } else if (node->parent->right == node) {
        node->parent->right = tmpRight;
    } else {
        node->parent->left = tmpRight;
    }

    tmpRight->parent = node->parent;
    tmpRight->left = node;
    node->parent = tmpRight;
}

void rbTree_insert(RBTree* tree, void* element) {
    TreeNode* x = malloc(sizeof(TreeNode));
    x->element = element;
    x->left = NULL;
    x->right = NULL;
    x->parent = NULL;
    x->color = red;

    if (tree->root) {
        TreeNode* current = NULL;
        TreeNode* previous = NULL;
        // find x's parent
        for (current = tree->root; current;) {
            previous = current;
            if (tree->less(element, current->element)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        // insert node `x` at the appropriate position
        if (previous && tree->less(element, previous->element)) {
            previous->left = x;
        } else {
            previous->right = x;
        }
        x->parent = previous;
        
        // check if the tree violate the rule of RBTree

        // case1: uncle is red => re-mark the color of nodes
        //          1. The color of x's uncle and x's parent should be set to
        //          black
        //          2. x->parent->parent->color = red
        // case2: uncle is black and x is L-R
        //          1. left rotation(x->parent)
        //          2. do case3
        //        uncle is black and x is R-L
        //          1. right rotation(x->parent)
        //          2. do case3
        // case3: uncle is black and x is L-L
        //          1. x->parent->parent->color = red
        //          2. x->parent->color = black
        //          3. right rotation(x->parent->parent)
        //        uncle is black and x is R-R
        //          1. x->parent->parent->color = red
        //          2. x->parent->color = black
        //          3. left rotation(x->parent->parent)
        while (x != tree->root && x->parent && x->parent->color == red) {
            TreeNode* parent = x->parent;
            TreeNode* grandParent = (parent) ? x->parent->parent : NULL;
            TreeNode* uncle = NULL;

            if (grandParent && parent == grandParent->left) {
                uncle = grandParent->right;
                // case 1
                if (uncle && uncle->color == red) {
                    uncle->color = black;
                    parent->color = black;
                    grandParent->color = red;
                    // now focus on grandparent node
                    x = grandParent;
                } else {
                    // case 2 L-R
                    if (x == parent->right) {
                        treeNode_leftRotation(tree, x->parent);
                        // continue handle as case3
                        parent = x;
                        x = parent->parent;
                    }
                    // case 3 L-L
                    grandParent->color = red;
                    parent->color = black;
                    treeNode_rightRotation(tree, grandParent);
                }
            } else if (grandParent) {
                uncle = grandParent->left;
                // case 1
                if (uncle && uncle->color == red) {
                    uncle->color = black;
                    parent->color = black;
                    grandParent->color = red;
                    // now focus on grandparent node
                    x = grandParent;
                } else {
                    // case 2 R-L
                    if (x == parent->left) {
                        treeNode_rightRotation(tree, x->parent);
                        // continue handle as case3
                        parent = x;
                        x = parent->parent;
                    }
                    // case 3 R-R
                    grandParent->color = red;
                    parent->color = black;
                    treeNode_leftRotation(tree, grandParent);
                }
            }
        }
    } else {
        tree->root = x;
    }
    tree->root->color = black;
}

// build an empty red black tree
RBTree* __RBTree__(Less_func less) {
    RBTree* new = malloc(sizeof(RBTree));
    new->root = NULL;
    new->less = less;
    new->insert = rbTree_insert;
    return new;
}

// ----------------------------------------

struct number {
    int val;
};

int numberLessFunc(void* el1, void* el2) {
    return ((struct number*)el1)->val < ((struct number*)el2)->val;
}

void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        struct number* el = (struct number*)(root->element);
        printf("(%d, %s)\n", el->val,
               (root->color == red) ? "R" : "B");
        if (root->left) {
            el = (struct number*)(root->left->element);
            printf("    left: (%d)\n", el->val);
        } else {
            printf("    left: NULL\n");
        }
        if (root->right) {
            el = (struct number*)(root->right->element);
            printf("    right: (%d)\n", el->val);
        } else {
            printf("    right: NULL\n");
        }
        inorder(root->right);
    }
}

int main() {
    // Prepare data
    struct number list[] = {{10}, {20}, {30}, {40}, {50}, {60}, {70}, {80}};
    int list_len = sizeof(list) / sizeof(list[0]);

    // Create binary tree
    RBTree* tree = __RBTree__(numberLessFunc);
    // Put data into the tree
    int i;
    for (i = 0; i < list_len; i++) {
        printf("Round %d\n", i);
        tree->insert(tree, list + i);
        inorder(tree->root);
        printf("---------------------\n");
    }

    // See the tree
    inorder(tree->root);

    return 0;
}
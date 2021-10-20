#include <stdio.h>
#include <stdlib.h>

struct t {
    int d;
    struct t* l;
    struct t* r;
};
typedef struct t* tree;

tree makeTree(int* post, int* in, int start, int end, int* index) {
    // Traverse post[] from the last to the first
    // So we create a tree V R L step by step
    if (start > end) {
        return NULL;
    }

    tree node = malloc(sizeof(*node));
    node->d = post[*index];
    node->l = node->r = NULL;
    (*index)--;

    //----- V -----
    if (start == end) {
        return node;
    }

    // find the node in in[]
    int i, thisNode;
    for (i = start; i <= end; i++) {
        if (in[i] == node->d) {
            thisNode = i;
            break;
        }
    }

    //----- R -----
    node->r = makeTree(post, in, thisNode + 1, end, index);
    //----- L -----
    node->l = makeTree(post, in, start, thisNode - 1, index);
    return node;
}

tree makeTreeInit(int* post, int* in, int len) {
    int index = len - 1;
    return makeTree(post, in, 0, len - 1, &index);
}

void preorder(char* answer, tree root) {
    if (root) {
        sprintf(answer, "%s%d ", answer, root->d);
        preorder(answer, root->l);
        preorder(answer, root->r);
    }
}

int main() {
    // Phase1: Read file
    FILE* f = fopen("input1.txt", "r");
    if (!f) {
        fprintf(stderr, "Cannot open input1.txt");
        exit(1);
    }
    char c;
    int num_nodes = 0;
    for (c = getc(f); c != '\n'; c = getc(f)) {
        if (c == ' ') {
            num_nodes++;
        }
    }
    num_nodes++;
    fclose(f);

    int* post = malloc(sizeof(int) * num_nodes);
    int* in = malloc(sizeof(int) * num_nodes);

    f = fopen("input1.txt", "r");
    int i;
    for (i = 0; i < num_nodes; i++) {
        fscanf(f, "%d", &post[i]);
    }
    for (i = 0; i < num_nodes; i++) {
        fscanf(f, "%d", &in[i]);
    }
    printf("num_nodes:%d\n", num_nodes);
    printf("post:\t");
    for (i = 0; i < num_nodes; i++) {
        printf("%d ", post[i]);
    }
    printf("\n");
    printf("in:\t");
    for (i = 0; i < num_nodes; i++) {
        printf("%d ", in[i]);
    }
    printf("\n");
    fclose(f);

    // Phase2: Create Tree
    // Reference:
    // https://www.geeksforgeeks.org/construct-a-binary-tree-from-postorder-and-inorder/?fbclid=IwAR3QwVQL62smCzHcN0by1_t-Tu4i-gyU9_VzvYNKTUpdLwzg4Dk9qRsl65A
    tree root = makeTreeInit(post, in, num_nodes);
    char* answer = calloc(1024, sizeof(char));
    preorder(answer, root);
    printf("%s\n", answer);

    // Phase3: Write to file
    f = fopen("output1.txt", "w");
    fprintf(f, "%s", answer);
    fclose(f);

    system("pause");
    return 0;
}

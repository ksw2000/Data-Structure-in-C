// This is an example of create a simple max heap
// The maximum heap size is 200
// Reference "Fundamentals of data structures in C 2nd edition" page. 226-229

#include<stdio.h>
#include<stdlib.h>
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct{
    int key;
}element;

int n = 0;  // n is the number of elements in heap
element heap[MAX_ELEMENTS];

// insert item into a max heap of current size *n
void push(element item, int* n){
    if(HEAP_FULL(*n)){
        fprintf(stderr, "The heap is full.\n");
        exit(EXIT_FAILURE);
    }
    int i = ++(*n);
    // if the key of parent node is smaller than the key of item
    // and the current node is not root
    // make current node become parent node
    while((i!=1) && (item.key > heap[i/2].key)){
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = item;
}

// delete element with the highest key from the heap in parent
element pop(int* n){
    element ret;
    if(HEAP_EMPTY(*n)){
        fprintf(stderr, "The heap is empty.\n");
        exit(EXIT_FAILURE);
    }
    // save value of the element with the highest key
    ret = heap[1];
    // use the last element in heap to adjust heap
    element temp = heap[(*n)--];
    int larger_child = 2;
    while (larger_child <= *n) {
        // find the larger child
        // if right child is greater than left child
        if (larger_child < *n && heap[larger_child].key < heap[larger_child + 1].key){
            larger_child++;
        }
        // if the current node is greater than the larger child
        // we have adjusted!
        if (temp.key >= heap[larger_child].key) break;
        // larger_child / 2 == the parent node
        heap[larger_child/2] = heap[larger_child];
        larger_child = larger_child * 2;
    }
    heap[larger_child/2] = temp;
    return ret;
}

int main(){
    int array[] = {1, 7, 5, 6, 3, 9, 8, 10, 4, 2};
    int len = sizeof(array)/sizeof(int);
    int i = 0;
    for(i=0; i<len; i++){
        element item = (element){
            .key = array[i]
        };
        push(item, &n);
    }

    // pop
    element node;
    for(i=0; i<len; i++){
        node = pop(&n);
        printf("%d, ", node.key);
    }
    printf("\n");

    // ------------ OUTPUT ------------
    // 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,
    return 0;
}


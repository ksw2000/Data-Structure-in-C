#include<stdio.h>
#include<stdlib.h>
struct t{
    int d;
    struct t* l;
    struct t* r;
};
typedef struct t* tree;

tree* bubbleSort(tree* array, int len){
    int i,j;
    for(i=0; i<len; i++){
        for(j=0; j<len-i-1; j++){
            if(array[j]->d < array[j+1]->d){
                tree tmp = array[j];
                array[j]=array[j+1];
                array[j+1]=tmp;
            }
        }
    }
    return array;
}

int sum=0;
void inorder(tree root, int rank){
    if(root){
        inorder(root->l, rank+1);
        if(root->l==NULL && root->r==NULL){
            sum+=root->d*rank;
        }
        inorder(root->r, rank+1);
    }
}

int main(){
//Phase1: Read file
    FILE* f=fopen("input3.txt","r");
    if(!f){
        fprintf(stderr, "Cannot open input3.txt\n");
        exit(1);
    }
    char c;
    int num_nodes=0;
    for(c=getc(f); c!='\n'; c=getc(f)){
        if(c==' '){
            num_nodes++;
        }
    }
    num_nodes++;
    fclose(f);

    int i,tmp;
    tree* array=malloc(num_nodes * sizeof(tree));

    f=fopen("input3.txt","r");
    for(i=0; i<num_nodes; i++){
        fscanf(f,"%d",&tmp);
        tree new=malloc(sizeof(*new));
        new->d = tmp;
        new->l = NULL;
        new->r = NULL;
        array[i]=new;
    }
    fclose(f);

//Phase2: Create tree (Keyword: Huffman tree)
    int len;
    for(len=num_nodes; len>1; len--){
        bubbleSort(array, len);
        tree new=malloc(sizeof(struct t));
        new->d = (array[len-1]->d) + (array[len-2]->d);
        new->l = array[len-1];
        new->r = array[len-2];
        array[len-2] = new;
    }

//Phase3: Calculate
    tree root = array[0];
    inorder(root,1);
    printf("sum:%d\n",sum);

    system("pause");
    return 0;
}

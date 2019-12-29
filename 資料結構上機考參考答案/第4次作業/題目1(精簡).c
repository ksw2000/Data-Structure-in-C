#include<stdio.h>
#include<stdlib.h>
struct q{
    int data;
    struct q* next;
};
typedef struct q* queue;

int deq(queue* q){
    queue tmp;
    int ret;
    ret=(*q)->data;
    tmp=*q;
    *q=(*q)->next;
    free(tmp);
    return ret;
}

void enq(queue* q, int data){
    queue current, previous, new=malloc(sizeof(*new));
    new->data=data;
    new->next=NULL;
    if(*q){
        for(current=*q; current; current=current->next){
            previous=current;
        }
        previous->next=new;
    }else{
        *q=new;
    }
}

int main(){
//Phase1: Read file
    FILE *f=fopen("input1.txt","r");
    if(!f){
        fprintf(stderr, "Cannot open input1.txt\n");
        exit(1);
    }
    char c, num_node=1;
    for(c=getc(f); c!='\n'; c=getc(f)){
        if(c==' '){
            num_node++;
        }
    }
    fclose(f);

    int i,j;
    int** adj_matrix;
    adj_matrix = calloc(num_node, sizeof(int*));
    for(i=0; i<num_node; i++){
        adj_matrix[i] = calloc(num_node, sizeof(int));
    }

    int tmp;
    f=fopen("input1.txt","r");
    for(i=0; i<num_node; i++){
        for(j=0; j<num_node; j++){
            fscanf(f,"%d",&tmp);
            if(tmp!=0){
                adj_matrix[i][j]=tmp;
                adj_matrix[j][i]=tmp;
            }
        }
    }
    fclose(f);

//Phase2: BFS
    int* visited = calloc(num_node, sizeof(int));
    int sum=0, vertex;
    queue traversal=NULL;
    for(j=0; j<num_node; j++){
        if(!visited[j]){
            traversal=NULL;
            enq(&traversal, j);
            visited[j]=1;
            printf("%d->",j);
            while(traversal){
                vertex=deq(&traversal);
                for(i=0; i<num_node; i++){
                    if(adj_matrix[vertex][i]!=0 && visited[i]!=1){
                        printf("%d->",i);
                        visited[i]=1;
                        enq(&traversal, i);
                    }
                }
            }
            printf("NULL\n");
            sum++;
        }
    }

    printf("\nsum:%d\n",sum);

//Phase3: Write file
    f=fopen("output1.txt","w");
    fprintf(f, "%d", sum);
    fclose(f);

    system("pause");
    return 0;
}

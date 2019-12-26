#include<stdio.h>
#include<stdlib.h>
#define INF 9999

struct q{
    int data;
    struct q* next;
};
typedef struct q* queue;

void enq(queue* q, int data){
    queue cur,pre,new;
    new=malloc(sizeof(*new));
    new->data=data;
    new->next=NULL;
    if(*q){
        for(cur=*q; cur; cur=cur->next){
            pre=cur;
        }
        pre->next=new;
    }else{
        *q=new;
    }
}

int deq(queue* q){
    int ret;
    queue tmp;
    tmp=*q;
    ret=(*q)->data;
    *q=(*q)->next;
    free(tmp);
    return ret;
}

struct s{
    int i,j;
    struct s* next;
};
typedef struct s* stack;

void push(stack* s, int i, int j){
    stack new;
    new=malloc(sizeof(*new));
    new->i=i;
    new->j=j;
    new->next=*s;
    *s=new;
}

stack pop(stack* s){
    stack tmp;
    tmp=*s;
    *s=(*s)->next;
    free(tmp);
    return *s;
}

int main(){
//Phase1: Read file
    FILE* f=fopen("input3.txt","r");
    if(!f){
        fprintf(stderr, "Cannot open input3.txt\n");
        exit(1);
    }
    char c;
    int num_node=1;
    for(c=getc(f); c!='\n'; c=getc(f)){
        if(c==' '){
            num_node++;
        }
    }
    fclose(f);

    int i,j,tmp;
    int** adj_matrix=calloc(num_node, sizeof(int*));
    for(i=0; i<num_node; i++){
        adj_matrix[i]=calloc(num_node, sizeof(int));
    }
    f=fopen("input3.txt","r");
    for(i=0; i<num_node; i++){
        for(j=0; j<num_node; j++){
            fscanf(f,"%d",&tmp);
            if(tmp!=0){
                adj_matrix[i][j]=tmp;
            }
        }
    }
    fclose(f);

    for(i=0; i<num_node; i++){
        for(j=0; j<num_node; j++){
            printf("%3d ",adj_matrix[i][j]);
        }
        printf("\n");
    }

//Phase2: Ford-Fulkerson (simplified)
    //Reference: https://www.youtube.com/watch?v=GiN3jRdgxU4
    int sum_flow=0;
    int* visited=malloc(num_node*sizeof(int));
    int vertex;
    queue traversal=NULL;
    stack cur, full_path=NULL, node_pair=NULL;
    for(;;){
        //Reset
        for(i=0; i<num_node; i++){
            visited[i]=0;
        }
        full_path=node_pair=NULL;
        traversal=NULL;

        //Use BFS find edge from 0 to num_node-1
        enq(&traversal,0);
        visited[0]=1;
        printf("Find path:\n");
        while(traversal){
            vertex=deq(&traversal);
            for(i=0; i<num_node; i++){
                if(adj_matrix[vertex][i]>0 && visited[i]==0){
                    enq(&traversal, i);
                    visited[i]=1;
                    printf("%d->%d\n",vertex,i);
                    push(&node_pair,vertex,i);
                }
            }
        }

        //Find equivalence class from num_node-1 to 0
        //In order to find one path from 0 to num_node-1
        printf("\nEquivalent:\n");
        int min_rn=INF;
        vertex=num_node-1;
        for(cur=node_pair; cur; cur=cur->next){
            if(cur->j == vertex){
                push(&full_path,cur->i,cur->j);
                vertex = cur->i;
                printf("%d->%d residual_num:%d\n",cur->i,cur->j,adj_matrix[cur->i][cur->j]);
                if(adj_matrix[cur->i][cur->j] < min_rn){
                    min_rn = adj_matrix[cur->i][cur->j];
                }
            }
        }

        //Update residual_num
        for(cur=full_path; cur; cur=cur->next){
            adj_matrix[cur->i][cur->j]-=min_rn;
        }

        if(full_path == NULL){
            break;
        }else{
            sum_flow+=min_rn;
        }

        //Clear stack
        for(cur=node_pair; cur; cur=pop(&cur));
        for(cur=full_path; cur; cur=pop(&cur));
        printf("------------------------\n");
    }

    printf("ans:%d\n",sum_flow);

//Phase3: Write file
    f=fopen("output3.txt","w");
    fprintf(f,"%d", sum_flow);
    fclose(f);

    system("pause");
    return 0;
}

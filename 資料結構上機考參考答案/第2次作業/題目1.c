#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct list{
    char* number;
    struct list* next;
};
typedef struct list* card;

void append(card* c, char* str_num){
    card new, current, previous;
    new = malloc(sizeof(*new));
    new->number = malloc(sizeof(char)*3);
    strcpy(new -> number,str_num);
    new -> next = NULL;
    printf("append %s\n",str_num);

    if(*c){
        for(current=*c; current; current=current->next){
            previous = current;
        }
        previous -> next = new;
    }else{
        *c = new;
    }
}

void printList(card* c, char* answer){
    card current;
    for(current=*c; current; current=current->next){
        printf("%s ", current->number);
        strcat(answer,current->number);
        strcat(answer," ");
    }
}

typedef struct l* list;
int main(){
//Phase1: Read file and append cards into liked-list
    FILE *f=fopen("input1.txt","r");
    if(!f){
        fprintf(stderr, "Cannot open input1.txt\n");
        exit(1);
    }
    int i, j, num_card;
    char suit, number[3];
    card list_h, list_s, list_d, list_c;
    list_h = list_s = list_d = list_c = NULL;

    fscanf(f,"%d\n",&num_card);
    char buffer[6];
    while(fgets(buffer,sizeof(buffer),f)){
        sscanf(buffer,"%c %s\n",&suit,number);
        printf("suit:%c number:%s ",suit,number);

        switch (suit) {
            case 'H':
                append(&list_h, number);
                break;
            case 'S':
                append(&list_s, number);
                break;
            case 'D':
                append(&list_d, number);
                break;
            case 'C':
                append(&list_c, number);
                break;
        }
    }
    fclose(f);

//Phase2 Get linked-list and transfer into string
    char answer[64]="";
    printf("H ");           strcat(answer,"H ");
    printList(&list_h, answer);
    printf("\nS ");         strcat(answer,"\nS ");
    printList(&list_s, answer);
    printf("\nD ");         strcat(answer,"\nD ");
    printList(&list_d, answer);
    printf("\nC ");         strcat(answer,"\nC ");
    printList(&list_c, answer);
    printf("\n");

//Phase3 Write to file
    f=fopen("output1.txt","w");
    fprintf(f, "%s", answer);
    fclose(f);

    system("pause");
    return 0;
}

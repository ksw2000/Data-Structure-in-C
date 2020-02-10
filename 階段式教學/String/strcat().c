#include<stdio.h>
#include<string.h>

int main(){
    char destination[16]="hello ";
    char source[]="world";

    strcat(destination, source);
    printf(destination);
    //hello world

    printf("\n");

    //也可以由一個字元指標去接收
    char destination2[16]="是在";
    char* result;
    result=strcat(destination2,destination);
    printf(result);
    //是在hello world

    return 0;
}

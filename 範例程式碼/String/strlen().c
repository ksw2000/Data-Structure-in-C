#include<stdio.h>
#include<string.h>

int main(){
    printf("%d ",strlen("abc"));
    //3

    printf("%d ",strlen("中文"));
    //6 (UTF8 if you use VScode or Atom)
    //4 (Big5 if you use Dev-C++)

    return 0;
}

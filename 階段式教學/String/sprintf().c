#include<stdio.h>

int main(){
    char str1[]="hello ";
    char str2[]="world";
    char result[16];
    sprintf(result, "%s%s", str1, str2);
    printf("%s\n",result);

    char str_ori[]="Taiwan NO.1";
    char str_copy[16];
    sprintf(str_copy, "%s", str_ori);
    printf("%s\n",str_copy);

    int a=10;
    char b='A';
    float c=9.487;
    char str[16];
    sprintf(str,"%d %c %.3f", a, b, c);
    printf("%s",str);

    return 0;
}

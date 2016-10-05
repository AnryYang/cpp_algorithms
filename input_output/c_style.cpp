/*************************************************************************
    > File Name: c_style.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Wed Oct  5 21:34:23 2016
 ************************************************************************/

#include<stdio.h>

int main(){

    // get short chars, delimiter is space
    char str1[20], str2[20];
    scanf("%s%s", str1, str2);
    printf("%s,%s\n", str1, str2);

    // get long chars, delimiter is line break
    char buf[100];
    gets(buf);
    printf("%s\n", buf);

    // get one char
    char c = getchar();
    printf("%c\n", c);

    // input until incurring EOF (CTRL-Z in Windows, CTRL-D in *nix)
    int a=0,b=0;
    while(scanf("%d %d", &a, &b)!=EOF && a!=0 && b!=0) printf("%d\n", a+b);

    return 0;
}


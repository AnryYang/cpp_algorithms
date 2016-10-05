/*************************************************************************
    > File Name: quick_power.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Wed 05 Oct 2016 05:27:42 PM
 ************************************************************************/

#include<iostream>
using namespace std;

// complexity is O(logb)

int RecursivePow(int a, int b){
    if(b==0) return 1;
    else if(b & 1) return a*RecursivePow(a, b-1);
    else{
        int c = RecursivePow(a, b/2); 
        return c*c;
    }
}

int IterativePow(int a, int b){
    int result = 1;
    int base = a;

    while(b){
        if(b & 1) result *= base;
        base*=base;
        b = b>>1;
    }

    return result;
}

int main(){
    int a,b;
    a = 3;
    b = 4;
    cout<<a<<" to the "<<b<<"-th power equals:"<<RecursivePow(a, b)<<endl;
    cout<<a<<" to the "<<b<<"-th power equals:"<<IterativePow(a, b)<<endl;

    return 0;
}
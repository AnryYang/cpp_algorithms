/*************************************************************************
    > File Name: cpp_style.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Wed Oct  5 21:34:33 2016
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

int main(){

    string strBuf;
    getline(cin, strBuf);
    cout<<strBuf<<endl;

    char chBuf[255];
    cin.getline(chBuf, 255);
    // cin.getline(buf, 255, '\n');
    cout<<chBuf<<endl;
    
    int a=0,b=0;
    // CTRL-Z or CTRL-D to interrupt inputting
    while(cin>>a>>b && a!=0 && b!=0) cout<<a+b<<endl;

    return 0;
}


/*************************************************************************
    > File Name: insertion_sort.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Thu 29 Sep 2016 10:00:02 AM SGT
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

void swap(int i, int j, vector<int> &vecData){
    int iTemp = vecData[i];
    vecData[i] = vecData[j];
    vecData[j] = iTemp;
}

void InsertionSort(vector<int> &vecData, int i){
    if(i==vecData.size()-1) return;

    InsertionSort(vecData, i+1);

    while(i+1<vecData.size()){
        if(vecData[i]<vecData[i+1]){
            swap(i, i+1, vecData);
            i++;
        }
        else return;
    }
}

int main(){
    vector<int> vecTestData;
    
    vecTestData.push_back(4);
    vecTestData.push_back(5);
    vecTestData.push_back(3);
    vecTestData.push_back(2);
    vecTestData.push_back(6);
    vecTestData.push_back(9);
    vecTestData.push_back(8);
    vecTestData.push_back(1);
    vecTestData.push_back(12);
    vecTestData.push_back(7);

    InsertionSort(vecTestData, 0);

    for(int i=0;i<vecTestData.size();i++) cout<<vecTestData[i]<<endl;
}

/*************************************************************************
    > File Name: heap_sort.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Thu 29 Sep 2016 11:44:14 AM SGT
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

void swap(vector<int> &vecData, int i, int j){
    int iTemp = vecData[i];
    vecData[i] = vecData[j];
    vecData[j] = iTemp;
}

void sink(vector<int> &vecData, int i, int iBorder){
    while(2*i+1<=iBorder){
        int k = 2*i+1;
        if(2*i+2<=iBorder) k = vecData[2*i+1]>vecData[2*i+2]?2*i+1:2*i+2;

        if(vecData[k]>vecData[i]){
            swap(vecData, i, k);
            i = k;
        }
        else return;
    }
}

void HeapSort(vector<int> &vecData){
    for(int i=(vecData.size()-2)/2;i>=0;i--) sink(vecData, i, vecData.size()-1);

    for(int i=vecData.size()-1;i>0;i--){
        swap(vecData, 0, i);
        sink(vecData, 0, i-1);
    }
}

int main(){

    vector<int> vecTestData;

    vecTestData.push_back(7);
    vecTestData.push_back(9);
    vecTestData.push_back(8);
    vecTestData.push_back(4);
    vecTestData.push_back(2);
    vecTestData.push_back(3);
    vecTestData.push_back(5);
    vecTestData.push_back(11);
    vecTestData.push_back(10);
    vecTestData.push_back(6);
    vecTestData.push_back(7);
    vecTestData.push_back(1);
    vecTestData.push_back(13);
    vecTestData.push_back(9);

    HeapSort(vecTestData);

    for(int i=0;i<vecTestData.size();i++) cout<<vecTestData[i]<<endl;

    return 0;
}

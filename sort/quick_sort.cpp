/*************************************************************************
    > File Name: quick_sort.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Thu 29 Sep 2016 11:44:22 AM SGT
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

int Partition(vector<int> &vecData, int low, int high){
     int iPivot = low;
     int iPivotData = vecData[iPivot];

     while(low<high){
         while(low<high){
             if(iPivotData > vecData[high]){
                 vecData[low] = vecData[high];
                 break;
             }
             else high--;
         }

         while(low<high){
             if(iPivotData < vecData[low]){
                 vecData[high] = vecData[low];
                 break;
             }
             else low++;
         }
     }

     vecData[low] = iPivotData;
     iPivot = low;

     return iPivot;
}

void QuickSort(vector<int> &vecData, int low, int high){
     if(low<high){ 
         int iPivot = Partition(vecData, low, high);

         QuickSort(vecData, low, iPivot-1);
         QuickSort(vecData, iPivot+1, high);
     }
}

int main(){
    
    vector<int> vecTestData;

    vecTestData.push_back(9);
    vecTestData.push_back(2);
    vecTestData.push_back(10);
    vecTestData.push_back(5);
    vecTestData.push_back(8);
    vecTestData.push_back(7);
    vecTestData.push_back(1);
    vecTestData.push_back(6);
    vecTestData.push_back(11);
    vecTestData.push_back(3);
    vecTestData.push_back(4);
    vecTestData.push_back(9);

    QuickSort(vecTestData, 0, vecTestData.size()-1);

    for(int i=0;i<vecTestData.size()-1;i++) cout<<vecTestData[i]<<endl;

    return 0;
}

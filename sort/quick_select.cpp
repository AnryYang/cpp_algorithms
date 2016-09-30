/*************************************************************************
    > File Name: quick_select.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Thu 29 Sep 2016 05:57:09 PM
 ************************************************************************/

/*
 * how to find the kth of an unsorted array in O(n) time?
*/

#include<iostream>
#include<vector>
using namespace std;

int Partition(vector<int> &vecData, int low, int high){
    int iPivot = low;
    int iPivotValue = vecData[iPivot];

    while(low<high){
        while(low<high){
            if(iPivotValue>vecData[high]){
                vecData[low] = vecData[high];
                break;
            }
            else high--;
        }

        while(low<high){
            if(iPivotValue<vecData[low]){
                vecData[high] = vecData[low];
                break;
            }
            else low++;
        }
    }

    iPivot = low;
    vecData[iPivot] = iPivotValue;

    return iPivot;
}

int QuickSelect(vector<int> &vecData, int k, int low, int high){
    
    int iPivot = Partition(vecData, low, high);

    if(iPivot<k-1) return QuickSelect(vecData, k, iPivot+1, high);
    else if(iPivot>k-1) return QuickSelect(vecData, k, low, iPivot-1);
    else return vecData[iPivot];   
}

int main(){

    vector<int> vecTestData;

    vecTestData.push_back(9);
    vecTestData.push_back(8);
    vecTestData.push_back(7);
    vecTestData.push_back(5);
    vecTestData.push_back(6);
    vecTestData.push_back(1);
    vecTestData.push_back(2);
    vecTestData.push_back(3);
    vecTestData.push_back(4);
    vecTestData.push_back(10);

    for(int k=1;k<=vecTestData.size();k++){
        int k_element = QuickSelect(vecTestData, k, 0, vecTestData.size()-1);
        cout<<"NO."<<k<<" element is:"<<k_element<<endl;
    }

    return 0;
}


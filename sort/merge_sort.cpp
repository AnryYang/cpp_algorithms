/*************************************************************************
    > File Name: merge_sort.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Thu 29 Sep 2016 11:44:34 AM SGT
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

void MergeSort(vector<int> &vecData, int low, int high){
    
    if(low>=high) return;

    int mid = (low + high)/2;
    
    MergeSort(vecData, low, mid);
    MergeSort(vecData, mid+1, high);

    vector<int> vecTemp;
    int i=low;
    int j=mid+1;

    while(i<=mid || j<=high){
        if(i<=mid && j<=high){
            if(vecData[i]<=vecData[j]){
                vecTemp.push_back(vecData[i]);
                i++;
            }
            else{
                vecTemp.push_back(vecData[j]);
                j++;
            }
        }
        else if(i<=mid && j>high){
            vecTemp.push_back(vecData[i]);
            i++;
        }
        else if(i>mid && j<=high){
            vecTemp.push_back(vecData[j]);
            j++;
        }
    }

    for(int k=0;k<vecTemp.size();k++) vecData[low+k] = vecTemp[k];
}

int main(){
    vector<int> vecTestData;

    vecTestData.push_back(9);
    vecTestData.push_back(10);
    vecTestData.push_back(13);
    vecTestData.push_back(8);
    vecTestData.push_back(7);
    vecTestData.push_back(2);
    vecTestData.push_back(6);
    vecTestData.push_back(3);
    vecTestData.push_back(4);
    vecTestData.push_back(12);
    vecTestData.push_back(5);
    vecTestData.push_back(9);

    MergeSort(vecTestData, 0, vecTestData.size()-1);

    for(int i=0;i<vecTestData.size();i++) cout<<vecTestData[i]<<endl;

    return 0;
}


/*************************************************************************
    > File Name: heap.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Tue 27 Sep 2016 10:01:51 PM SGT
 ************************************************************************/

#include<iostream>
#include "heap.h"

template <class T>
Heap<T>::Heap(std::vector<T>& vecSrcData): vecData(vecSrcData){
    for(int i=(vecData.size()-2)/2;i>=0;i--) sink(i);
}

template <class T>
void Heap<T>::sink(int i){
    while(2*i+1 <= size()-1){
        int j = 2*i+1;
        if(2*i+2<=size()-1) j = (vecData[2*i+1] > vecData[2*i+2])?2*i+1:2*i+2;
        
        if(vecData[i]<vecData[j]){
            swap(i, j);
            i = j;
        }
        else return;
    }
}

template <class T>
void Heap<T>::swim(int i){
    while(i>0){
        if(vecData[(i-1)/2]<vecData[i]){
            swap((i-1)/2 ,i);
            i=(i-1)/2;
        }
        else return;
    }
}

template <class T>
void Heap<T>::swap(int i, int j){
    T temp;
    temp = vecData[i];
    vecData[i] = vecData[j];
    vecData[j] = temp;
}

template <class T>
void Heap<T>::remove(int i){
    swap(i, vecData.size()-1);
    vecData.pop_back();
    sink(i);
}

template <class T>
void Heap<T>::insert(T const& element){
    vecData.push_back(element);
    swim(size()-1);
}

template <class T>
T Heap<T>::peek() const {
    if(vecData.size()>0) return vecData[0];
    else return 0;
}

template <class T>
void Heap<T>::pop(){
    swap(0, vecData.size()-1);
    vecData.pop_back();
    sink(0);
}

template <class T>
int Heap<T>::size(){
    return vecData.size();
}

template <class T>
bool Heap<T>::empty(){
    return vecData.size()==0;
}

int main(){

    std::vector<int> vecData;
    vecData.push_back(8);
    vecData.push_back(4);
    vecData.push_back(7);
    vecData.push_back(5);
    vecData.push_back(6);
    vecData.push_back(9);
    vecData.push_back(3);
    vecData.push_back(2);

    Heap<int> heap(vecData);

    std::cout<<"peek: "<<heap.peek()<<std::endl;

    heap.insert(10);

    std::cout<<"peek: "<<heap.peek()<<std::endl;

    heap.pop();

    std::cout<<"peek: "<<heap.peek()<<std::endl;

    heap.insert(11);
    heap.insert(12);

    while(!heap.empty()){
        std::cout<<"peek: "<<heap.peek()<<std::endl;
        heap.pop();
    } 

    return 0;
}



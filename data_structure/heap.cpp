/*************************************************************************
    > File Name: heap.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Tue 27 Sep 2016 10:01:51 PM SGT
 ************************************************************************/

#include<iostream>
#include "heap.h"

template <class T>

Heap<T>::Heap(vector<T> const& vecSrcData){
    vecData = vecSrcData;

    for(int i=0;i<vecData.size();i++) sink(i);
}

void Heap<T>::sink(int i){
    while(){
    
    }
}

void Heap<T>::swim(int i){
    while(){
    
    }
}

void Heap<T>::remove(int i){

}

void Heap<T>::insert(T const& element){
    
}

T Heap<T>::peek() const {
    if(vecData.size()>0) return vecData[0];
    else return 0;
}

void Heap<T>::pop(){

}

int Heap<T>::size(){
    return vecData.size();
}

bool Heap<T>::empty(){
    return vecData.size()==0;
}



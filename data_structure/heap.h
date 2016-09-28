/*************************************************************************
    > File Name: heap.h
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Tue 27 Sep 2016 06:10:29 AM PDT
 ************************************************************************/

#include<iostream>
#include<vector>

template <class T>

class Heap{
    public:
        //constructor and destructor
        Heap(){}
        Heap(std::vector<T>& vecSrcData);
        ~Heap(){}

        //operator
        void remove(int);
        void insert(T const&);
        T peek() const;
        void pop();
        int size();
        bool empty();

    protected:
        //innner operator
        void sink(int);
        void swim(int);
        void swap(int, int);

    private:
        std::vector<T> vecData;
};


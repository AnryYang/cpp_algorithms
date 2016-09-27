/*************************************************************************
    > File Name: heap.h
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Tue 27 Sep 2016 06:10:29 AM PDT
 ************************************************************************/

#include<iostream>
#include<vector>

#ifndef
#define std::vector vector


template <class T>

class Heap(){
    public:
        //constructor and destructor
        Heap(vector<T> const&);
        ~Heap();

        //operator
        void remove();
        void insert(T const&);
        T peek() const;
        void pop();
        int size();
        bool empty();

    protected:
        //innner operator
        void sink(int i);
        void swim(int i);

    private:
        vector<T> vecData;
};


#undef vector
#endif

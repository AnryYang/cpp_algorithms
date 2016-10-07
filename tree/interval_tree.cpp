/*************************************************************************
    > File Name: interval_tree.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Fri 07 Oct 2016 05:32:41 PM
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

struct IntervalNode{
    int low;
    int high;
    int mid(){return (low+high)/2}
    
    int iMax;   //maximum value in this interval [low, high]
    int iMin;   //minimum value in this interval [low, high]
    int iSum;   //sum of the values in this interval [low, high]
    int iMedian;    //median of the values in this interval [low, high]
    int iAvg;   //average value of the values in this interval [low, high]
};

class IntervalTree{
    IntervalTree(){}
    ~IntervalTree(){}

    protected: 
        void Build(){}
    public:
        void Insert(){}
        void Query(){}

    private:
        vector<IntervalNode> vecTree;
}


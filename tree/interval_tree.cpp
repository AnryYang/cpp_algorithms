/*************************************************************************
    > File Name: interval_tree.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Fri 07 Oct 2016 05:32:41 PM
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

#define INF 1<<30

struct IntervalNode{
    int low;    //lower bound 
    int high;   //upper bound
    int mid(){return (low+high)/2;}
    
    int iMax;   //maximum value in this interval [low, high]
    int iMin;   //minimum value in this interval [low, high]
    int iSum;   //sum of the values in this interval [low, high]
    // int iMedian;    //median of the values in this interval [low, high]
    int iAvg;   //average value of the values in this interval [low, high]
};

// why 4 times size? because we use array, it's a full binary tree'
// see http://stackoverflow.com/questions/28470692/how-is-the-memory-of-the-array-of-segment-tree-2-2-ceillogn-1

class IntervalTree{
    public:
        IntervalTree(){}
        template<size_t ARR_SIZE>
        IntervalTree(int (&arr)[ARR_SIZE]){
            int size = ARR_SIZE;
            vecTree.resize(4*size); 
            Build(0, 0, size-1);
            for(int i=0;i<size;i++){
                Insert(0, i, arr[i]);
            }
        }
        ~IntervalTree(){}

    protected: 
        void Build(int root, int left, int right){
            // create a new node
            vecTree[root].low = left;
            vecTree[root].high = right;

            vecTree[root].iMin = INF;
            vecTree[root].iMax = -INF;
            vecTree[root].iSum = 0;
            vecTree[root].iAvg = 0;

            if(left!=right){    //interval of node root can still be divided
                Build(2*root+1, left, (left+right)/2);
                Build(2*root+2, (left+right)/2+1, right);
            }
            else return;
        }
        void Insert(int root, int index, int value){ //insert a new node
            if(vecTree[root].low==vecTree[root].high){
                vecTree[root].iMax = vecTree[root].iMin = vecTree[root].iSum = vecTree[root].iAvg = value;
                return;
            }

            vecTree[root].iMin = min(vecTree[root].iMin, value);
            vecTree[root].iMax = max(vecTree[root].iMax, value);
            vecTree[root].iSum += value;
            vecTree[root].iAvg = vecTree[root].iSum/(vecTree[root].high-vecTree[root].low+1);

            if(index<=vecTree[root].mid()) Insert(2*root+1, index, value); // index is on the left
            else Insert(2*root+2, index, value);    // index is on the right
        }
        void Query(int root, int left, int right){
            if(vecTree[root].low==left && vecTree[root].high==right){
                iQueryMax = max(vecTree[root].iMax, iQueryMax);
                iQueryMin = min(vecTree[root].iMin, iQueryMin);
                iQuerySum += vecTree[root].iSum;
                return;
            }

            if(right<=vecTree[root].mid()) Query(2*root+1, left, right); //interval is on the left 
            else if(left>vecTree[root].mid()) Query(2*root+2, left, right); //interval is on the right
            else{
                Query(2*root+1, left, vecTree[root].mid());
                Query(2*root+2, vecTree[root].mid()+1, right);
            }
        }
    public:
        int QueryMax(int left, int right){
            iQueryMax = -INF;
            Query(0, left, right);
            return iQueryMax;
        }
        int QueryMin(int left, int right){
            iQueryMin = INF;
            Query(0, left, right);
            return iQueryMin;
        }
        int QuerySum(int left, int right){
            iQuerySum = 0;
            Query(0, left, right);
            return iQuerySum;
        }
        float QueryAvg(int left, int right){
            return QuerySum(left, right)/float(right-left+1);
        }

        // void Print(){
        //     for(int i=0;i<vecTree.size();i++){
        //         cout<<"Node "<<i<<" interval["<<vecTree[i].low<<","<<vecTree[i].high<<"]:"\
        //             <<vecTree[i].iMax<<","<<vecTree[i].iMin<<","<<vecTree[i].iSum<<","\
        //             <<vecTree[i].iAvg<<endl;

        //     }
        // }
    private:
        vector<IntervalNode> vecTree;
        int iQueryMax;
        int iQueryMin;
        int iQuerySum;
};

int main(){

    int arr[10];

    arr[0] = 3;
    arr[1] = 2;
    arr[2] = 1;
    arr[3] = 1;    
    arr[4] = 2;
    arr[5] = 3;
    arr[6] = 3;
    arr[7] = 2;
    arr[8] = 1;
    arr[9] = 2;

    IntervalTree tree(arr);

    // tree.Print();

    int left=2, right=8;
    cout<<"Maximum value between "<<left<<" and "<<right<<" is "<<tree.QueryMax(left,right)<<endl;
    cout<<"Minimum value between "<<left<<" and "<<right<<" is "<<tree.QueryMin(left,right)<<endl;
    cout<<"Sum value between "<<left<<" and "<<right<<" is "<<tree.QuerySum(left,right)<<endl;
    cout<<"Avarage value between "<<left<<" and "<<right<<" is "<<tree.QueryAvg(left,right)<<endl;

    return 0;
}


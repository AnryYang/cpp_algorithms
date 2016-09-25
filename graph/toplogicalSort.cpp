/*************************************************************************
    > File Name: toplogicalSort.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Sun 25 Sep 2016 05:25:35 PM
 ************************************************************************/

#include<iostream>
#include<queue>
using namespace std;

#define MAX_NODE_COUNT 100
int Graph[MAX_NODE_COUNT][MAX_NODE_COUNT];
int Visited[MAX_NODE_COUNT]={0};
int InDegree[MAX_NODE_COUNT]={0};

void TopSortByInDegree(int n){

    cout<<"Toplogical Sort by using in-degree"<<endl;
    
    deque<int> q;

    //find the 0-in-degree vertex
    for(int i=0;i<n;i++){
        if(InDegree[i]==0) q.push_back(i);
    }

    while(!q.empty()){
        int u = q.front();
        cout<<"visit vertex "<<u<<endl;
        q.pop_front();
        
        // reduce the in-degree of all vertices 
        // that the 0-in-degree vertex point to by 1
        for(int v=0;v<n;v++){
            if(Graph[u][v]>0){
                InDegree[v]--;
                if(InDegree[v]==0) q.push_back(v); // find next 0-in-degree vertices
            }
        }
    }
}

void TopSortByPostOrder(int n){
    
}

int main(){
    int n,m;

    cout<<"Please input vertex count and edge count (seperate them by one space):"<<endl;
    cin>>n>>m;

    cout<<"Please input edges, each edge one line, in the form 'start-vertex end-vertex':"<<endl;
    for(int i=0;i<m;i++){
        int start, end;
        cin>>start>>end;
        Graph[start][end] = 1;
        InDegree[end]++;
    }

    TopSortByInDegree(n);

    return 0;
}

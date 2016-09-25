/*************************************************************************
    > File Name: graphTraversal.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Sun 25 Sep 2016 01:11:52 PM
 ************************************************************************/

#include<iostream>
#include<stack>
#include<queue>
using namespace std;

#define MAX_NODE_COUNT 100
int Graph[MAX_NODE_COUNT][MAX_NODE_COUNT];
int Visited[MAX_NODE_COUNT];

void DepthFirstTraversal(int n){
    
    cout<<"Depth First Traversal:"<<endl;

    for(int i=0;i<n;i++) Visited[i]=0;

    stack<int> s;
    s.push(0);
    Visited[0] = 1;
    cout<<"visit vertex "<<0<<endl;

    while(!s.empty()){
        int u = s.top();

        bool bHasNeighbor = false;
        for(int v=0;v<n;v++){
            if(Graph[u][v]>0 && Visited[v]==0){
                bHasNeighbor = true;
                s.push(v);
                Visited[v] = 1;
                cout<<"visit vertex "<<v<<endl;
            }
        }

        if(bHasNeighbor == false) s.pop();
    }

}

void BreadthFirstTraversal(int n){

    cout<<"Breadth First Traversal:"<<endl;

    for(int i=0;i<n;i++) Visited[i]=0;

    deque<int> q;
    q.push_back(0);
    Visited[0] = 1;
    cout<<"visit vertex "<<0<<endl;

    while(!q.empty()){
        int u = q.front();
        q.pop_front();
        
        for(int v=0;v<n;v++){
            if(Graph[u][v]>0 && Visited[v]==0){
                q.push_back(v);
                Visited[v] = 1;
                cout<<"visit vertex "<<v<<endl;
            }
        }
    }
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
    }

    BreadthFirstTraversal(n);

    DepthFirstTraversal(n);
    
    return 0;
}

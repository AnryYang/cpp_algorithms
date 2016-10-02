/*************************************************************************
    > File Name: findMinimumVertex.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Sun 02 Oct 2016 03:41:46 PM
 ************************************************************************/

#include<iostream>
using namespace std;

#define MAX_NODE_COUNT 100
int Graph[MAX_NODE_COUNT][MAX_NODE_COUNT]={0};
int MinWeight[MAX_NODE_COUNT];
bool Visited[MAX_NODE_COUNT];

/*
 * suppose every vertex is assigned a weight, e.g., W(v) is the weight of vertex v
 * define min(u) yo be the minimum W(v) over all vertices v that are reachable from u
 * how to compute min(u) for all vertices u of graph G
 * 
 * Idea: use DFS(u) to serach all paths from u, DFS always returns the minimum W(v) on this path to its start vertex
*/

void FindMinVertexByDFS(int n, int u){
    
    Visited[u] = true;

    for(int v=0;v<n;v++){
        if(Graph[u][v]>0){
            if(Visited[v]!=true){
                FindMinVertexByDFS(n, v);
            }

            if(MinWeight[u]>MinWeight[v]) {
                MinWeight[u] = MinWeight[v];
            }
        }
    }
}

int main(){

    cout<<"Please input vertex count and edge count:"<<endl;

    int n,m;
    cin>>n>>m;

    cout<<"Please input the weight of each vertex:"<<endl;
    for(int i=0;i<n;i++){
        cout<<"vertex "<<i<<" :"<<endl;
        cin>>MinWeight[i];
    }

    cout<<"Please input edges: start-vertex end-vertex"<<endl;

    for(int i=0;i<m;i++){
        int s,t;
        cin>>s>>t;
        Graph[s][t] = 1;
    }

    FindMinVertexByDFS(n, 0);

    for(int i=0;i<n;i++) cout<<"Minimum weight of the vertices reachable from "<<i<<" is:"<<MinWeight[i]<<endl;

    return 0;
}

/*************************************************************************
    > File Name: hamiltonianPath.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Tue 04 Oct 2016 11:48:47 AM
 ************************************************************************/

#include<iostream>
#include<queue>
using namespace std;

#define MAX_NODE_COUNT 100
int Graph[MAX_NODE_COUNT][MAX_NODE_COUNT];
int Visited[MAX_NODE_COUNT]={0};
int InDegree[MAX_NODE_COUNT]={0};

/*
 * what's Hamiltonian path?
 * In a DAG, if there is a path which visits each vertex exactly once
 * this is a Hamiltonian Path 
 *
 * how to find a Hamiltonian path?
 * An idea is using toplological sort but we need to add some modifications
 * the basic idea is always find a vertex has no incoming edges
 * firstly, start to find a vertex in graoh which has no in-degree, 
 * if there is not exactly only one such vertex, there is no Halmitonian Path 
 * after picking the only one vertex u which has no in-degree, 
 * then remove it from graph and update the in-degree of all the vertices that v points to 
 * then do the above steps again until no such vertex 
*/

bool CheckHalmitonianPath(int n){  

    int iCount = 0; //the current count of vertices whose in-degree is zero
    deque<int> q;

    //find the 0-in-degree vertex
    for(int i=0;i<n;i++){
        if(InDegree[i]==0){
            if(iCount!=0) return false; //more than one vertices have no incoming edges
            iCount++;
            q.push_back(i);
        }
    }

    if(iCount==0) return false; // no vertex has zero indegree

    while(!q.empty()){
        int u = q.front();
        cout<<"visit vertex "<<u<<endl;
        q.pop_front();
        iCount--;
        
        // reduce the in-degree of all vertices 
        // that the 0-in-degree vertex point to by 1
        bool bHasNeighbor = false;
        for(int v=0;v<n;v++){
            if(Graph[u][v]>0){
                bHasNeighbor = true;
                InDegree[v]--;
                if(InDegree[v]==0){
                    if(iCount!=0) return false; //more than one vertices have no incoming edges
                    iCount++;
                    q.push_back(v); // find next 0-in-degree vertices
                }
            }
        }

        if(bHasNeighbor==true && iCount==0) return false; // after remove current 0-in-degree vertx, no neighbors have 0 degree 
    }  

    return true;  
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

    cout<<"Is Halmitonian Path? "<<CheckHalmitonianPath(n)<<endl;

    return 0;
}





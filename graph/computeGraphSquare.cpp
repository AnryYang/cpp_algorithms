/*************************************************************************
    > File Name: computeGraphSquare.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Fri 30 Sep 2016 03:02:23 PM SGT
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;


#define MAX_NODE_COUNT 100

/*
 * how to compute the square of a graph G=(V, E)
 * denote the square of graph G as G^2
 * G^2 has the same vertices as G, but any edge(u ,v) in G^2 is the path in G whose length is 2
 * see the question 1 in http://www.bowdoin.edu/~ltoma/teaching/cs231/fall09/Homeworks/old/H9-sol.pdf
 * for adjacency list representation, it takes O(|V||E|) time
 * for adjacency matrix representation, it takes O(|V|^3) to compute Matrix G * Matrix G
*/

void ComputeSquaredAdjListGraph(vector<vector<int>> &graph){

    cout<<"compute the adjacency list graph's suqare"<<endl;

    vector<vector<int>> SquaredGraph;
    for(int i=0;i<graph.size();i++){
        vector<int> vecAdjNodes;
        SquaredGraph.push_back(vecAdjNodes);
    }

    for(int u=0;u<graph.size();u++){
        for(int i=0;i<graph[u].size();i++){
            int v = graph[u][i];
            for(int j=0;j<graph[v].size();j++){
                int w = graph[v][j];
                bool bExists=false;
                //if w already exits, don't add it again
                for(int k=0;k<SquaredGraph[u].size();k++){
                   if(w == SquaredGraph[u][k]) bExists=true;
                }
                //otherwise, add it
                if(u!=w && bExists==false) SquaredGraph[u].push_back(w);
            }
        }
    }

    for(int u=0;u<SquaredGraph.size();u++){
        for(int i=0;i<SquaredGraph[u].size();i++){
            int v = SquaredGraph[u][i];
            if(u<v) cout<<"edge ("<<u<<","<<v<<")"<<endl;
        }
    }
}

void ComputeSquaredAdjMatrixGraph(int Graph[MAX_NODE_COUNT][MAX_NODE_COUNT], int n){
    
     cout<<"compute the adjacency matrix graph's square"<<endl;

     int SquaredGraph[MAX_NODE_COUNT][MAX_NODE_COUNT];

     for(int i=0;i<n;i++){
         for(int j=0;j<n;j++){
             SquaredGraph[i][j] = 0;
             for(int k=0;k<n;k++){
                 SquaredGraph[i][j]+=(Graph[i][k]*Graph[k][j]);
             }
         }
     }

     for(int u=0;u<n;u++){
         for(int v=0;v<u;v++){
             if(SquaredGraph[u][v]>0&&u!=v) cout<<"edge ("<<u<<","<<v<<")"<<endl;
         }
     }
}

int main(){

    int AdjMatrixGraph[MAX_NODE_COUNT][MAX_NODE_COUNT];
    vector<vector<int>> AdjListGraph;

    cout<<"Please input vertex count and edge count:"<<endl;
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        vector<int> vecAdjNodes;
        AdjListGraph.push_back(vecAdjNodes);
    }

    cout<<"Please input edge: start-vertex end-vertex"<<endl;
    for(int i=0;i<m;i++){
        int s,t;
        cin>>s>>t;
        AdjMatrixGraph[s][t] = 1;
        AdjMatrixGraph[t][s] = 1;
        AdjListGraph[s].push_back(t);
        AdjListGraph[t].push_back(s);
    }

    ComputeSquaredAdjListGraph(AdjListGraph);

    ComputeSquaredAdjMatrixGraph(AdjMatrixGraph, n);

    return 0;
}

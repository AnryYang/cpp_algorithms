/*************************************************************************
    > File Name: minimumSpanningTree.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Sun Sep 25 22:22:28 2016
 ************************************************************************/

#include<iostream>
#include<queue>

using namespace std;

#define MAX_NODE_COUNT 100
int Graph[MAX_NODE_COUNT][MAX_NODE_COUNT];
int MST[MAX_NODE_COUNT][MAX_NODE_COUNT]; //minimum spanning tree nodes

struct EdgeToMST{
    int vertex;
    int weight;

    EdgeToMST(int vertex_, int weight_):vertex(vertex_), weight(weight_){}

    bool operator <(const EdgeToMST &edge) const{
        return weight>edge.weight;
    }
};

void Prim(int n){
    int iMSTSize=0;
    int iMSTWeight=0;
    int MSTVertices[MAX_NODE_COUNT];

    priority_queue<EdgeToMST> qMinEdge;
    
    EdgeToMST eMinEdge(0,0);

    qMinEdge.push(eMinEdge);

    while(!qMinEdge.empty() && iMSTSize<n){
        //pick the minimum edge between V\MST and  MST
        do{
            eMinEdge = qMinEdge.top();
            qMinEdge.pop();
        }while(MSTVertices[eMinEdge.vertex]==1 && !qMinEdge.empty());
        
        // add new vertex into MST and update edges between V\MST and MST
        if(MSTVertices[eMinEdge.vertex]!=1){
            MSTVertices[eMinEdge.vertex]=1; //mark that the vertex is in MST
            iMSTSize++; //total vertex count of MST increases
            iMSTWeight += eMinEdge.weight; //total weight of MST increases

            // once the vertex is added into MST, update priority-queue by adding new edges between V\MST and MST
            for(int v=0;v<n;v++){
                if(Graph[eMinEdge.vertex][v]>0 && MSTVertices[v]!=1){ //only for neighbor and non-added vertex
                    MST[eMinEdge.vertex][v] = eMinEdge.weight;
                    MST[v][eMinEdge.vertex] = eMinEdge.weight;
                    qMinEdge.push(EdgeToMST(v, Graph[eMinEdge.vertex][v]));
                }
            }
        }
    }

    cout<<"total MST weight:"<<iMSTWeight<<endl;
}

int main(){
   int n, m;
   
   cout<<"Please input vertex count and edge count"<<endl;
   cin>>n>>m;
   cout<<"Please input edges (in the form 'start-vertex end-vertex')"<<endl;
   for(int i=0;i<m;i++){
       int start,end,weight;
       cin>>start>>end>>weight;
       Graph[start][end] = weight;
       Graph[end][start] = weight;
   }

   Prim(n);
}

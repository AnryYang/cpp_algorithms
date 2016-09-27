/*************************************************************************
    > File Name: shortestPath.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Mon 26 Sep 2016 10:07:22 PM PDT
 ************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define MAX_NODE_COUNT 100
#define INFINITE 1<<30
int Graph[MAX_NODE_COUNT][MAX_NODE_COUNT];

struct NodeToSource{
    int vertex;
    int distance;

    NodeToSource(int v_, int d_):vertex(v_), distance(d_){}

    bool operator <(const NodeToSource & node) const{
        return distance > node.distance;
    }
};

void Dijkstra(int n){

    vector<NodeToSource> V;   //use vector to store all unselected nodes


    //inialize the distances of all other nodes to source node
    for(int i=1;i<n;i++){
        if(Graph[0][i]>0){
            V.push_back(NodeToSource(i, Graph[0][i]));
        }
        else{ //if no edge between source node and i, set the distance between them as Infinite
            V.push_back(NodeToSource(i, INFINITE));
        }
    }

    make_heap(V.begin(), V.end()); // make V as a min-heap

    // extract nearest node and update distances between source and unselected nodes
    while(!V.empty()){
        // get the root of min-heap and remove it
        NodeToSource stNearestNode = V.front();
        int u = stNearestNode.vertex;
        
        pop_heap(V.begin(),V.end());
        V.pop_back();
        
        cout<<"shortest distance to "<<u<<" is "<<stNearestNode.distance<<endl;

        for(int v=0;v<n;v++){ 
            if(Graph[u][v] > 0){ //for every neighbors of u
                for(int i=0;i<V.size();i++){
                    if(V[i].vertex == v){ //find the position of the neighbor of in min-heap
                       //update distance and rebuild min-heap
                       V[i].distance = min(V[i].distance, stNearestNode.distance + Graph[u][v]);
                       make_heap(V.begin(), V.end());
                    }
                }
            }
        }
    }
}

int main(){
   int n, m;
   
   cout<<"Please input vertex count and edge count"<<endl;
   cin>>n>>m;
   cout<<"Please input edges (in the form 'start-vertex end-vertex distance')"<<endl;
   for(int i=0;i<m;i++){
       int start,end,distance;
       cin>>start>>end>>distance;
       Graph[start][end] = distance;
   }
   
   Dijkstra(n);
}

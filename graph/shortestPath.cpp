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
#define INFINITE 1<<29
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

    cout<<"Dijkstra:"<<endl;

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

// dynamic programming
void BellmanFord(int n){

    cout<<"Bellman Ford:"<<endl;

    int Distance[MAX_NODE_COUNT]={0};

    for(int i=0;i<n;i++){
        if(Graph[0][i]>0) Distance[i] = Graph[0][i];
        else Distance[i] = INFINITE; 
    }
    
    for(int k=1;k<n;k++){
        for(int u=1;u<n;u++){
            for(int v=1;v<n;v++){
                if(Graph[v][u]>0){
                    Distance[u] = min(Distance[u], Distance[v]+Graph[v][u]);
                }
            }
        }
    }

    for(int i=1;i<n;i++){
        cout<<"shortest distance to "<<i<<" is "<<Distance[i]<<endl;
    }
}

//all-pair shortest path
void FloydWarshall(int n){

    cout<<"Floyd Warshall:"<<endl;

    int Distance[MAX_NODE_COUNT][MAX_NODE_COUNT];

    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(Graph[i][j]>0) Distance[i][j] = Graph[i][j];
            else Distance[i][j]=INFINITE;

            if(Graph[j][i]>0) Distance[j][i] = Graph[j][i];
            else Distance[j][i]=INFINITE;
        }
    }

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                Distance[i][j] = min(Distance[i][j], Distance[i][k]+Distance[k][j]);
            }
        }
    }

    // print out all distances
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){

            if(Distance[i][j]>=INFINITE) Distance[i][j]=-1;
            if(Distance[j][i]>=INFINITE) Distance[j][i]=-1;

            cout<<"shortest distance from "<<i<<" to "<<j<<" is "<<Distance[i][j]<<endl;
            cout<<"shortest distance from "<<j<<" to "<<i<<" is "<<Distance[j][i]<<endl;
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

   BellmanFord(n);

   FloydWarshall(n);
}

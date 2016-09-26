/*************************************************************************
    > File Name: minimumSpanningTree.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Sun Sep 25 22:22:28 2016
 ************************************************************************/

#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

#define MAX_NODE_COUNT 100
int Graph[MAX_NODE_COUNT][MAX_NODE_COUNT];
int MST[MAX_NODE_COUNT][MAX_NODE_COUNT]; //minimum spanning tree nodes
int Parent[MAX_NODE_COUNT];

struct EdgeToMST{
    int vertex;
    int weight;

    EdgeToMST(int vertex_, int weight_):vertex(vertex_), weight(weight_){}

    bool operator <(const EdgeToMST &edge) const{
        return weight>edge.weight;
    }
};

struct Edge{
    int start;
    int end;
    int weight;

    Edge(int s, int e, int w):start(s), end(e), weight(w){}

    bool operator <(const Edge &edge) const{
        return weight<edge.weight;
    }
};

void Prim(int n){

    cout<<"Prim:"<<endl;

    int iMSTSize=0;
    int iMSTWeight=0;
    int MSTVertices[MAX_NODE_COUNT]={0};

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

int Find(int vertex){
    while(Parent[vertex]!=vertex){
        vertex = Parent[vertex];
    }

    int root = Parent[vertex];
    return root;
}

void Union(int v_1, int v_2){

    int root_v_1 = Find(v_1);
    int root_v_2 = Find(v_2);

    int new_root = min(root_v_1, root_v_2);

    Parent[root_v_1] = new_root;
    Parent[root_v_2] = new_root;
}


// use union-find
void Kruskal(int n, int m){
    
    cout<<"Kruskal:"<<endl;

    int iMSTWeight = 0;
    vector<Edge> edges;

    vector<Edge> MSTEdges;

    // get edges from Graph
    for(int i=0;i<n;i++){
        Parent[i] = i;
        for(int j=0;j<i;j++){
            if(Graph[i][j]>0||Graph[j][i]>0){
                edges.push_back(Edge(i, j, Graph[i][j]));    
            }
        }
    }

    // sort all edges in asecending order
    sort(edges.begin(), edges.end());

    // choose edge in ascending order, for each edge,
    // check if there exits a cycle when adding this edge into to MST 
    // if so, abandon this edge and choose other one
    // if not, add it into MST and merge them into one set
    for(int i=0;i<m;i++){
        if(Find(edges[i].start)!=Find(edges[i].end)){
            iMSTWeight += edges[i].weight;
            MSTEdges.push_back(edges[i]);
            Union(edges[i].start, edges[i].end);
        }

        if(MSTEdges.size()==n-1) break; // already selected n-1 edges, it's a MST
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
   Kruskal(n, m);
}

/*************************************************************************
    > File Name: cycleDetection.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Sun 25 Sep 2016 10:28:52 PM PDT
 ************************************************************************/

#include<iostream>
#include<stack>
#include<queue>
using namespace std;

#define MAX_NODE_COUNT 100
int UndirectedGraph[MAX_NODE_COUNT][MAX_NODE_COUNT];
int DirectedGraph[MAX_NODE_COUNT][MAX_NODE_COUNT];
bool Visited[MAX_NODE_COUNT];
bool Checked[MAX_NODE_COUNT];
int Parent[MAX_NODE_COUNT];

// use dfs to detect cycle on undirected graph
// in order to detect cycle, we need to find an edge of current vertex,
// whose another vertex is visited before
bool DetectCycleByDFS_UndirectedGraph(int n){

    bool VisitedEdge[MAX_NODE_COUNT][MAX_NODE_COUNT];
    for(int i=0;i<n;i++) Visited[i]=false;

    stack<int> s;
    s.push(0);
    Visited[0] = true;

    while(!s.empty()){
        int u = s.top();

        bool bHasNeighbor = false;
        for(int v=0;v<n;v++){
            
            // if the neighbor is visited before, and the edge is not visited, there must be a cycle
            if(UndirectedGraph[u][v]>0 && Visited[v]==true && VisitedEdge[u][v]!=true) return true; 
            
            if(UndirectedGraph[u][v]>0 && Visited[v]==false){
                bHasNeighbor = true;
                s.push(v);
                Visited[v] = true;
                VisitedEdge[u][v]=true;
                VisitedEdge[v][u]=true;
            }
        }

        if(bHasNeighbor == false) s.pop();
    }

    return false;
}

// find the head of the set that vertex is in
int Find(int vertex){
    while(Parent[vertex]!=vertex){
        vertex = Parent[vertex];
    }

    int root = Parent[vertex];

    return root;
}

// merge two sets of two vertices into one set sharing common head
void Union(int v_1, int v_2){
    int v_1_root = Find(v_1);
    int v_2_root = Find(v_2);

    int new_root = min(v_1_root, v_2_root);

    Parent[v_1_root] = new_root;
    Parent[v_2_root] = new_root;
}

// use union-find to detect cycles on undirected graph
bool DetectCycleByUnionFind_UnDirectedGraph(int n){

    for(int i=0;i<n;i++) Parent[i]=i; // initialization, every vertex as a set

    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(UndirectedGraph[i][j]>0){  // for each edge
                // if one edge's two vertices share common root
                // i, j must be in the same set and they are connected in the set
                // but another edge between i and j, so there must be a cycle
                if(Find(i) == Find(j)){
                    return true;
                }
                Union(i, j);
            }
        }
    }

    return false; 
}

bool CheckBackEdgeByDFS(int n, int u){

    Visited[u] = true;
    Checked[u] = true; //mark that u is in stack, namely, u is already on the path

    //check every children of u
    for(int v=0;v<n;v++){
        if(DirectedGraph[u][v]>0){ //for edge u->v
            if(Visited[v]==false){ //if v is not visited before
                if(CheckBackEdgeByDFS(n, v)==true){ //start to check all the paths from v (u is on the path already)
                    return true;
                } 
            }
            else{ 
                // if v is visited, and v is on the path
                // that means there is a path v->u (u is the most new one added on the path)
                // so edge u->v is a back edge
                if(Checked[v]==true) return true;
            }
        }
    }

    Checked[u] = false; // we have checked the all paths from u, so start to check other paths from u's previous node

    return false;
}

// use dfs to detect cycles on directed graph
bool DetectCycleByDFS_DirectedGraph(int n){

    for(int i=0;i<n;i++){ 
        Visited[i]=false;
        Checked[i]=false;
    }

    //start to DFS from each vertex, namely, start to check back-edges on all paths from u
    //once found an back edge, there is a cycle
    for(int u=0;u<n;u++){
        if(CheckBackEdgeByDFS(n, u)==true) return true;
    }

    return false;
}

int main(){
    int n,m;

    cout<<"Please input vertex count and edge count (seperate them by one space):"<<endl;
    cin>>n>>m;

    cout<<"Please input edges, each edge one line, in the form 'start-vertex end-vertex':"<<endl;
    for(int i=0;i<m;i++){
        int start, end;
        cin>>start>>end;

        DirectedGraph[start][end] = 1;
        
        UndirectedGraph[start][end] = 1;
        UndirectedGraph[end][start] = 1;
    }
    
    cout<<"DFS detect cycles on undirected graph:"<<DetectCycleByDFS_UndirectedGraph(n)<<endl;

    cout<<"Union-Find detect cycles on undirected graph:"<<DetectCycleByUnionFind_UnDirectedGraph(n)<<endl;

    cout<<"DFS detect cycles on directed graph:"<<DetectCycleByDFS_DirectedGraph(n)<<endl;

    return 0;
}

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

// use dfs to detect cycles on directed graph
// in order to detect cycle, we need to detect back-edge
bool DetectCycleByDFS_DirectedGraph(int n){
    
    int Pre[MAX_NODE_COUNT];
    int Post[MAX_NODE_COUNT];
    int iClock=0;

    for(int i=0;i<n;i++){ 
        Visited[i]=false;
        Pre[i]=0;
        Post[i]=0;
    }

    stack<int> s;
    s.push(0);
    Visited[0] = true;
    Pre[0] = ++iClock;

    while(!s.empty()){
        int u = s.top();

        bool bHasNeighbor = false;

            for(int v=0;v<n;v++){
                if(DirectedGraph[u][v]>0){
                    // if the u's child v has been visited but and checked
                    // edge u->v is a back-edge
                    // that means v must be the ancestor of u
                    // there is a cycle here
                    if(Visited[v]==true){
                        if(Post[v]>Post[u]&&Post[u]>Pre[u]&&Pre[u]>Pre[v]) return true;
                    }
            
                    if(Visited[v]==false){
                        bHasNeighbor = true;
                        s.push(v);
                        Visited[v] = true;
                        Pre[v] = ++iClock;
                    }
                }
            }


        //if no children found or every child has been visited, pop it
        if(bHasNeighbor == false){
            s.pop();
            Post[u] = ++iClock;
        }
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

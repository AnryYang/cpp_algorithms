/*************************************************************************
    > File Name: checkBipartite.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Fri 30 Sep 2016 01:28:03 PM SGT
 ************************************************************************/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
 * how to check if a conected graph is a bipartite graph
 * start from vertex s, mark it as level 0
 * mark the vertex v, which is dist(s ,v) far away from s, as level dist(s, v)
 * add vertices on odd number level into subset L, add vertices on event number level into subset R
 * if there are no edges among vertices on all odd levels or on all even levels , then we have a bipartite graph
 * this means we need to make sure that the two vertices of any edge belongs two different levels, one is odd level and another is even level
 * so if we can find that there is an edge, whose two vertices are all on even level, then we can say it's not a bipartite graph
 * simply, we can just label odd level vertices as 0, and even level vertices as 1, then the only thing we need to do is find an edge whose two vertices' labels' sum is not equal to 1
*/

bool CheckBipartiteByBFS(const vector<vector<int>> &graph){
    vector<bool> vecVisited;
    vector<int> vecLabels;

    for(int i=0;i<graph.size();i++){
        vecVisited.push_back(false);
        vecLabels.push_back(0);
    }

    deque<int> q;
    q.push_back(0);
    vecVisited[0] = true;
    vecLabels[0] = 1;

    while(!q.empty()){
        int u = q.front();

        q.pop_front();

        for(int i=0;i<graph[u].size();i++){
            int v = graph[u][i];

            if(vecVisited[v] != true){
                vecVisited[v] = true;
                vecLabels[v] = 1-vecLabels[u];
                q.push_back(v);
            }
            else{
                if(vecLabels[u] + vecLabels[v] != 1){
                    return false;
                }
            }
        }
    }

    return true;
}

int main(){

    vector<vector<int>> Graph;

    cout<<"Please input node count and edge count:"<<endl;
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        vector<int> vecAdjNodes;
        Graph.push_back(vecAdjNodes);
    }

    cout<<"Please input edge: start-vertex end-vertex"<<endl;
    for(int i=0;i<m;i++){
        int s,t;
        cin>>s>>t;
        Graph[s].push_back(t);
        Graph[t].push_back(s);
    }

    if(CheckBipartiteByBFS(Graph)) cout<<"the graph is a bipartite graph"<<endl;
    else cout<<"the graph is not a bipartite graph"<<endl;

    return 0;
}

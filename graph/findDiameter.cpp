/*************************************************************************
    > File Name: findDiameter.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Fri 30 Sep 2016 11:15:18 AM SGT
 ************************************************************************/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
 * idea: start from a arbitrary node v, find the furthest node s of v by BFS
 * start from u, find the furthest node t of s by BFS
 * the shortest disatnce between (s, t) is the diameter
 * see proof on http://stackoverflow.com/questions/25649166/linear-algorithm-of-finding-tree-diameter
*/

void FindFurthestNodeByBFS(const vector<vector<int>> &tree, int start, int *result){
    vector<bool> vecVisited;
    vector<int> vecDistToStart;

    for(int i=0;i<tree.size();i++){
        vecVisited.push_back(false);
        vecDistToStart.push_back(0);
    }

    deque<int> q;

    int iFurthestNode=0;
    int iFurthestDist=0;

    q.push_back(start);
    vecVisited[start]=true;

    while(!q.empty()){
        int u = q.front();
        q.pop_front();

        for(int i=0;i<tree[u].size();i++){
            int v = tree[u][i];
            if(vecVisited[v]!=true){
                vecVisited[v]=true;
                vecDistToStart[v]=vecDistToStart[u]+1;
                if(vecDistToStart[v]>iFurthestDist){
                    iFurthestNode = v;
                    iFurthestDist = vecDistToStart[v];
                }
                q.push_back(v);
            }
        }
    }

    result[0] = iFurthestNode;
    result[1] = iFurthestDist;
}

int FindTreeDiameter(const vector<vector<int>> &tree){
    int start = 0;

    int result[2];
    
    FindFurthestNodeByBFS(tree, start, result);
    int s = result[0];

    FindFurthestNodeByBFS(tree, s, result);
    int t = result[0];
    int iDiameter = result[1];

    cout<<"The Diameter is "<<iDiameter<<", the distance between node "<<s<<" and node "<<t<<endl;

    return iDiameter;
}

int FindGraphDiameter(){
    return 0;
}

int main(){

    vector<vector<int>> Tree;
    vector<vector<int>> Graph;

    int n;
    cout<<"Please input node count:"<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        vector<int> vecAdjNodes;
        Tree.push_back(vecAdjNodes);
    }

    int s,t;
    for(int i=0;i<n-1;i++){
        cin>>s>>t;
        Tree[s].push_back(t);
        Tree[t].push_back(s);
    }

    int iDiameter = FindTreeDiameter(Tree);

    return 0;
}

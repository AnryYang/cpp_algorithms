/*************************************************************************
    > File Name: maxNetworkFlow.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Thu 22 Sep 2016 05:24:17 PM
 ************************************************************************/

#include<iostream>
#include<queue>
#include<stack>

using namespace std;

#define MAX_NODE_COUNT 100
int Edge[MAX_NODE_COUNT][MAX_NODE_COUNT]; //edgs, Edge[i][j] denotes capacity
int ResiEdge[MAX_NODE_COUNT][MAX_NODE_COUNT];
int Visited[MAX_NODE_COUNT]; //visited nodes 
int Pre[MAX_NODE_COUNT];  //save an found augment path

bool DFS(int n){
  // empty the previous augmenting path and visited list
  for(int i=0;i<n;i++){
     Visited[i]=0;
     Pre[i]=-1;
  }
  
  stack<int> s;
  s.push(0);
  Pre[0]=-1; //source node has no previous node
  Visited[0]=1;

  while(!s.empty()){
     int u = s.top();
     
     bool bHasNeighbor = false;
     for(int v=0;v<n;v++){
       if(ResiEdge[u][v]>0 && Visited[v]==0){ //an valid neighbor node
         bHasNeighbor = true;
         Visited[v] = 1;
         Pre[v] = u;
         s.push(v);
         if(v == n-1){ // reach the sink node, there is an augmenting path
           return true;
         }
       }
     }
     if(bHasNeighbor == false) s.pop(); // if node neighbors, pop it from stack
  }
  return false;
}

bool BFS(int n){
   // empty the previous augmenting path and visited list
   for(int i=0;i<n;i++){
     Visited[i]=0;
     Pre[i]=-1;
   }

   deque<int> q;
   q.push_back(0);
   Pre[0] = -1; // source node has no previous node
   Visited[0]=1;

   while(!q.empty()){
       int u = q.front();
       q.pop_front();

       // access all neighbors
       for(int v=0;v<n;v++){
         if(ResiEdge[u][v]>0 && Visited[v]==0){ //invalid neighbor
           Visited[v]=1;
           Pre[v] = u;
           if(v == n-1){ // reach the sink node, there is an augmenting path
             return true;
           }
           else{
             q.push_back(v);
           }
         }
       } 
   }

   return false;
}

int Augment(int n){ //augment along this path

    int iBottleNeck=ResiEdge[Pre[n-1]][n-1];
    
    int v =n-2;

    while(Pre[v]>=0){ // find the bottleneck capacity of this path
      iBottleNeck = min(iBottleNeck, ResiEdge[Pre[v]][v]);
      v = Pre[v];
    }

    v = n-1;
    while(Pre[v]>=0){ //update residual graph
      ResiEdge[Pre[v]][v]-=iBottleNeck; // reduce capacity
      ResiEdge[v][Pre[v]]+=iBottleNeck; // add flow
      v = Pre[v];
    }

    return iBottleNeck;
}

int FordFulkerson(int n, int m){
    int iMaxFlow=0;

    copy(&Edge[0][0], &Edge[0][0]+MAX_NODE_COUNT*MAX_NODE_COUNT, &ResiEdge[0][0]);

    while(DFS(n)){ //find an augmenting path
      iMaxFlow += Augment(n); //augment along this path
    }

    return iMaxFlow;
}

int EdmondsKarp(int n, int m){
    int iMaxFlow=0;

    copy(&Edge[0][0], &Edge[0][0]+MAX_NODE_COUNT*MAX_NODE_COUNT, &ResiEdge[0][0]);

    while(BFS(n)){ //find an augmenting path which is shortest
      iMaxFlow += Augment(n); //augment along this path
    }

    return iMaxFlow;
}

int main(){
  int n,m;

  cin>>n>>m; // input vertices count, edge count
  for(int i=0;i<m;i++){
    int src,tgt,cap;
    cin>>src>>tgt>>cap; //input an edge, src is from-node, tgt is to-node, cap is capacity
    Edge[src][tgt]+=cap;
  }

  cout<<"FordFulkerson:"<<FordFulkerson(n, m)<<endl;
  cout<<"EdmondsKarp:"<<EdmondsKarp(n, m)<<endl;
  return 0;
}

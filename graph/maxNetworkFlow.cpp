/*************************************************************************
    > File Name: maxNetworkFlow.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Thu 22 Sep 2016 05:24:17 PM
 ************************************************************************/

#include<iostream>
#include<queue>
#include<stack>
#include<vector>

using namespace std;

#define MAX_NODE_COUNT 100
int Edge[MAX_NODE_COUNT][MAX_NODE_COUNT]; //edgs, Edge[i][j] denotes capacity
int ResiEdge[MAX_NODE_COUNT][MAX_NODE_COUNT];
int Visited[MAX_NODE_COUNT]={0}; //visited nodes 
int Pre[MAX_NODE_COUNT]={0};  //save an found augment path
int Layers[MAX_NODE_COUNT]={0}; //save the layer number of nodes

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
         if(v == n-1){ // reach the sink node, there is an augmenting path
           return true;
         }
         s.push(v);
       }
     }
     if(bHasNeighbor == false) s.pop(); // if node has no valid neighbors, pop it from stack
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
           q.push_back(v);
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

bool Layer(int n){
  // empty the previous augmenting path and visited list
  for(int i=0;i<n;i++){
     Layers[i]=-1;
  }
  
  deque<int> q;
  q.push_back(0);

  while(!q.empty()){
     int u = q.front();
     q.pop_front();
     
     for(int v=0;v<n;v++){
       if(ResiEdge[u][v]>0 && Layers[v]==-1){ //an valid and not layered neighbor node
         Layers[v] = Layers[u]+1;
         if(v == n-1){ // reach the sink node, there is an augmenting path
            return true;
         }
         q.push_back(v);
       }
     }
  }
  return false;
}

int Dinic(int n, int m){
    int iMaxFlow=0;

    copy(&Edge[0][0], &Edge[0][0]+MAX_NODE_COUNT*MAX_NODE_COUNT, &ResiEdge[0][0]);

    stack<int> s;

    while(Layer(n)){
        for(int i=0;i<n;i++){
            Visited[i]=0;
            Pre[i]=-1;
        }

        s.push(0);
        
        while(!s.empty()){
            int u = s.top();
            
            //reach the sink node
            if(u==n-1){
                // convert stack into vector
                vector<int> vecStack(&s.top()+1-s.size(), &s.top()+1);

                int iBottleNeckSrc=vecStack[vecStack.size()-2];
                int iBottleNeck=ResiEdge[vecStack[vecStack.size()-2]][vecStack[vecStack.size()-1]];

                // get augmenting path from stack
                for(int i=vecStack.size()-1;i>0;i--){
                     if(ResiEdge[vecStack[i-1]][vecStack[i]] < iBottleNeck){
                         iBottleNeck = ResiEdge[vecStack[i-1]][vecStack[i]];
                         iBottleNeckSrc = vecStack[i-1];
                     }
                     Pre[vecStack[i]]=vecStack[i-1];  
                }

                //augment along the path
                iMaxFlow += Augment(n);

                //pop stack until the top is iBottleNeckSrc
                while(!s.empty()&&s.top()!=iBottleNeckSrc){
                    Visited[s.top()]=0;
                    Pre[s.top()]=-1;
                    s.pop();
                }
            }
            else{ //push layered node into stack
                bool bHasNeighbor = false;
                for(int v=0;v<n;v++){
                   if(ResiEdge[u][v]>0 && Visited[v]==0 && Layers[v]==Layers[u]+1){ // push valid and not visited and next-layer node
                       bHasNeighbor = true;
                       s.push(v);
                       Visited[v]=1;
                       break;
                    }
                }

                if(bHasNeighbor == false) s.pop(); // if node has no valid neighbors, pop it from stack
            }
        }
    }
    return iMaxFlow;
}

int main(){
  int n,m;

  cout<<"Please input vertex count and edge count (seperate them by one space):"<<endl;
  cin>>n>>m; // input vertices count, edge count
  cout<<"Please input edges, each edge one line in the form 'start-vertex end-vertex':"<<endl;
  for(int i=0;i<m;i++){
    int src,tgt,cap;
    cin>>src>>tgt>>cap; //input an edge, src is from-node, tgt is to-node, cap is capacity
    Edge[src][tgt]+=cap;
  }

  cout<<"FordFulkerson:"<<FordFulkerson(n, m)<<endl;
  cout<<"EdmondsKarp:"<<EdmondsKarp(n, m)<<endl;
  cout<<"Dinic:"<<Dinic(n, m)<<endl;
  return 0;
}

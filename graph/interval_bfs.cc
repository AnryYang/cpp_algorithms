/*************************************************************************
    > File Name: interval_bfs.cc
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Sun 04 Dec 2016 08:17:34 PM
 ************************************************************************/

#include "graph.h"
#include<queue>

void visit(NodeID nid){
    std::cout << "visiting vertex:" << nid << std::endl;
}

void BFS(Graph &graph){
    std::queue<NodeID> q;
    NodeID start = 1;
    q.push(start);
    graph.mark(start);
    visit(start);

    while(! q.empty()){
        NodeID u = q.front();
        q.pop();

        std::vector<NodeID> unvisited_neighbors = graph.get_out_neighbors(u, true);
        for(int i=0;i<unvisited_neighbors.size();i++){
            q.push(unvisited_neighbors[i]);
            graph.mark(unvisited_neighbors[i]);
            visit(unvisited_neighbors[i]);
        }
    }

    graph.clear_marks();
}

void Interval_BFS(Graph &graph){
    int r,w;
    std::queue<NodeID> q;
    NodeID start = 1;
    q.push(start);
    w++;
    graph.mark(start);
    visit(start);
    r++;

    while(! q.empty()){
        NodeID u = q.front();
        q.pop();

        std::vector<NodeID> unvisited_neighbors = graph.get_out_neighbors(u, true);
        for(int i=0;i<unvisited_neighbors.size();i++){
            NodeID v = unvisited_neighbors[i];
            if(graph.get_in_neighbors(v, true).size()!=0)
                continue;
            visit(v);
            r++;
            std::vector<NodeID> unvisited_grand_neighbors = graph.get_out_neighbors(v, true);
            for(int j=0;j<unvisited_grand_neighbors.size();j++){
                q.push(unvisited_grand_neighbors[j]);
                w++;
                graph.mark(unvisited_grand_neighbors[j]);
                visit(unvisited_grand_neighbors[j]); 
                r++;               
            }
        }
    }

    std::cout << "alpha:" << double(w)/double(r) << std::endl;
    graph.clear_marks();
}

int main(){
    std::string config_file = "g.data.conf";
    std::string graph_file = "g.data";

    Graph graph(graph_file, config_file);

    std::cout << "avg degree:" << graph.get_avg_degree() << std::endl;

    // graph.print_edges();

    Interval_BFS(graph);

    return 0;
}





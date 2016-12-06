/*************************************************************************
    > File Name: graph.h
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Sun 04 Dec 2016 08:20:16 PM
 ************************************************************************/
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
#include<assert.h>
#include<iomanip>

typedef int NodeID;
typedef double Weight;
typedef std::string Label;
typedef std::pair<NodeID, Label> Vertex;
typedef std::vector< std::map<NodeID, Weight> > Edges;
typedef std::vector< Vertex > Vertices;
typedef std::vector< bool > Marks;

inline bool exists_test(const std::string &name){
    std::ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    }
    else {
        f.close();
        return false;
    }
}

inline void assert_file_exist(std::string desc, std::string name) {
    if (!exists_test(name)) {
        std::cerr << desc << " " << name << " not found!" << std::endl;
        exit(1);
    }
}

class Graph{
public:
    Graph(){}
    Graph(const std::string strGraphFile, const std::string strConfFile){
        init_config(strConfFile);
        init_graph(strGraphFile);
    }
    ~Graph(){}

    int node_count(){
        return m_n;
    }

    long long edge_count(){
        return m_m;
    }

    int get_indegree(const NodeID nid){
        if(!check_vertex(nid-1)) return 0;
        return m_reverse_edges[nid-1].size();
    }

    int get_outdegree(const NodeID nid){
        if(!check_vertex(nid-1)) return 0;
        return m_edges[nid-1].size();
    }

    double get_avg_degree(){
        return double(m_m)/double(m_n);
    }

    Weight get_edge_weight(const NodeID sid, const NodeID tid){
        if(!check_vertex(sid-1)||!check_vertex(tid-1)) return 0.0;

        if(m_edges[sid].find(tid-1)!=m_edges[sid-1].end())
            return m_edges[sid-1][tid-1];
        else
            return 0.0;        
    }

    bool check_vertex(const NodeID nid){
        return (m_vertices.size()<nid)?false:true;
    }

    bool check_edge(const NodeID sid, const NodeID tid){
        if(!check_vertex(sid)||!check_vertex(tid)) return false;

        if(m_edges[sid-1].find(tid-1)!=m_edges[sid-1].end())
            return true;
        else
            return false;
    }

    bool check_reverse_edge(const NodeID sid, const NodeID tid){
        if(!check_vertex(sid)||!check_vertex(tid)) return false;
        
        if(m_reverse_edges[sid-1].find(tid-1)!=m_reverse_edges[sid-1].end())
            return true;
        else
            return false;
    }

    std::vector<NodeID> get_in_neighbors(NodeID nid, bool only_unmark=false){
        std::vector<NodeID> vecNodes;
        if(!check_vertex(nid)) return vecNodes;
        std::map<NodeID, Weight>::const_iterator iter = m_reverse_edges[nid-1].begin();
        for(; iter!=m_reverse_edges[nid-1].end();iter++){
            if( (only_unmark && !check_mark(iter->first+1)) ||  !only_unmark)
                vecNodes.push_back(iter->first+1);
        }
        return vecNodes;
    }

    std::vector<NodeID> get_out_neighbors(NodeID nid, bool only_unmark=false){
        std::vector<NodeID> vecNodes;
        if(!check_vertex(nid)) return vecNodes;
        std::map<NodeID, Weight>::const_iterator iter = m_edges[nid-1].begin();
        for(; iter!=m_edges[nid-1].end();iter++){
            if( (only_unmark && !check_mark(iter->first+1)) ||  !only_unmark)
                vecNodes.push_back(iter->first+1);
        }

        return vecNodes;
    }

    void clear_marks(){
        marks.clear();
        marks = Marks(m_n, false);        
    }

    void mark(const NodeID nid){
        marks[nid-1] = true;
    }

    bool check_mark(const NodeID nid){
        return marks[nid-1];
    }

    void print_edges(){
        for(int v=1;v<=m_n;v++){
            std::cout << "vertex:" << v <<std::endl;
            std::map<NodeID, Weight>::const_iterator iter = m_edges[v-1].begin();
            for(; iter!=m_edges[v-1].end();iter++){
                std::cout << std::setw(16) << std::left << "neighbor:" << iter->first << " weight:" << iter->second << std::endl;
            }
        }
    }

protected:
    void init_config(const std::string strConfFile){
        assert_file_exist("Graph config file", strConfFile);

        std::ifstream ifs(strConfFile);
        std::string line;

        while ( getline (ifs, line) ){
            std::size_t loc = line.find("=");

            if(loc != std::string::npos){
                if(line.substr(0, loc) == "vertex")
                    m_n = atoi( line.substr(loc+1).c_str() );
                else if(line.substr(0, loc) == "edge")
                    m_m = atoi( line.substr(loc+1).c_str() );
                else if(line.substr(0, loc) == "directed")
                    isDirected = (atoi( line.substr(loc+1).c_str() )>0)?true:false;
                else if(line.substr(0, loc) == "weighted")
                    isWeighted = (atoi( line.substr(loc+1).c_str() )>0)?true:false;
            }

            loc = line.find(",");
            if(loc != std::string::npos){
                NodeID nid = atoi( line.substr(0, loc).c_str() );
                Label label = line.substr(loc+1);
                m_vertices.push_back( std::make_pair(nid, label) );
            }
        }
        
        if(m_vertices.size()!=m_n){
            for(int i=0;i<m_n;i++) m_vertices.push_back( std::make_pair(i, "") );
        }

        marks = Marks(m_n, false); 
        m_edges.resize(m_n);
        m_reverse_edges.resize(m_n);
    }

    void init_graph(const std::string strGraphFile){
        assert_file_exist("Graph file", strGraphFile);

        FILE *fin = fopen(strGraphFile.c_str(), "r");
        int s, t;
        double w;

        if(isWeighted){
            while (fscanf(fin, "%d%d%lf", &s, &t, &w) != EOF) {
                assert(s <= m_n);
                assert(t <= m_n);

                if(isDirected){
                    m_edges[s-1][t-1] = w;
                    m_reverse_edges[t-1][s-1] = w;
                }
                else{
                    m_edges[s-1][t-1] = w;
                    m_edges[t-1][s-1] = w;
                    m_reverse_edges[s-1][t-1] = w;   
                    m_reverse_edges[t-1][s-1] = w;                  
                }
            }
        }else{
            while (fscanf(fin, "%d%d", &s, &t) != EOF) {
                assert(s <= m_n);
                assert(t <= m_n);

                if(isDirected){
                    m_edges[s-1][t-1] = 1.0;
                    m_reverse_edges[t-1][s-1] = 1.0;
                }
                else{
                    m_edges[s-1][t-1] = 1.0;
                    m_edges[t-1][s-1] = 1.0;
                    m_reverse_edges[s-1][t-1] = 1.0;   
                    m_reverse_edges[t-1][s-1] = 1.0;                  
                }
            }
        }
    }

private:
    int m_n;
    long long m_m;
    bool isDirected;
    bool isWeighted;
    Edges m_edges;
    Edges m_reverse_edges;
    Vertices m_vertices;
    Marks marks;
};

#endif




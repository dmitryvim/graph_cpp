//
//  graph.hpp
//  graph
//
//  Created by Dmitry Mikhaylovich on 09.10.15.
//  Copyright © 2015 Dmitry Mikhaylovich. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include <map>







class graph {
    typedef float weight_t;
    typedef char color_t;
    
    
    
private:
    
    bool directed;
    bool weighted;
    
    struct Vertex {
        typedef std::pair<Vertex*, weight_t> __Edge;
        typedef std::list<__Edge> __EdgeList;
        __EdgeList edges;

        int data;
        
        
        Vertex* previous = nullptr;
        color_t color;
        
        Vertex (int _data):data(_data) {};
        Vertex () {};
        
        int time_start;
        int time_finish;
        int time_up;
        
        int component_index;
        
        Vertex* transposed = nullptr;
        
        Vertex* find_set () {
            if (previous == nullptr || previous == this) {
                return this;
            } else {
                return this->previous = previous->find_set();
            }
        };
        
        void union_set (Vertex* par) {
            this->find_set()->previous = par->find_set();
        };
    };
    
    struct Edge {
        Vertex* left;
        Vertex* right;
        weight_t weight;
        
        Edge (Vertex* _left, Vertex* _right, weight_t _weight): left(_left), right(_right), weight(_weight) {};
        
        bool operator < (const Edge& E) const {
            return (this->weight < E.weight) || ((this->weight == E.weight) && !(this->left == E.left && this->right == E.right) && !(this->right == E.left && this->left == E.right));
        };
    };
    

    
    typedef std::vector<Vertex> __VertexList;
    typedef __VertexList::iterator __VertexIterator;
    typedef std::deque<Vertex*> __VertexPointerList;
    typedef __VertexPointerList::iterator __VertexPointerIterator;
    typedef Vertex::__EdgeList::iterator __EdgeIterator;
    typedef std::set<Edge> __EdgeSet;
    typedef __EdgeSet::iterator __EdgeSetIterator;
    typedef std::set<Vertex*> __VertexPointerSet;
    typedef __VertexPointerSet::iterator __VertexPointerSetInterator;

    
    __VertexList vertexes;
    __VertexPointerList topologically_sorted;
    int component_count;
    __EdgeSet bridges;
    __VertexPointerSet cut_points;
    __EdgeSet ostov;
    
    
    void newDirectedEdge (Vertex* left, Vertex* right, weight_t weight = 1);
    void newEdge (Vertex* left, Vertex* right, weight_t weight = 1);
    void deleteDirectedEdge (Vertex* left, Vertex* right);
    void deleteEdge (Vertex* left, Vertex* right);
    void deleteOutway (Vertex* vertex);
    void deleteInway (Vertex* vertex);
    weight_t** newMatrix ();
    void bfs_weighted (Vertex* vertex);
    void bfs_unweighted (Vertex* vertex);
    void dfs (Vertex* vertex, int &time);
    void dijkstra(Vertex* vertex);
    
    
    
public:
    

    graph (size_t size, bool _directed = false, bool _weighted = false);
    ~graph ();
    
    size_t vertexesCount ();
    size_t edgesCount ();
    
    void resize (size_t size);
    
    void newVertex ();
    void newEdge (int left, int right, weight_t weight = 1);
    void deleteVertex (int index);
    void deleteEdge (int left, int right);
    
    void asign (weight_t** matrix, size_t size);
    
    void readFromFileAsMatrix (std::string filename);
    void readFromFileAsEdgeList (std::string filename);
    
    void print ();
    void printAsMatrix ();
    
    void bfs (int from);
    void print_bfs ();
    
    void dfs ();
    void print_dfs ();
    void print_component ();
    void print_topologically_sorted ();
    void strong_component ();

    void print_bridges ();
    void print_cutpoints ();
    
    void ostov_prima ();
    void ostov_kruskal ();
    void print_ostov ();
    
    void dijkstra (int from);

    //дейкстра
    
    
    
    
    
};



#endif /* graph_hpp */

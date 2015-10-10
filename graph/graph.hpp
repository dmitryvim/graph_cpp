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







class graph {
    typedef double weight_t;
    typedef char color_t;
    
    
    
private:
    
    bool directed;
    bool weighted;
    
    struct Vertex {
        typedef std::list< std::pair<Vertex*, int> > __EdgeList;
        __EdgeList edges;

        int data;
        
        
        Vertex* previous = nullptr;
        color_t color;
        
        Vertex (int _data):data(_data) {};
        Vertex () {};
        
        int time_start;
        int time_finish;
        
        int component_index;
        
        Vertex* transposed = nullptr;
    };
    
    typedef std::vector<Vertex> __VertexList;
    typedef __VertexList::iterator __VertexIterator;
    typedef std::deque<Vertex*> __VertexPointerList;
    typedef __VertexPointerList::iterator __VertexPointerIterator;
    typedef Vertex::__EdgeList::iterator __EdgeIterator;
    
    __VertexList vertexes;
    __VertexPointerList topologically_sorted;
    int component_count;
    
    
    
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

    //мосты
    //точки сочленения
    //остовные деревья
    
    
    
    
    
};



#endif /* graph_hpp */

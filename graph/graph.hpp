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
#include <list>
#include <string>
#include <fstream>
#include <iostream>






class graph {
    
    
    
    
private:
    bool directed;
    bool weighted;
    
    struct Vertex {
        typedef std::list< std::pair<Vertex*, int> > __EdgeList;
        
        
        __EdgeList edges;
        //pair <vertex to, edge weight>
        int data;
        
        Vertex (int _data):data(_data) {};
        Vertex () {};
        
    };
    
    typedef std::vector<Vertex> __VertexList;
    typedef __VertexList::iterator __VertexIterator;
    typedef Vertex::__EdgeList::iterator __EdgeIterator;
    typedef double weight_t;
    
    
    __VertexList vertexes;
    
    
    void newDirectedEdge (Vertex* left, Vertex* right, weight_t weight = 1);
    void newEdge (Vertex* left, Vertex* right, weight_t weight = 1);
    void deleteDirectedEdge (Vertex* left, Vertex* right);
    void deleteEdge (Vertex* left, Vertex* right);
    void deleteOutway (Vertex* vertex);
    void deleteInway (Vertex* vertex);
    
    weight_t** newMatrix ();
    
    
public:
    
    graph (bool _directed = false, bool _weighted = false);
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
    
    
    //добавить ребро
    //прочитать из файла
    //получить из двумерной матрицы
    
    //вывести на экран
    //  как списки смежности
    //  как двумерную матрицу
    
    //обход в ширину
    //обход в глубину
    //кратчайший путь (обход в ширину)
    //топологическая сортировка
    //компоненты связности
    //сильные компоненты связности
    //мосты
    //точки сочленения
    //остовные деревья
    
    
    
    
    
};



#endif /* graph_hpp */

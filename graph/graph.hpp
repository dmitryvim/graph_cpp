//
//  graph.hpp
//  graph
//
//  Created by Dmitry Mikhaylovich on 08.10.15.
//  Copyright © 2015 Dmitry Mikhaylovich. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include <vector>
#include <deque>
#include <list>

using namespace std;


template <class T, bool oriented = true>
class Graph {
    

private:
    struct Vertex {
        list< pair<Vertex*, int> > edges;
        int index;
        T data;
        
    };
    
    vector<Vertex> vertexes;
    
public:
    
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

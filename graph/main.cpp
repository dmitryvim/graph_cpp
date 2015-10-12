//
//  main.cpp
//  graph
//
//  Created by Dmitry Mikhaylovich on 08.10.15.
//  Copyright © 2015 Dmitry Mikhaylovich. All rights reserved.
//

#include <iostream>
#include "graph.hpp"


int main(int argc, const char * argv[]) {
    /*graph gr(10, true, false);
    gr.newEdge(1, 2);
    gr.newEdge(2, 3);
    gr.newEdge(3, 4);
    gr.newEdge(4, 1);
    gr.newEdge(2, 6);
    gr.newEdge(3, 5);
    gr.newEdge(5, 6);
    gr.newEdge(6, 7);
    gr.newEdge(7, 5);
    gr.newEdge(5, 0);
    gr.newEdge(7, 9);
    gr.newEdge(4, 8);
    gr.newEdge(8, 9);
    gr.newEdge(9, 8);
     */
    
    /*
    graph gr(11, false, false);
    gr.newEdge(1, 2);
    gr.newEdge(2, 3);
    gr.newEdge(3, 4);
    gr.newEdge(4, 1);
    gr.newEdge(3, 5);
    gr.newEdge(5, 6);
    gr.newEdge(6, 7);
    gr.newEdge(7, 5);
    gr.newEdge(5, 0);
    gr.newEdge(4, 8);
    gr.newEdge(8, 9);
    gr.newEdge(0, 10);*/
    
    /*
    graph gr(9, false, true);
    gr.newEdge(0, 1, 4);
    gr.newEdge(0, 7, 8);
    gr.newEdge(1, 7, 11);
    gr.newEdge(1, 2, 9);
    gr.newEdge(2, 8, 1);
    gr.newEdge(2, 3, 7);
    gr.newEdge(2, 5, 4);
    gr.newEdge(3, 5, 14);
    gr.newEdge(3, 4, 9);
    gr.newEdge(4, 5, 10);
    gr.newEdge(5, 6, 2);
    gr.newEdge(6, 7, 1);
    gr.newEdge(6, 8, 6);
    gr.newEdge(7, 8, 7);
     */
    
    graph gr(9, false, true);
    gr.newEdge(0, 1, 4);
    gr.newEdge(0, 7, 3);
    gr.newEdge(1, 7, 11);
    gr.newEdge(1, 2, 8);
    gr.newEdge(2, 8, 1);
    gr.newEdge(2, 3, 7);
    gr.newEdge(2, 5, 10);
    gr.newEdge(3, 5, 14);
    gr.newEdge(3, 4, 9);
    gr.newEdge(4, 5, 10);
    gr.newEdge(5, 6, 2);
    gr.newEdge(6, 7, 1);
    gr.newEdge(6, 8, 6);
    gr.newEdge(7, 8, 2);

    
    
    gr.print();
    gr.dijkstra(4);
    gr.print_bfs();
    
    
    return 0;
}

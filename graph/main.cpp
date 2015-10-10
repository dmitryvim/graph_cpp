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
    graph gr(10, true, false);
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
    gr.print();
    gr.dfs();
    gr.print_dfs();
    gr.print_component();
    gr.print_topologically_sorted();
    gr.strong_component();
    gr.print_component();
    
    return 0;
}

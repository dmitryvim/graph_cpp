//
//  graph.cpp
//  graph
//
//  Created by Dmitry Mikhaylovich on 09.10.15.
//  Copyright © 2015 Dmitry Mikhaylovich. All rights reserved.
//

#include "graph.hpp"
#include <queue>


void graph::newDirectedEdge (Vertex* left, Vertex* right, weight_t weight) {
    left->edges.push_back(std::make_pair(right, weight));
};



void graph::newEdge (Vertex* left, Vertex* right, weight_t weight) {
    newDirectedEdge(left, right, weight);
    if (!directed) {
        newDirectedEdge(right, left, weight);
    }
};

void graph::deleteDirectedEdge (Vertex* left, Vertex* right) {
    for (__EdgeIterator E = left->edges.begin(); E != left->edges.end(); ++E) {
        if (E->first == right) {
            left->edges.erase(E);
        }
    }
};


void graph::deleteEdge (Vertex* left, Vertex* right) {
    deleteDirectedEdge(left, right);
    if (!directed) {
        deleteDirectedEdge(right, left);
    }
};

void graph::deleteOutway (Vertex* vertex) {
    vertex->edges.clear();
};


void graph::deleteInway (Vertex* vertex) {
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        deleteDirectedEdge(&(*V), vertex);
    }
};



graph::weight_t** graph::newMatrix () {
    size_t size = vertexesCount();
    weight_t** matrix = new weight_t*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new weight_t[size];
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
};






graph::graph (size_t size, bool _directed, bool _weighted): directed(_directed), weighted(_weighted) {
    resize(size);
};

graph::~graph () {
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        V->edges.clear();
    }
    vertexes.clear();
};

size_t graph::vertexesCount () {
    return vertexes.size();
};


size_t graph::edgesCount () {
    size_t count = 0;
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        count += V->edges.size();
    }
    return count;
};



void graph::resize (size_t size) {
    vertexes.resize(size);
    for (int i = 0; i < size; ++i) {
        vertexes[i].data = i;
    }
};


void graph::newVertex () {
    int index = (int)vertexes.size();
    vertexes.push_back(Vertex(index));
};

void graph::newEdge (int left, int right, weight_t weight) {
    newEdge(&vertexes[left], &vertexes[right], weight);
};

void graph::deleteVertex (int index) {
    Vertex* vertex = &vertexes[index];
    deleteInway(vertex);
    deleteOutway(vertex);
    vertexes.erase(vertexes.begin() + index);
};

void graph::deleteEdge (int left, int right) {
    deleteEdge(&vertexes[left], &vertexes[right]);
};

void graph::asign (weight_t** matrix, size_t size) {
    resize(size);
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (matrix[y][x] > 0) {
                newEdge(y, x, matrix[y][x]);
            }
        }
    }
};

void graph::readFromFileAsMatrix (std::string filename) {
    std::ifstream fin(filename);
    size_t size;
    fin >> size;
    weight_t** matrix = new weight_t*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new weight_t[size];
    }
    
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            fin >> matrix[y][x];
        }
    }
    
    asign(matrix, size);
    
    for (int i = 0; i < size; ++i) {
        delete []matrix[i];
    }
    delete []matrix;
    fin.close();
};

void graph::readFromFileAsEdgeList (std::string filename) {
    std::ifstream fin(filename);
    size_t size;
    fin >> size;
    int count;
    int left, right;
    fin >> count;
    resize(size);
    for (int i = 0; i < count; ++i) {
        fin >> left >> right;
        newEdge(left, right);
    }
    fin.close();
};

void graph::print () {
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        std::cout << V->data;
        for (__EdgeIterator E = V->edges.begin(); E != V->edges.end(); ++E) {
            std::cout << " ->" << E->first->data;
        }
        std::cout << std::endl;
    }
};



void graph::printAsMatrix () {
    size_t size = vertexesCount();
    weight_t** matrix = newMatrix();
    
    
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        for (__EdgeIterator E = V->edges.begin(); E != V->edges.end(); ++E) {
            matrix[V->data][E->first->data] = E->second;
        }
    }
    
    std::cout << size << std::endl;
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            std::cout << matrix[y][x] << " ";
        }
        std::cout << std::endl;
    }
    
    
    for (int i = 0; i < size; ++i) {
        delete []matrix[i];
    }
    delete []matrix;
};

void graph::bfs_weighted (Vertex* vertex) {/*
    typedef std::pair<Vertex*, weight_t> queuer;
    class compare_queuer {
    public:
        bool operator()(const queuer &p, const queuer &q) {
            return (p.second > q.second);
        };
    };
    
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        V->color = 0;
        V->previous = nullptr;
    }
    
    std::priority_queue<queuer, std::vector<queuer>, compare_queuer> qWay;
    int distance = 0;
    qWay.push(std::make_pair(vertex, distance));
    
    
    
    printf("Start debug\n");
    while (!qWay.empty()) {
        distance = qWay.top().second;
        vertex = qWay.top().first;
        qWay.pop();
        printf("pop %d distance = %d ", vertex->data, distance);
        
        if (!vertex->color) {
            printf("color = %d\n", vertex->color);
            vertex->color = 1;
            for (__EdgeIterator E = vertex->edges.begin(); E != vertex->edges.end(); ++E) {
                if (!E->first->color) {
                    E->first->previous = vertex;
                    qWay.push(std::make_pair(E->first, distance + E->second));
                    printf("push %d distance = %d\n", E->first->data, distance + E->second);
                }
            }
        }
    }*/
    printf("DFS FOR WEIGHTED IGNORED\n");
};

void graph::bfs_unweighted (Vertex* vertex) {
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        V->color = 0;
        V->previous = nullptr;
    }
    
    
    std::queue<Vertex*> qWay;
    qWay.push(vertex);
    vertex->color = 1;
    
    while (!qWay.empty()) {
        vertex = qWay.front();
        qWay.pop();
        
        for (__EdgeIterator E = vertex->edges.begin(); E != vertex->edges.end(); ++E) {
            if (!E->first->color) {
                E->first->color = 1;
                E->first->previous = vertex;
                qWay.push(E->first);
            }
        }
        
    }
}

void graph::bfs (int from) {
    if (weighted) {
        bfs_weighted(&vertexes[from]);
    } else {
        bfs_unweighted(&vertexes[from]);
    }
};



void graph::print_bfs () {
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        std::cout << V->data;
        Vertex* prev_vertex = V->previous;
        while (prev_vertex != nullptr) {
            std::cout << " <- " << prev_vertex->data;
            prev_vertex = prev_vertex->previous;
        }
        std::cout << std::endl;
    }
    
};

void graph::dfs (Vertex* vertex, int& time) {
    int children_count = 0;
    
    vertex->color = 1;
    vertex->time_start = ++time;
    vertex->time_up = time;

    vertex->component_index = component_count;
    
    for (__EdgeIterator E = vertex->edges.begin(); E != vertex->edges.end(); ++E) {

        
        if (E->first != vertex->previous) {
            if (E->first->color == 1) {
                vertex->time_up = std::min(vertex->time_up, E->first->time_up);
            }
            if (E->first->color == 0) {
                E->first->previous = vertex;
                dfs(E->first, time);
                vertex->time_up = std::min(vertex->time_up, E->first->time_up);

                if (E->first->time_up > vertex->time_start) {
                    bridges.insert(Edge(E->first, vertex, E->second));
                }
                
                if (E->first->time_up >= vertex->time_start && vertex->previous != nullptr) {
                    cut_points.insert(vertex);
                }
                
                
                children_count++;
            }
            
        }
    }
    
    if (vertex->previous == nullptr && children_count > 1)
        cut_points.insert(vertex);
    
    
    vertex->color = 2;
    vertex->time_finish = ++time;
    topologically_sorted.push_front(vertex);
    
};

void graph::dfs () {
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        V->color = 0;
        V->previous = nullptr;
        V->time_start = -1;
        V->time_finish = -1;
        V->time_up = -1;
        V->component_index = -1;
    }
    component_count = 0;
    topologically_sorted.clear();
    bridges.clear();
    cut_points.clear();
    
    int time = 0;
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        if (!V->color) {
            dfs(&(*V), time);
            component_count++;
        }
    }
};

void graph::print_dfs () {
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        std::cout << V->data << "[" << V->time_start << "; " << V->time_finish << "] (" << V->time_up << ") ";
        if (V->previous != nullptr) {
            std::cout << "<- " << V->previous->data;
        }
        std::cout << std::endl;
    }
    
};

void graph::print_component () {

        std::cout << "count = " << component_count << std::endl;
        for (int i = 0; i < component_count; i++) {
            std::cout << i << " { ";
            for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
                if (V->component_index == i) {
                    std::cout << V->data << " ";
                }
            }
            std::cout << "}\n";
        }

};

void graph::print_topologically_sorted () {
    for (__VertexPointerIterator V = topologically_sorted.begin(); V != topologically_sorted.end(); ++V) {
        std::cout << "> " << (*V)->data << " >";
    }
    std::cout << std::endl;
};

void graph::strong_component () {
    if (!directed) {
        return;
    }
    graph T(vertexesCount(), true, false);
    
    int iter_T = 0;
    for (__VertexPointerIterator V = topologically_sorted.begin(); V != topologically_sorted.end(); ++V, ++iter_T) {
        T.vertexes[iter_T].data = (*V)->data;
        (*V)->transposed = &T.vertexes[iter_T];
        T.vertexes[iter_T].transposed = (*V);
    }
    
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        for (__EdgeIterator E = V->edges.begin(); E != V->edges.end(); ++E) {
            T.newEdge(E->first->transposed, V->transposed);
        }
    }
    

    T.dfs();

    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        V->component_index = V->transposed->component_index;
    }
    component_count = T.component_count;
};

void graph::print_bridges () {
    for (__EdgeSetIterator B = bridges.begin(); B != bridges.end(); ++B) {
        std::cout << B->left->data << " <=> " << B->right->data << std::endl;
    }
};

void graph::print_cutpoints() {
    for (__VertexPointerSetInterator C = cut_points.begin(); C != cut_points.end(); ++C) {
        std::cout << (*C)->data << std::endl;
    }
};

void graph::ostov_prima () {
    ostov.clear();

    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        V->color = 0;
    }
    
    

    __EdgeSet Q;
    Q.insert(Edge(nullptr, &*vertexes.begin(), 0));
    
    
    size_t ostov_out = vertexesCount();
    while(ostov_out && !Q.empty()) {
        Edge edge = *Q.begin();
        Q.erase(Q.begin());
        
        
        
        if (!edge.right->color) {
            edge.right->color = 1;
            if (edge.left != nullptr) {
                ostov.insert(edge);
            }
            
            for (__EdgeIterator E = edge.right->edges.begin(); E != edge.right->edges.end(); ++E) {
                if (!E->first->color) {
                    Q.insert(Edge(edge.right, E->first, E->second));
                }
            }
            ostov_out--;
        }
        
    }
    
};



void graph::ostov_kruskal () {
        
    ostov.clear();
    __EdgeSet Q;
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        V->previous = nullptr;
        for (__EdgeIterator E = V->edges.begin(); E != V->edges.end(); ++E) {
            Q.insert(Edge(&*V, E->first, E->second));
        }
    }
    
    size_t n = vertexesCount() - 1;
    while (n) {
        Edge E = *Q.begin();
        Q.erase(Q.begin());
        
        if (E.left->find_set() != E.right->find_set()) {
            E.left->union_set(E.right);
            ostov.insert(E);
            n--;
        }

    }
    
    
};

void graph::print_ostov () {
    for (__EdgeSetIterator E = ostov.begin(); E != ostov.end(); ++E) {
        std::cout << E->left->data << " <=> " << E->right->data << std::endl;
    }
};

void graph::dijkstra (int from) {
    dijkstra(&vertexes[from]);
};

void graph::dijkstra (Vertex* vertex) {
    for (__VertexIterator V = vertexes.begin(); V != vertexes.end(); ++V) {
        V->previous = nullptr;
        V->color = 0;
    }

    __EdgeSet Q;
    Q.insert(Edge(nullptr, vertex, 0));
    
    
    
    while(!Q.empty()) {
        Edge edge = *Q.begin();
        Q.erase(Q.begin());
        
        
        if (!edge.right->color) {
            edge.right->color = 1;
            edge.right->previous = edge.left;
            
            for (__EdgeIterator E = edge.right->edges.begin(); E != edge.right->edges.end(); ++E) {
                if (!E->first->color) {
                    Q.insert(Edge(edge.right, E->first, edge.weight + E->second));
                }
            }
        }
        
    }

};

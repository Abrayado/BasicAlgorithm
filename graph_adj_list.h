#ifndef GRAPH_ADJ_LIST
#define GRAPH_ADJ_LIST

#include <vector>
#include <iostream>
#include "graph_adj_list.h"

struct graph_adj_l
{
    graph_adj_l(int);

    int n;
    std::vector<std::vector<int>> l;
        
    void add_edge(int , int);
    void display_graph();
};

#endif
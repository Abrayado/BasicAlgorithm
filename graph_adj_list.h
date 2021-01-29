#ifndef GRAPH_ADJ_LIST
#define GRAPH_ADJ_LIST

#include <vector>
#include <iostream>
#include <tuple>
#include "graph_adj_list.h"

struct graph_unweight_adj_l
{
    graph_unweight_adj_l(int);

    int n;
    std::vector<std::vector<int>> adj_l;
        
    void add_edge(int , int);
    void display_graph();
};

struct graph_weight_adj_l
{
    graph_weight_adj_l(int);

    int n;
    std::vector<std::vector<std::tuple<int, int>>> adj_l;
    std::vector<std::tuple<int, int, int>> edges;
        
    void add_edge(int , int, int);
    void display_graph();
};

#endif
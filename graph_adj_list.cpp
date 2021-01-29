#include "graph_adj_list.h"

graph_unweight_adj_l::graph_unweight_adj_l(int _n)
{
    this->n = _n;
    this->adj_l.resize(this->n);
}

void graph_unweight_adj_l::add_edge(int i, int j)
{
    if (i >= this->n || j >= this->n || i < 0 || j < 0)
    {
        std::cout << "Edge not valid : " << i << " " << j << std::endl;
        return;
    }
    
    this->adj_l[i].push_back(j);
}

void graph_unweight_adj_l::display_graph()
{
    for (int i = 0; i < this->n; i++)
    {
        std::cout << "Node " << i << " -> ";
        for(int x : this->adj_l[i])
        {
            std::cout << x << ", ";
        }
        std::cout << std::endl;
    }
}

graph_weight_adj_l::graph_weight_adj_l(int _n)
{
    this->n = _n;
    this->adj_l.resize(this->n);
}

void graph_weight_adj_l::add_edge(int i, int j, int k)
{
    if (i >= this->n || j >= this->n || i < 0 || j < 0)
    {
        std::cout << "Edge not valid : " << i << " " << j << std::endl;
        return;
    }
    
    this->adj_l[i].push_back(std::make_tuple(j, k));
    this->edges.push_back(std::make_tuple(i, j, k));
}

void graph_weight_adj_l::display_graph()
{
    for (int i = 0; i < this->n; i++)
    {
        std::cout << "Node " << i << " -> ";
        for(std::tuple<int, int> x : this->adj_l[i])
        {
            std::cout << "(" << std::get<0>(x) << ", " << std::get<1>(x) << "), ";
        }
        std::cout << std::endl;
    }
}
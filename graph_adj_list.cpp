#include "graph_adj_list.h"

graph_adj_l::graph_adj_l(int _n)
{
    this->n = _n;
    this->l.resize(this->n);
}

void graph_adj_l::add_edge(int i, int j)
{
    if (i >= this->n || j >= this->n || i < 0 || j < 0)
    {
        std::cout << "Edge not valid : " << i << " " << j << std::endl;
        return;
    }
    
    this->l[i].push_back(j);
    this->l[j].push_back(i);
}

void graph_adj_l::display_graph()
{
    for (int i = 0; i < this->n; i++)
    {
        std::cout << "Node " << i << " -> ";
        for(int x : this->l[i])
        {
            std::cout << x << ", ";
        }
        std::cout << std::endl;
    }
}
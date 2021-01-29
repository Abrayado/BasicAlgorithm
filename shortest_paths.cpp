/*
MIT License

Copyright (c) 2021 LEMERCIER Thomas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits.h>
#include <algorithm>
#include "graph_adj_list.h"

using namespace std;

tuple<vector<int>, vector<int>> dijkstra(graph_weight_adj_l g, int s)
{
    vector<int> parent(g.n, -1);
    vector<int> distance(g.n, INT_MAX);
    priority_queue<pair<int, int>> frontiere;
    vector<bool> process(g.n, false);

    parent[s] = s;
    distance[s] = 0;
    frontiere.push(make_pair(0, s));

    while (!frontiere.empty())
    {
        int x = frontiere.top().second;
        frontiere.pop();

        if (process[x])
        {
            continue;
        }
        else
        {
            process[x] =true;
        }

        for (tuple<int, int> v : g.adj_l[x])
        {
            auto[u, w] = v;
            if (distance[x] + w < distance[u])
            {
                //cout << "current node : " << x << " neigh : " << u << endl;
                distance[u] = distance[x] + w;
                parent[u] = x;
                frontiere.push(make_pair(-distance[u], u));
            }
        }
    }
    return make_tuple(parent, distance);
} /* Time Complexity : O(|E| + |V| * ln(|V|)) with |V| the number of node in the graph and |E| the number of edge */

tuple<vector<int>, vector<int>> bellman_ford(graph_weight_adj_l g, int s)
{
    vector<int> distance(g.n, INT_MAX);
    vector<int> parent(g.n, -1);
    distance[s] = 0;
    parent[s] = s;

    for(int i = 0; i<g.n; i++)
    {
        for(tuple<int, int , int> e : g.edges)
        {
            auto[u, v, w] = e;
            if(distance[u] != INT_MAX && distance[u] + w < distance[v])
            {
                distance[v] = distance[u] + w;
                parent[v] = u;
            }
        }
    }
    for(tuple<int, int , int> e : g.edges)
    {
        auto[u, v, w] = e;
        if(distance[u] != INT_MAX && distance[u] + w < distance[v])
        {
            cout << "Negative cycle detected !" << endl;
        }
    }    
    return make_tuple(parent, distance);
} /* Time Complexity : O(|E| * |V|) with |V| the number of node in the graph and |E| the number of edge */

vector<int> retrieve_path(vector<int> parent, int s, int t)
{
    vector<int> path;
    int next_node = t;
    while(next_node != s)
    {
        path.push_back(next_node); 
        next_node = parent[next_node];
    }
    path.push_back(next_node);

    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int size, nb_edge;
    cin >> size >> nb_edge;

    graph_weight_adj_l G = graph_weight_adj_l(size);

    for (int l = 0; l < nb_edge; l++)
    {
        int i, j, k;
        cin >> i >> j >> k;
        G.add_edge(i, j, k);
    }

    G.display_graph();

    tuple<vector<int>, vector<int>> result = bellman_ford(G, 2);

    auto[parent, distance] = result;

    vector<int> path = retrieve_path(parent, 2, 0);

    for(int x : path)
    {
        cout << x << " -> ";
    }
    cout << endl;
    for(int i =0; i<G.n; i++)
    {
        cout << i << " : " << distance[i] << endl;
    }
    for(int i =0; i<G.n; i++)
    {
        cout << i << " :> " << parent[i] << endl;
    }
    
    return 0;
}
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
#include <stack>
#include <queue>
#include "graph_adj_list.h"

using namespace std;

bool DFS(graph_adj_l g, int s, int t)
{
    vector<bool> visited(g.n, false);
    stack<int> n_next;

    n_next.push(s);
    visited[s] = true;

    while (!n_next.empty())
    {
        int x = n_next.top();
        n_next.pop();

        if(x == t) { return true; }

        for(int v : g.l[x])
        {
            if (visited[v] == false)
            {
                visited[v] =true;
                n_next.push(v);
            }            
        }
    }
    return false;
} /* Complexity : O(|V| + |E|) with |V| the number of node in the graph and |E| the number of edge*/

bool BFS(graph_adj_l g, int s, int t)
{
    vector<bool> visited(g.n, false);
    queue<int> n_next;

    n_next.push(s);
    visited[s] = true;

    while (!n_next.empty())
    {
        int x = n_next.front();
        n_next.pop();

        if(x == t) { return true; }

        for(int v : g.l[x])
        {
            if (visited[v] == false)
            {
                visited[v] =true;
                n_next.push(v);
            }            
        }
    }
    return false;
} /* Complexity : O(|V| + |E|) with |V| the number of node in the graph and |E| the number of edge*/

vector<bool> BFS_connex(graph_adj_l g, int s)
{
    vector<bool> visited(g.n, false);
    queue<int> n_next;

    n_next.push(s);
    visited[s] = true;

    while (!n_next.empty())
    {
        int x = n_next.front();
        n_next.pop();

        for(int v : g.l[x])
        {
            if (visited[v] == false)
            {
                visited[v] =true;
                n_next.push(v);
            }            
        }
    }
    return visited;
}

vector<vector<bool>> get_components(graph_adj_l g)
{
    vector<vector<bool>> components;
    vector<bool> visited(g.n, false);
    for (int node = 0; node < g.n; node++)
    {
        if(!visited[node])
        {
            vector<bool> component = BFS_connex(g, node);
            for(int k = 0; k < g.n; k++)
            {
                visited[k] = visited[k] || component[k];
            }
            components.push_back(component);
        }
    }
    return components;
} /* Complexity : O(|E|) with |E| the number of edge*/

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int size, nb_edge;
    cin >> size >> nb_edge;

    graph_adj_l G = graph_adj_l(size);

    for (int k = 0; k < nb_edge; k++)
    {
        int i, j;
        cin >> i >> j;
        G.add_edge(i, j);

    }

    G.display_graph();
    vector<vector<bool>> comps = get_components(G);

    for(vector<bool> comp : comps)
    {
        for(bool x : comp)
        {
            cout << x << ", ";
        }
        cout << endl;
    }
    return 0;
}
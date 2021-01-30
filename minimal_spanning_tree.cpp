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
#include <tuple>
#include <queue>
#include <algorithm>
#include "graph_adj_list.h"

using namespace std;

bool compare_edge(const tuple<int, int, int> &x, const tuple<int, int, int> &y)
{
    return (get<2>(x) < get<2>(y));
}

int u_find(int x ,const vector<int>& links)
{
    while (x != links[x])
    {
        x = links[x];
    }
    return x;
}

void u_union(int u, int v, vector<int>& links, vector<int>& size)
{
    u = u_find(u, links);
    v = u_find(v, links);
    if(size[v] > size[u]) {swap(u, v);}
    links[v] = u;
    size[u] += size[v];    
}



vector<tuple<int,int>> kruskal_mst(graph_weight_adj_l g)
{

    vector<tuple<int, int>> chosen_edges;
    vector<tuple<int,int, int>> edges = g.edges;
    sort(edges.begin(), edges.end(), compare_edge);

    vector<int> links(g.n);
    vector<int> size(g.n);

    for(int i = 0; i < g.n; i++) {links[i] = i;}


    int cnt = 0;
    for(tuple<int, int, int> edge: edges)
    {
        auto[u, v, k] = edge;
        if(u_find(u, links) != u_find(v, links))
        {
            u_union(u, v, links, size);
            cnt += 1;
            chosen_edges.push_back(make_tuple(u, v));
        }
        if(cnt == g.n -1) {break;}
    }
    

    return chosen_edges;
}/* Time Complexity : O(|E| * ln(|E|)) with |E| the number of edge */

vector<tuple<int,int>> prim_mst(graph_weight_adj_l g)
{
    vector<int> parent(g.n, -1);
    priority_queue<tuple<int, int>> frontiere;
    vector<bool> proceed(g.n, false);
    vector<int> distance(g.n, INT_MAX);

    frontiere.push(make_tuple(0,0));
    parent[0] = 0;
    distance[0] = 0;

    while(!frontiere.empty())
    {
        auto[d, x] = frontiere.top(); frontiere.pop();
        if(proceed[x] == true) { continue; }
        proceed[x] = true;

        for(tuple<int, int> e : g.adj_l[x])
        {
            auto[v, w] = e;
            if(!proceed[v] && w < distance[v])
            {
                frontiere.push(make_tuple(-w, v));
                parent[v] = x;
                distance[v] = w;
            }
        }
    }
    
    vector<tuple<int, int>> chosen_edges;
    for (int i = 1; i < g.n; i++)
    {
        chosen_edges.push_back(make_tuple(parent[i], i));
    }
    return chosen_edges;
}/* Time Complexity : O(|E| + |V| * log |V|)}) with |V| the number of node and |E| the number of edge */

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

    vector<tuple<int, int>> min_s_tree = kruskal_mst(G);

    int value = 0;

    for (tuple<int, int> edge : min_s_tree)
    {
        auto[u, v] = edge;
        cout << u << " - " << v << endl;
        for(tuple<int, int> x : G.adj_l[u])
        {
            if(get<0>(x) == v)
            {
                value += get<1>(x);
                break;
            }

        }
    }
    cout << "Val : " << value;
    

    return 0;
}
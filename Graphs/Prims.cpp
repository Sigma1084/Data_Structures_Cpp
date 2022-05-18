//
// Created by Sig on 18-05-2022.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1000000007;
#define V vector
typedef V<int> vi;
typedef V<bool> vb;
typedef V<vi> vvi;
typedef pair<int, int> pii;


// Prints the Adjacency List (Takes O(m+n))
void printAdjacencyList(vvi adj) {
    cout << "\n";
    for (int i=0; i<adj.size(); i++) {
        cout << i << ": ";
        for (int j=0; j<adj[i].size(); j++)
            cout << adj[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

// Sorts the Adjacency List. Takes about O(m logm)
void sortAdjacencyList(vvi &adj) {
    for (vi list: adj)
        sort(list.begin(), list.end());
}


int main() {
    // Graph Setup

    int n = 5;
    int m = 8;  // In an undirected manner
    vvi edges(n);
    vvi weights(n);

    // Adds a directed edge from u to v
    auto addEdge = [&](int u, int v, int weight=0) -> void {
        edges[u].push_back(v);
        edges[v].push_back(u);
        weights[u].push_back(weight);
        weights[v].push_back(weight);
    };

    // A Block to add all the edges to m
    {
        vector<pair<int, int>> tempEdges = {{0, 1}, {1, 2}, {1, 3}, {3, 0},
                                            {3, 2}, {3, 4}, {4, 0}, {4, 2}};
        vi wts = {10, 7, 2, 8, 5, 1, 4, 3};
        for (int i=0; i<m; i++)
            addEdge(tempEdges[i].first, tempEdges[i].second, wts[i]);
    }

    // Code Here

    // It is assumed that the graph is connected
    // The Graph is undirected

    V<pii> spanEdges;
    vb visited(n, false);
    int minWeight = -1;
    auto prims = [&](int start=0) -> void {
        // Redefinition
        spanEdges.clear();
        visited.assign(n, false);
        minWeight = 0;

        int spanVerts = 1;
        priority_queue<pair<int, pii>, V<pair<int, pii>>, greater<pair<int, pii>>> neighbours;

        visited[start] = true;
        for (int i=0; i<edges[start].size(); i++)
            neighbours.push({weights[start][i], {start, edges[start][i]}});

        int d, u, v;
        while(!neighbours.empty() && spanVerts < n) {
            auto e = neighbours.top(); neighbours.pop();
            if (visited[e.second.second]) continue;
            d = e.first;  // The distance of the edge
            u = e.second.first;  // The index of the starting point of the edge
            v = e.second.second;  // The index of the ending point of thr edge
            visited[v] = true;
            spanEdges.push_back({u, v});
            minWeight += d;
            for (int i=0; i<edges[v].size(); i++) if (!visited[edges[v][i]])
                neighbours.push({weights[v][i], {v, edges[v][i]}});
        }
    };

    prims();

    // Sample Check

    cout << minWeight << '\n';
    for (auto e: spanEdges)
        cout << e.first << ' ' << e.second << "  ";
    cout << '\n';

    return 0;
}

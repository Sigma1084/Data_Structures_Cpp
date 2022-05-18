//
// Created by Sig on 28-04-2022.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stack>
using namespace std;

#define INF 1000000007
#define vi vector<int>
#define vvi vector<vi>


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
    int m = 8;
    vvi edgesFrom(n);
    vvi edgesInto(n);

    // Adds a directed edge from u to v
    auto addEdge = [&](int u, int v) -> void {
        edgesFrom[u].push_back(v);
        edgesInto[v].push_back(u);
    };

    // A Block to add all the edges to m
    {
        vector<pair<int, int>> tempEdges = {{0, 1}, {1, 2}, {1, 3}, {3, 0},
                                            {3, 2}, {3, 4}, {4, 0}, {4, 2}};
        for (auto tempEdge: tempEdges)
            addEdge(tempEdge.first, tempEdge.second);
    }

    // Code Here

    vi p(n, -1);  // p[v] gives the parent of v in the DFS Tree
    auto dfs = [&](int start, int end=-1) -> void {
        p[start] = start;
        bool ret = false;
        auto inner = [&](auto &&inner, int u) -> void {
            if(ret) return;
            for (int v: edgesFrom[u]) {
                if (p[v] == -1) {
                    p[v] = u;
                    inner(inner, v);
                    if (v == end) ret = true;
                }
                if (ret) return;
            }
        };
        inner(inner, start);
    };

    // Example
    int start = 1;
    dfs(start);
    for (int pi: p)
        cout << pi << " ";
    cout << "\n";

    return 0;
}

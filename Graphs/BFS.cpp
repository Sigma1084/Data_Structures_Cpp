//
// Created by Sig on 28-04-2022.
//


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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
    vi d(n, INF);  // d(v) is the distance of v from s
    vi p(n);  // p(v) gives the parent of v in the BFS Tree
    auto bfs = [&](int start, int end=-1) {
        queue<int> Q;
        Q.push(start);
        d[start] = 0;
        for (int i=0; i<p.size(); i++)
            p[i] = i;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int v: edgesFrom[u]) {
                if (d[v] != INF) continue;  // v has already been traversed
                d[v] = d[u] + 1;
                p[v] = u;
                Q.push(v);
                if (v == end) return;  // We have reached our end
            }
        }
    };


    // Example

    bfs(3);

    for (auto di: d)
        cout << di << " ";
    cout << "\n";
    for (int pi: p)
        cout << pi << " ";
    cout << "\n";

    return 0;
}

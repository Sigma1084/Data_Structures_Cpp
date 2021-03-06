//
// Created by Sig on 28-04-2022.
//

#include <iostream>
#include <vector>
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
    int m = 8;
    vvi edgesFrom(n);
    vvi edgesInto(n);

    vvi weightsFrom(n);
    vvi weightsInto(n);

    // Adds a directed edge from u to v
    auto addEdge = [&](int u, int v, int weight=0) -> void {
        edgesFrom[u].push_back(v);
        edgesInto[v].push_back(u);
        weightsFrom[u].push_back(weight);
        weightsInto[v].push_back(weight);
    };

    // A Block to add all the edges to m
    {
        vector<pair<int, int>> tempEdges = {{0, 1}, {1, 2}, {1, 3}, {3, 0},
                                 {3, 2}, {3, 4}, {4, 0}, {4, 2}};
        vi weights = {10, 7, 2, 8, 5, 1, 4, 3};
        for (int i=0; i<m; i++)
            addEdge(tempEdges[i].first, tempEdges[i].second, weights[i]);
    }

    // Code Here


    return 0;
}

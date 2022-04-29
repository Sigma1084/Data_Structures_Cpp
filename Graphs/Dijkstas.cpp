//
// Created by Sig on 29-04-2022.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 1000000007
#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int, int>

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

// Heap
template <class T>
struct MinHeap {
    T *heap;
    int heapSize;
    int arraySize;
    bool compare(T a, T b) { return a < b; }

    static int getLeft(int index) { return 2*index + 1; }
    static int getRight(int index) { return 2*index + 2; }
    static int getParent(int index) { return (index-1) / 2; }

    bool empty() const { return heapSize == 0; }
    bool hasLeft(int index) const { return getLeft(index) < heapSize; }
    bool hasRight(int index) const { return getRight(index) < heapSize; }
    void swap(int i, int j) { T temp = heap[i]; heap[i] = heap[j]; heap[j] = temp; }
    void print() { for (int i=0; i<heapSize; i++) cout << heap[i] << "\n"; }

    void push(T data) { if(heapSize == arraySize) return; heap[heapSize] = data; heapifyUp(heapSize++); }
    T peek() { return heap[0]; }
    T pop(int index=0) { T retInt = heap[index]; heap[index] = heap[--heapSize]; heapifyDown(index); return retInt; }

    MinHeap(int size) { arraySize = size; heap = new T[size]; heapSize = 0; }
    ~MinHeap() { delete [] heap; }

    void heapifyUp(int index) {
        if (index == 0)
            return;
        int parent = getParent(index);
        if (compare(heap[index], heap[parent])) {
            swap(parent, index);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index=0) {
        if (index >= heapSize)
            return;

        int left = getLeft(index);
        int right = getRight(index);
        int maxEle = index;

        if (hasLeft(index) && compare(heap[left], heap[maxEle]))
            maxEle = left;
        if (hasRight(index) && compare(heap[right], heap[maxEle]))
            maxEle = right;
        if (maxEle != index) {
            swap(index, maxEle);
            heapifyDown(maxEle);
        }
    }
};

// Triple
struct triple {
    int first, second, third;
    triple(int a=0, int b=0, int c=0): first(a), second(b), third(c) {};
    triple(triple const &t): first(t.first), second(t.second), third(t.third) {};
    bool operator < (triple const &other) {if (this->first < other.first) return true; return false; }
    bool operator > (triple const &other) {if (this->first > other.first) return true; return false; }
    friend std::ostream& operator << (ostream &outFunc, const triple& t) {
        outFunc << t.first << " " << t.second << " " << t.third; return outFunc; }
};

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
    vi parent(n, -1);  // Parent of the vertex in the min distance path
    vi dist(n, INF);  // Distance from start vertex after the end of the algorithm

    auto dijkstra = [&](int start) {
        parent[start] = start;

        /*
         * triple here signifies 3 things
         * second: The starting edge
         * third: The ending edge
         * first: d[starting edge] + weight of the edge
         *
         * MinHeap on first to keep track of the edge with the least distance
         */
        MinHeap<triple> heap(n);

        heap.push({0, start, start});
        while (!heap.empty()) {
            triple edgeInfo = heap.pop();

            int distance = edgeInfo.first;
            int u = edgeInfo.second;
            int v = edgeInfo.third;

            if (dist[v] != INF)
                continue;

            parent[v] = u;
            dist[v] = distance;

            for (int i=0; i<edgesFrom[v].size(); i++) {
                if (dist[edgesFrom[v][i]] == INF)
                    heap.push({distance + weightsFrom[v][i], v, edgesFrom[v][i]});
            }
        }
    };

    // Testing
    dijkstra(3);

    cout << "Distances: ";
    for (int i=0; i<n; i++)
        cout << dist[i] << " ";
    cout << "\n";

    cout << "Parents: ";
    for (int i=0; i<n; i++)
        cout << parent[i] << " ";
    cout << "\n";

    return 0;
}

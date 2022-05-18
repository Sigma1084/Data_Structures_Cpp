# Graph Algorithms


## Initial Setup
```cpp
// Defining the notion of Infinity
#define INF 1000000007

// For simplicity and will be used throughout
#define vi vector<int>
#define vvi vector<vi>

/*
 * @brief Adds an edge from u to v
 * @param {int} u: Starting vertex of the edge
 * @param {int} v: Ending vertex of the edge
 */
void addEdge(int u, int v);
```


## Notation
```cpp
// Standard Notation of a directed graph is followed

int n; // Number of Vertices
int m;  // Number of Edges (in a directed environment)

// If m is the number of edges in an undirected graph,
//     2m will be the number of edges in the graph considered

// Assumption: vertices are ordered 0 to n-1

// edgesFrom[i] gives the list of all edges coming out of vertex i
vii edgesFrom(n);

// edgesInto[i] gives the list of all edges going to vertex i
vii edgesInto(n);
```

An example of a Sample Graph can be found in [SampleGraph.cpp](SampleGraph.cpp)

```mermaid
graph LR
A((V0)) -- 10 --> B((V1))
D((V3)) -- 8 --> A
B -- 7 --> C((V2))
D -- 5 --> C
B -- 2 --> D
D -- 1 --> E((V4))
E -- 4 --> A
E -- 3 --> C
```


## BFS
```cpp
/*
 * @brief Finds whether a node can be reached from the start node
 * 
 * @param {int} start: The starting point of BFS;
 * @param {int} end [Optional] [Default = -1]: Terminates if end is reached
 * 
 * After execution
 * d[v] = INF if v can't be reached from start
 * d[v]: Minimum distance of v from u
 * 
 * p[v] = v IF v = start
 * p[v] = u implies u is the parent of u in the shortest path from start to v
 * p[v] = -1 if v can't be reached from start
 */
void bfs(int start, int end=-1);
```

```cpp
vi d(n, INF);  // d[v] is the distance of v from s
vi p(n, -1);  // p[v] gives the parent of v in the graph

auto bfs = [&](int start, int end=-1) -> void { ... }  // Function Definition

bfs(start);

// d and p are now updated after calling bfs and can be accessed
```

## DFS
```cpp
/*
 * @brief Finds whether a node can be reached from the start node
 *
 * @param {int} start: The starting point of BFS;
 * @param {int} end [Optional] [Default = -1]: Terminates if end is reached
 *
 * After execution
 * d[v]: Minimum distance of v from u
 *
 * p[v] = v IF v = start
 * p[v] = u implies u is the parent of u in the shortest path from start to v
 * p[v] = -1 if v can't be reached from start
 */
void dfs(int start, int end=-1);
```

```cpp
vi p(n, -1);  // p[v] gives the parent of v in the DFS Tree

auto dfs = [&](int start, int end=-1) -> void { ... }  // Function definition

dfs(start);
```


## Kruskal's Algorithm (Minimum Spanning Tree)


## Prim's Algorithm (Minimum Spanning Tree)
```cpp
/*
 * @brief Calculates the minimum spanning tree using Prim's algorithm
 *
 * @param {int} start: The starting point of BFS;
 * @param {int} end [Optional] [Default = -1]: Terminates if end is reached
 *
 * After execution
 * d[v]: Minimum distance of v from u
 *
 * p[v] = v IF v = start
 * p[v] = u implies u is the parent of u in the shortest path from start to v
 * p[v] = -1 if v can't be reached from start
 */
void prims(int start=0);
```

```cpp
vector<pair<int, int>> spanEdges;  // In the end gives the edges of Spanning Tree
vector<bool> visited(n, false);  // Default to false
int minWeight = -1;

auto prims = [&](int start=0) -> void { ... }

prims();
```

## Dijkstra's Algorithm
```cpp
/* 
 * @brief: Finds the Shortest Path from a given vertex "start" 
 *  to all the other vertices in a weighted graph. 
 *  
 * (Single Source Shortest Path)
 * 
 * @param {int} start: The starting point;
 * 
 * After execution
 * d[v] = INF if v can't be reached from start
 * d[v]: Minimum distance of v from u
 * 
 * p[v] = v IF v = start
 * p[v] = -1 IF v can't be reached from start
 * p[v] = u implies u is the parent of u in
 *        the shortest distance path from start to v
 */
void dijkstra(int start);
```

```cpp
vi dist(n, INF);  // Distance from start vertex after the end of the algorithm
vi parent(n, -1);  // Parent of the vertex in the min distance path

auto dijkstra = [&](int start) -> void { ... };

bfs(start);

// dist and parent are now updated after calling dijkstra and can be accessed
```

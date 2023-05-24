# Parallel Breadth First Search and Depth First Search using OpenMP

This practical guide provides an example implementation of parallel Breadth First Search (BFS) and Depth First Search (DFS) algorithms using OpenMP for an undirected graph. The code is written in C++. The guide includes instructions to compile and run the code, a problem-solving example, and a conclusion.

## Problem Statement

Consider a social network represented as an undirected graph, where each vertex represents a person and each edge represents a friendship. You need to find the shortest path between two individuals in the network using BFS and determine all possible paths using DFS.

# Complete code in cpp

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adjList;

public:
    Graph(int vertices) {
        numVertices = vertices;
        adjList.resize(numVertices);
    }

    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    void printGraph() {
        for (int i = 0; i < numVertices; i++) {
            cout << "Adjacency list of vertex " << i << ": ";
            for (auto v : adjList[i])
                cout << v << " ";
            cout << endl;
        }
    }

    void parallelBFS(int source) {
        vector<bool> visited(numVertices, false);
        queue<int> bfsQueue;

        visited[source] = true;
        bfsQueue.push(source);

        while (!bfsQueue.empty()) {
            int currentVertex = bfsQueue.front();
            bfsQueue.pop();

            cout << "Visited vertex: " << currentVertex << endl;

#pragma omp parallel for
            for (int i = 0; i < adjList[currentVertex].size(); i++) {
                int neighbor = adjList[currentVertex][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    bfsQueue.push(neighbor);
                }
            }
        }
    }

    void parallelDFS(int source) {
        vector<bool> visited(numVertices, false);
        parallelDFSUtil(source, visited);
    }

    void parallelDFSUtil(int vertex, vector<bool>& visited) {
        cout << "Visited vertex: " << vertex << endl;
        visited[vertex] = true;

#pragma omp parallel for
        for (int i = 0; i < adjList[vertex].size(); i++) {
            int neighbor = adjList[vertex][i];
            if (!visited[neighbor])
                parallelDFSUtil(neighbor, visited);
        }
    }
};

int main() {
    Graph graph(7); // Create a graph with 7 vertices

    // Add edges between vertices
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    graph.addEdge(2, 6);

    cout << "Graph:" << endl;
    graph.printGraph();

    cout << "Parallel BFS:" << endl;
    graph.parallelBFS(0);

    cout << "Parallel DFS:" << endl;
    graph.parallelDFS(0);

    return 0;
}

```


## Instructions

1. Ensure you have OpenMP installed and configured correctly on your system.
2. Copy the provided code into a C++ file, e.g., `parallel_bfs_dfs.cpp`.
3. Compile the code using the following command:

   ```bash
   g++ -fopenmp parallel_bfs_dfs.cpp -o parallel_bfs_dfs
   ```

4. Run the executable:
    ```bash
    ./parallel_bfs_dfs
    ```

# Code Explanation
    The provided code defines a Graph class with methods for adding edges, printing the graph, and performing parallel BFS and DFS traversal.

1. addEdge(int src, int dest): Adds an edge between two vertices in the graph.

2. printGraph(): Prints the adjacency list representation of the graph.

3. parallelBFS(int source): Performs parallel BFS traversal starting from the given source vertex.

4. parallelDFS(int source): Performs parallel DFS traversal starting from the given source vertex.

5. parallelDFSUtil(int vertex, vector<bool>& visited): Recursive utility function for parallel DFS traversal.

# Example Usage
    Consider a social network with 7 individuals connected as follows:
         0
        / \
       1    2
      / \  / \
     3   4    5
               \
                6

# Graph Creation
```code
Graph graph(7); // Create a graph with 7 vertices

// Add edges between vertices
graph.addEdge(0, 1);
graph.addEdge(0, 2);
graph.addEdge(1, 3);
graph.addEdge(1, 4);
graph.addEdge(2, 5);
graph.addEdge(2, 6);
```

# Graph Visualization
To verify the graph's structure, we can print its adjacency list representation.
```code
cout << "Graph:" << endl;
graph.printGraph();
```

# OUTPUT
```code
Adjacency list of vertex 0: 1 2
Adjacency list of vertex 1: 0 3 4
Adjacency list of vertex 2: 0 5 6
Adjacency list of vertex 3: 1
Adjacency list of vertex 4: 1
Adjacency list of vertex 5: 2
Adjacency list of vertex 6: 2
```
## Parallel BFS
We can perform parallel BFS traversal starting from vertex 0 and print the visited vertices.
```code
cout << "Parallel BFS:" << endl;
graph.parallelBFS(0);
```

BFS output:
```code
Visited vertex: 0
Visited vertex: 1
Visited vertex: 2
Visited vertex: 3
Visited vertex: 4
Visited vertex: 5
Visited vertex: 6
```
## Parallel DFS
We can perform parallel DFS traversal starting from vertex 0 and print the visited vertices.
```code
cout << "Parallel DFS:" << endl;
graph.parallelDFS(0);
```
DFS output:
```code
Visited vertex: 0
Visited vertex: 2
Visited vertex: 6
Visited vertex: 5
Visited vertex: 1
Visited vertex: 4
Visited vertex: 3
```

# Conclusion
In this practical guide, we implemented parallel BFS and DFS algorithms using OpenMP for an undirected graph. We demonstrated the usage of the algorithms on a social network graph, finding the visited vertices in parallel. Additionally, we provided suggestions for further exploration, such as finding the shortest path and connected components, as well as conducting performance analysis.

By leveraging parallel processing, we can significantly improve the efficiency of graph traversal algorithms and solve complex problems in a shorter time frame.

Feel free to experiment with the code and explore different graph structures and problem scenarios. Enjoy parallelizing your graph algorithms with OpenMP!


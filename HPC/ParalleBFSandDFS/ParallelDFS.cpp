#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

// Function to add an edge between two vertices
void addEdge(vector<int>* adjList, int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

// Parallel Depth First Search
void parallelDFS(vector<int>* adjList, int v, vector<bool>& visited) {
    stack<int> stack;

    // Start DFS with vertex v
    #pragma omp parallel
    {
        #pragma omp single
        {
            stack.push(v);
            visited[v] = true;
        }

        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();

            #pragma omp for
            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    #pragma omp critical
                    {
                        stack.push(neighbor);
                        visited[neighbor] = true;
                    }
                }
            }
        }
    }
}

int main() {
    int numVertices = 6;
    vector<int> adjList[numVertices];
    vector<bool> visited(numVertices, false);

    // Add edges
    addEdge(adjList, 0, 1);
    addEdge(adjList, 0, 2);
    addEdge(adjList, 1, 3);
    addEdge(adjList, 1, 4);
    addEdge(adjList, 2, 4);
    addEdge(adjList, 3, 4);
    addEdge(adjList, 3, 5);

    // Perform parallel DFS
    parallelDFS(adjList, 0, visited);

    // Print visited vertices
    for (int i = 0; i < numVertices; i++) {
        if (visited[i]) {
            cout << "Vertex " << i << " is visited." << endl;
        }
    }

    return 0;
}

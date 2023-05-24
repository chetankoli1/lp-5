#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph
{
private:
    int numVertices;
    vector<vector<int>> adjList;

public:
    Graph(int vertices)
    {
        numVertices = vertices;
        adjList.resize(numVertices);
    }

    void addEdge(int src, int dest)
    {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    void printGraph()
    {
        for (int i = 0; i < numVertices; i++)
        {
            cout << "Adjacency list of vertex " << i << ": ";
            for (auto v : adjList[i])
                cout << v << " ";
            cout << endl;
        }
    }

    void parallelBFS(int source)
    {
        vector<bool> visited(numVertices, false);
        queue<int> bfsQueue;

        visited[source] = true;
        bfsQueue.push(source);

        while (!bfsQueue.empty())
        {
            int currentVertex = bfsQueue.front();
            bfsQueue.pop();

            cout << "Visited vertex: " << currentVertex << endl;

#pragma omp parallel for
            for (int i = 0; i < adjList[currentVertex].size(); i++)
            {
                int neighbor = adjList[currentVertex][i];
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    bfsQueue.push(neighbor);
                }
            }
        }
    }

    void parallelDFS(int source)
    {
        vector<bool> visited(numVertices, false);
        parallelDFSUtil(source, visited);
    }

    void parallelDFSUtil(int vertex, vector<bool> &visited)
    {
        cout << "Visited vertex: " << vertex << endl;
        visited[vertex] = true;

#pragma omp parallel for
        for (int i = 0; i < adjList[vertex].size(); i++)
        {
            int neighbor = adjList[vertex][i];
            if (!visited[neighbor])
                parallelDFSUtil(neighbor, visited);
        }
    }
};

int main()
{
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

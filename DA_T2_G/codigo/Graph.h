#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <climits>

#define INF (INT_MAX/2)
using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        int cap;
        int horas;
        int flux;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    };
    bool hasDir;        // false: undirect; true: directed
    int n;

public:
    vector<Node> nodes; // The list of nodes being represented
    // Constructor: nr nodes and direction (default: undirected)
    explicit Graph(int num = 0, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int capacidade, int horas);

    int getNumNodes();
    static bool bfs2(vector<vector<int>>& gf , int s, int t,  vector<int>& parent,int size);
    void clear(int nodesNum, bool dir = false);
    bool EdgeExists(int start,int end);
    void printgraph1();
    void printgraph2();
};

#endif

#include "../include/Graph.h"

Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

void Graph::addEdge(int src, int dest, int capacity, int hours) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, capacity,hours});
    if (!hasDir) nodes[dest].adj.push_back({src, capacity,hours});
}

void Graph::dfs(int v) {
    nodes[v].visited=true;
    for(auto edge : nodes[v].adj){
        if(!nodes[edge.dest].visited){
            dfs(edge.dest);
        }
    }
}

void Graph::bfs(int v) {
    queue<int> q;
    q.push(v);
    nodes[v].visited = true;
    while(q.size() > 0){
        int u = q.front();
        q.pop();
        for(auto e: nodes[u] .adj){
            int w = e.dest;
            if(!nodes[w].visited){
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}


int Graph::getNumNodes() {
    return n;
}

void Graph::clear(int nodesNum, bool dir) {
    n = nodesNum;
    hasDir = dir;
    nodes.resize(nodesNum + 1);
    nodes.clear();
    nodes[nodesNum + 1];
}



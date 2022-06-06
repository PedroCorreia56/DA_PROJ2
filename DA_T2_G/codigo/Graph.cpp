#include "../codigo/Graph.h"

Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}



void Graph::addEdge(int src, int dest, int capacity, int hours) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, capacity,hours,0});
    if (!hasDir) nodes[dest].adj.push_back({src, capacity,hours,0});
}


bool Graph::bfs2(vector<vector<int>>& gf , int s, int t,  vector<int>& parent,int size)
{
    // Create a visited array and mark all vertices as not
    // visited
    bool visited[size];
    for (int i = 0; i <size ; i++) {
        visited[i]=false;
    }

    // Create a queue, enqueue source vertex and mark source
    // vertex as visited
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 1; v < size; v++) {
            if (visited[v] == false && gf[u][v] > 0) {
                // If we find a connection to the sink node,
                // then there is no point in BFS anymore We
                // just have to set its parent and can return
                // true
               if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // We didn't reach sink in BFS starting from source, so
    // return false
    return (visited[t]==true);
}

bool Graph::bfs3(vector<vector<int>>& gf , int s, int t,  vector<int>& parent,int size)
{
    // Create a visited array and mark all vertices as not
    // visited
    bool visited[size];
    for (int i = 0; i <size ; i++) {
        visited[i]=false;
    }

    // Create a queue, enqueue source vertex and mark source
    // vertex as visited
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 1; v < size; v++) {
            if (visited[v] == false && gf[u][v] > 0) {
                // If we find a connection to the sink node,
                // then there is no point in BFS anymore We
                // just have to set its parent and can return
                // true
                if (v == t) {
                    parent[v] = u;

                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // We didn't reach sink in BFS starting from source, so
    // return false
    return (visited[t]==true);
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





//!Prints Graph before changing the flux
void Graph::printgraph1() {
    cout<<"ARESTA\t\tFLUXO/CAPACIDADE"<<endl;
    for (int i = 1; i <=this->getNumNodes() ; i++){
        for (auto e : this->nodes[i].adj) {
                cout<<i<<":";
                cout<<"-->"<<e.dest<<"\t\t"<<e.flux<<"/"<<e.cap;
                cout<<endl;
        }
    }
}

//!Prints Graph After Changing the flux
void Graph::printgraph2() {
    cout<<"ARESTA\t\tFLUXO/CAPACIDADE"<<endl;
    for (int i = 1; i <=this->getNumNodes() ; i++){
        for (auto e : this->nodes[i].adj) {
                if(e.flux>0){
                    cout<<i<<":";
                    cout<<"-->"<<e.dest<<"\t\t"<<e.flux<<"/"<<e.cap;
                    cout<<endl;
                }
        }
    }
}

void Graph::printgraph3() {
    cout<<"ARESTA\t\tFLUXO/CAPACIDADE/Horas"<<endl;
    for (int i = 1; i <=this->getNumNodes() ; i++){
        for (auto e : this->nodes[i].adj) {
            if(e.flux>0){
                cout<<i<<":";
                cout<<"-->"<<e.dest<<"\t\t"<<e.flux<<"/"<<e.cap<<"/"<<e.horas;
                cout<<endl;
            }
        }
    }
}
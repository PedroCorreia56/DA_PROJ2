//
// Created by pedro on 24/05/2022.
//

#ifndef DA_T2_G_GRAFO_H
#define DA_T2_G_GRAFO_H

#include <iostream>
#include <list>

using namespace std;

// Classe que representa um no
class Node {
public:
    list<int> adj;  // Lista de adjacencias
    bool visited;   // Valor booleano que indica se foi visitado numa pesquisa
    int distance;   // Distancia ao no origem da pesquisa

    Node() {        // Nao e preciso mais nada porque adj ja foi criada
    };              // mas queria mostrar que em C++ tambem existem construtores
};

// Classe que representa um grafo
class Graph {
public:
    int n;          // Numero de nos do grafo
    Node *nodes;    // Array para conter os nos

    Graph(int n) {
        this->n = n;
        nodes = new Node[n+1];  // +1 se os comecam em 1 ao inves de 0
    }

    void addLink(int a, int b) {
        nodes[a].adj.push_back(b);
        nodes[b].adj.push_back(a);
    }

    void bfs(int v) {
        list<int> q;
        for (int i=1; i<=n; i++) nodes[i].visited = false;

        q.push_back(v);
        nodes[v].visited = true;
        nodes[v].distance = 0;

        while (q.size() > 0) {
            int u = q.front(); q.pop_front();
            cout << u << " [dist=" << nodes[u].distance << "]" << endl;
            for (auto w : nodes[u].adj)
                if (!nodes[w].visited) {
                    q.push_back(w);
                    nodes[w].visited  = true;
                    nodes[w].distance = nodes[u].distance + 1;
                }
        }
    }
};
#endif //DA_T2_G_GRAFO_H

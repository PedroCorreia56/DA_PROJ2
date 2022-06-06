#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <climits>

#define INF (INT_MAX/2)
using namespace std;
//!Cria um Grafo
class Graph {
    //! Aresta do Grafo
    struct Edge {
        //! Vértice de Destino
        int dest;
        //!Capacidade da aresta
        int cap;
        //! Duração da Aresta
        int horas;
        //!Fluxo da aresta
        int flux;
    };
    //!Vértice do grafo
    struct Node {
        //! A lista de arestas que saem do nó
        list<Edge> adj;
    };
    //! false: undirect; true: directed
    bool hasDir;
    //!Número de vértices
    int n;

public:
    //!A lista dos nós representados
    vector<Node> nodes;
    //! Constructor: nr nodes and direction (default: undirected)
    explicit Graph(int num = 0, bool dir = false);

    //! Cria uma aresta de src para dest com capacidade e horas dadas e com fluxo=0
    //! \param src - nó de origem
    //! \param dest - nó destino
    //! \param capacidade - capacacidade aresta
    //! \param horas - duração aresta
    void addEdge(int src, int dest, int capacidade, int horas);
    //! Devolve o número de nós do Grafo
    //! \return - número nós grafo
    int getNumNodes();

    //! Descobre se existe caminho do vértice de origem até ao vértice destino
    //! \param gf - grafo com os caminhos disponíveis
    //! \param s - vértice de origem
    //! \param t - vértice de destino
    //! \param parent - vetor que guarda o caminho usado
    //! \param size - número de nós do grafo
    //! \return true - existir caminho
    static bool bfs2(vector<vector<int>>& gf , int s, int t,  vector<int>& parent,int size);


    void clear(int nodesNum, bool dir = false);

    //!Print ao grafo com arestas com fluxo=0 e a sua capacidade
    void printgraph1();
    //!Print ao grafo com arestas com fluxo>0 e a sua capacidade
    void printgraph2();
    //! Print ao grafo com arestas com fluxo>0,a sua capacidade e a sua duração
    void printgraph3();
};

#endif

//
// Created by pedro on 28/05/2022.
//

#ifndef DA_T2_G_CENARIO2_H
#define DA_T2_G_CENARIO2_H
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "Graph.h"
#include "MaxHeap.h"
#include "cenario1.h"

using namespace std;

int MaxFlux(Graph graph,int start, int end){

    vector<vector<int>>gf( graph.getNumNodes()+1 , vector<int> (graph.getNumNodes()+1,0));

    cout<<"INITIAL:\n";
    cout<<"ARESTA\t\tFLUXO/CAPACIDADE"<<endl;


    for (int i = 1; i <=graph.getNumNodes() ; i++){
        for (auto e : graph.nodes[i].adj) {
    //        cout<<i<<":";
            gf[i][e.dest]=e.cap;
      //      cout<<"-->"<<e.dest<<"\t\t"<<e.flux<<"/"<<e.cap;
            cout<<endl;
        }
    }
    vector<int> parent(graph.getNumNodes()+1, 0);

    int v,u;
    int max_flow = 0;
    int used_flow=0;
    while (Graph::bfs2(gf,start,end,parent,graph.getNumNodes()+1)) {

        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = INT_MAX;
        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            //  cout<<v<<"<--";
            path_flow = min(path_flow, gf[u][v]);
        }

        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            //cout<<"BEFORE:"<<u<<"-->"<<v<<":"<<gf[u][v]<<endl;
            gf[u][v] -= path_flow;
            //cout<<"After:"<<u<<"-->"<<v<<":"<<gf[u][v]<<endl;
            gf[v][u] += path_flow;
        }
        max_flow += path_flow;
    }

    // FILL FLUX
    for (int i = 1; i <=graph.getNumNodes() ; i++){
        for (auto & e : graph.nodes[i].adj) {
            e.flux+=(e.cap-gf[i][e.dest]);
        }
    }
    cout<<"\nFINAL:\n";
    graph.printgraph2();
    cout<<"MAX FLOW:"<<max_flow<<endl;
    return max_flow;
}


int FindPath(Graph graph,int start,int end, int capacity){

    vector<vector<int>>gf( graph.getNumNodes()+1 , vector<int> (graph.getNumNodes()+1,0));

    cout<<"INITIAL:\n";
    graph.printgraph1();
    for (int i = 1; i <=graph.getNumNodes() ; i++){
        for (auto e : graph.nodes[i].adj) {
            gf[i][e.dest]=e.cap;
        }
    }
    vector<int> parent(graph.getNumNodes()+1, 0);


    int v,u;
    int max_flow = 0;
    int used_flow=0;
    while (Graph::bfs2(gf,start,end,parent,graph.getNumNodes()+1)) {
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = INT_MAX;
        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
          //  cout<<v<<"<--";
            path_flow = min(path_flow, gf[u][v]);
        }
       // cout<<v<<" CApacity="<<path_flow;
        cout<<endl;
        int added_flow;
        if((max_flow+path_flow)<=capacity)
            added_flow=path_flow;
        else
            added_flow=capacity-max_flow;
        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            //cout<<"BEFORE:"<<u<<"-->"<<v<<":"<<gf[u][v]<<endl;
            gf[u][v] -= added_flow;
            //cout<<"After:"<<u<<"-->"<<v<<":"<<gf[u][v]<<endl;
            gf[v][u] += added_flow;
        }
        if(added_flow!=path_flow){

            max_flow += path_flow;
            used_flow+=added_flow;
            break;
        }

        used_flow+=added_flow;
        // Add path flow to overall flow
        max_flow += path_flow;
     //   CENA DO max_flow==CAPACIDADE STOP
    }


    // FILL FLUX
    for (int i = 1; i <=graph.getNumNodes() ; i++){
        for (auto & e : graph.nodes[i].adj) {
            e.flux+=(e.cap-gf[i][e.dest]);
            /*if(e.flux<0){
                cout<<"I:"<<i<<"-->"<<"e.dest:"<<e.dest<<" FLUXO:"<<e.flux<<endl;
               // cout<<"Entrou primeiro if\n";
                if(graph.EdgeExists(e.dest,i)){
                  //  cout<<"Entrou segundo if\n";
                    for(auto itr=graph.nodes[e.dest].adj.begin();itr!=graph.nodes[e.dest].adj.end();itr++){
                        if(itr->dest==i){
                         //   cout<<"Entrou terceiro if\n";
                            cout<<"e.dest"<<e.dest<<"-->"<<itr->dest<<" Fluxo:"<<itr->flux<<endl;
                            itr->flux++;
                            cout<<"e.dest"<<e.dest<<"-->"<<itr->dest<<" NEW Fluxo:"<<itr->flux<<endl;
                        }
                    }
                }
                e.flux=0;
            }*/
        }
    }
    cout<<"\nFINAL:\n";
    graph.printgraph2();
    cout<<"USED FLOW:"<<used_flow<<endl;
    cout<<"MAX FLOW:"<<max_flow<<endl;
    if(used_flow!=0)
    return used_flow;
    else
        return max_flow;

}

//! Preenche, no grafo, as arestas dadas no path com o fluxo dado
//! \param graph- grafo
//! \param path - caminho dado
//! \param initialcapacity - fluxo que se quer usar
//! \return true - Foi possível preencher as arestas com o fluxo dado
//! \return false- Fluxo dado superior à capacidade minima do percurso dado
bool CreatePath(Graph& graph,vector<int> path,int initialcapacity){

   int cont=0;
   int min=INT_MAX;//Guarda a capacidade minima do percurso dado

   // Descobre a capacidade minima do percurso dado
    for (int i = path[cont]; i <=graph.getNumNodes() ; i=path[cont]) {
      //  cout<<"I:"<<i<<endl;
      //  cout<<"PATH INICIAL:"<<path[cont]<<endl;
        for ( auto & e : graph.nodes[i].adj) {
           // cout<<"CONT BEFORE:"<<cont<<endl;
            if(e.dest==path[cont+1]){
               // cout<<"ENTROU NO 1º IF"<<endl;
                if(min>=e.cap){
                    min=e.cap;
                }
                cont++;
               // cout<<i<<"-->"<<e.dest<<"  Cap:"<<e.cap<<endl;
                break;
            }
        }
        if(i==path[path.size()-1])
            break;
       // cout<<"CONT AFTER:"<<cont<<endl;
       // cout<<"PATH FINAL:"<<path[cont]<<endl;
    }
    int added_flow;//Serve para ver o fluxo que vai ser adicionado às arestas usadas

    // A capacidade initial não pode ser maior que a capacidade mínima
    if(initialcapacity>min)
        return false;
    else if(min>initialcapacity)
            added_flow=initialcapacity;
    else
        added_flow=min;

    cont=0;
    //Prenche as arestas usadas com o fluxo usado no caminho
    for (int i = path[cont]; i <=graph.getNumNodes() ; i=path[cont]) {
        for ( auto & e : graph.nodes[i].adj) {
            if(e.dest==path[cont+1]){
                e.flux+=added_flow;
                cont++;
               // cout<<i<<"-->"<<e.dest<<"  Cap:"<<e.cap<<endl;
                break;
            }
        }
        if(i==path[path.size()-1])
            break;
    }

  //  graph.printgraph2();
  //  cout<<"MIN:"<<min<<endl;
    return true;
}
void UpdatePath(Graph& graph,int addedcapacity);
    /** 2.4---Tempo minimo para reagrupar no destinho
     * Um grupo vai ripo- 1-2-4-5
     *  e outro 1-3-4-5
     *  Quanto tempo no minimo para todos chegarem ao destino
     * 2.5---- TEmpo maximo de espera dos locais
     * Cada aresta só tem 1 autocarro
     * Quanto tempo é que o grupo que chegou primeiro vai esperar e quanto vai esperar
     * Indicar o(s) nó(s) onde se espera e o tempo de espera
     */
#endif //DA_T2_G_CENARIO2_H

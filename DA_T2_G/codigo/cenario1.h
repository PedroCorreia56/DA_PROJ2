//
// Created by pedro on 28/05/2022.
//

#ifndef DA_T2_G_CENARIO1_H
#define DA_T2_G_CENARIO1_H
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "../codigo/Graph.h"
#include "../codigo/MaxHeap.h"
#include <map>


//! imprime caminho  
//!\param parent - parent
//!\param start - start
//!\param end - end
void printpath(vector<int>& parent, int start, int end)
{
    if (start == 0) {
        return;
    }

    printpath(parent, parent[start], end);

    cout << start << (start == end ? "\n" : "--");

}

//! cenario 1.1
//!\param graph - graph
//!\param start - start
//!\param end - end
pair<int,vector<int>> MaxGroupSize(Graph graph,int start, int end){


    vector<int> capacidade(graph.getNumNodes()+1, INT_MIN);

    // To get the path at the end of the algorithm
    vector<int> parent(graph.getNumNodes()+1, 0);

    MaxHeap<int,int> heap(graph.getNumNodes(),-1);
    for (int i = 1; i <= graph.getNumNodes(); i++) { // O(n)
        heap.insert(i,capacidade[i]);
    }
    capacidade[start]=INT_MAX;
    heap.increaseKey(start,INT_MAX);

    while(heap.getSize()!=0){
      int t= heap.removeMax(); //O(n)
        for (auto w : graph.nodes[t].adj) { // O(n)
                    if(min(capacidade[t],w.cap)>capacidade[w.dest]){
                        capacidade[w.dest]=min(capacidade[t],w.cap);
                        parent[w.dest]=t;
                        heap.increaseKey(w.dest,capacidade[w.dest]); // O(n)
                    }
        }
    }

    if(capacidade[end]==INT_MAX || capacidade[end]==INT_MIN){
        return {0,parent} ;
    }
    return {capacidade[end],parent};
}

bool BetterPath(map<int,vector<int>> caminhos,map<int,int> numeronos,int current) {

    for (auto itr = caminhos.begin(); itr != caminhos.end(); itr++) {
        if(itr->first<current)
            continue;
        auto temp=itr;
        for (auto i=++temp; i!= caminhos.end(); i++) {
                if(i->first>itr->first && numeronos[i->first]==numeronos[itr->first]){
                    return true;
                }
                else if( i->first>itr->first && numeronos[i->first]<=numeronos[itr->first]){
                    return true;
                }

        }
        return false;
        }

    return false;
}
//! Descobre os melhores pares capacidade+Numero_de_Nós
//! \param graph- grafo com as arestas e os vertices
//! \param start- nó de origem
//! \param end - nó de destino
//! \return true - se existe pelo menos um par
//! \return false- em caso de não existir um caminho do nó de origem para o destino ou esses nós não serem válido
bool cenario1_2(Graph graph, int start, int end) {

    if(start <=0 || start>graph.getNumNodes() || end <=0 || end>graph.getNumNodes() || start==end)
        return false;


    //Grafo residual
    vector<vector<int>> gf(graph.getNumNodes() + 1, vector<int>(graph.getNumNodes() + 1, 0));
    //Grafo que serve só para aceder mais facilmente à capacidade de cada aresta
    vector<vector<int>> originalvalues(graph.getNumNodes() + 1, vector<int>(graph.getNumNodes() + 1, 0));
    for (int i = 1; i <= graph.getNumNodes(); i++) {
        for (auto e: graph.nodes[i].adj) {
            gf[i][e.dest] = e.cap;
            originalvalues[i][e.dest] = e.cap;
        }
    }
    vector<int> parent(graph.getNumNodes() + 1, 0);//Vetor para guardar os caminhos usados

    int v, u;//variavéis de apoio

    //Mapa que guarda o caminho usado(vector<int>) para cada Capacidade(int)
    map<int, vector<int>> caminhos;
    //Mapa que guarda para cada Capacidade(key) o menor número de nós usados(value) para essa capacidade
    map<int, int> numeronos;


    while (Graph::bfs2(gf, start, end, parent, graph.getNumNodes() + 1)) {


        int path_flow = INT_MAX;
        int mincapacity = INT_MAX;
        int count = 1;
        //Encontra a capacidade residual mínima do caminho encontrado no BFS
        //Encontra a capacidade minima do caminho encontrado no BFS
        //Conta o número de nós usados no caminho encontrado no BFS
        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, gf[u][v]);
            mincapacity = min(mincapacity, originalvalues[u][v]);
            count++;
        }

        int flag = 0;//Flag que serve para ver se se vai guardar um novo caminho no map caminhos
        //Caso a capacidade não exista no mapa
        //Criar uma nova key com essa capacidade no caminhos
        //Atribuir o número de nós contados em count a essa capacidade no numeronos
        if (caminhos.find(mincapacity) == caminhos.end()) {
            numeronos[mincapacity] = count;
            caminhos[mincapacity];
            flag = 1;
        }
        //Caso a capacidade já exista
        //Ver se o novo caminho lido tem menor número de nós
        //Se tiver, alterar esse valor no map numeronos e
        //apagar o caminho já existente no map caminhos para essa capacidade
        else if(caminhos.find(mincapacity) != caminhos.end()){
            if(numeronos[mincapacity]>count){
                numeronos[mincapacity] = count;
                caminhos[mincapacity].clear();
                flag=1;
            }
        }
        //Atualiza a capacidade residual das arestas normais e
        // das arestas inversas ao longo do caminho
        //Caso a flag esteja ativada preencher o vetor para a capacidade lida
        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            gf[u][v] -= path_flow;
            gf[v][u] += path_flow;
            if (flag)
                caminhos[mincapacity].push_back(v);
        }
        if (flag)
            caminhos[mincapacity].push_back(u);
    }
    int maxcapacity= MaxGroupSize(graph,start,end).first;
    //MaxGroupSize.first retorna 0 em caso de erro
    if(maxcapacity==0)
        return false;


    cout<<"Melhores pares capacidade+número de nós:\n";
    //Dá print ao melhores pares
    for (auto itr = caminhos.begin(); itr != caminhos.end(); itr++) {

        //Caso haja um par capacidade+numero_de_nos passar à frente
        if(BetterPath(caminhos,numeronos,itr->first)){
            continue;
        }
        cout << "Capacidade:" << itr->first << " Numero nós:" << numeronos[itr->first] << " Caminho:";
        for(int i = itr->second.size() - 1; i >= 0; i--) {
            if (i != 0)
                cout << itr->second.at(i) << "-->";
            if (i == 0)
                cout << itr->second.at(i);
        }
        cout << endl;
    }


    parent=MaxGroupSize(graph,start,end).second;

    // Se a capacidade maxima não existir no map caminhos dar print a ela
    if(caminhos.find(maxcapacity)==caminhos.end()){
        int count=1;
        //Contar o numero de nós
        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            count++;
        }
        cout << "Capacidade:" << maxcapacity << " Numero nós:" << count << " Caminho:";
        printpath(parent,end,end);
    }
    return true;

}

#endif //DA_T2_G_CENARIO1_H

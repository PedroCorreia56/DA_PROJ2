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
#include <stack>

using namespace std;

//! funções usadas em cenario2
class cenario2{
    public:
//! Descobre o fluxo máximo do caminho indicado
//! \param graph - grafo com os caminhos disponíveis
//! \param start - vértice de origem
//! \param end - vértice destino
//! \return max_flow - fluxo máximo do caminho
static int MaxFlux(Graph& graph,int start, int end){
    //Vê se os valores dos vértices são válidas
    if(start <=0 || start>graph.getNumNodes() || end <=0 || end>graph.getNumNodes() || start==end)
        return 0;

    //Grafo Residual
    vector<vector<int>>gf( graph.getNumNodes()+1 , vector<int> (graph.getNumNodes()+1,0));

    //Copia o grafo original para o Grafo Residual
    for (int i = 1; i <=graph.getNumNodes() ; i++){
        for (auto e : graph.nodes[i].adj) {
            gf[i][e.dest]=e.cap;
        }
    }
    //Vetor para guardar os caminhos usados
    vector<int> parent(graph.getNumNodes()+1, 0);

    int v,u;//variavéis de apoio
    int max_flow = 0;//Guarda o fluxo máximo utilizado

    // Descobre o fluxo máximo.
    // O ciclo corre enquanto existir caminho do Vértice Inicial até o Vértice final no Grafo Residual
    while (Graph::bfs2(gf,start,end,parent,graph.getNumNodes()+1)) {

        //Guarda a capacidade residual mínima do caminho
        int path_flow = INT_MAX;
        // Encontra a capacidade residual mínima do caminho encontrado no BFS
        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, gf[u][v]);
        }

        //Atualiza a capacidade residual das arestas normais e
        // das arestas inversas ao longo do caminho
        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            gf[u][v] -= path_flow;
            gf[v][u] += path_flow;
        }
        max_flow += path_flow;//adiciona o fluxo do caminho encontrado
    }

    // Atualiza o fluxo das arestas do grafo original
    for (int i = 1; i <=graph.getNumNodes() ; i++){
        for (auto & e : graph.nodes[i].adj) {
            e.flux+=(e.cap-gf[i][e.dest]);
        }
    }

    return max_flow;
}

//! Descobre se existe um caminho que leve a quantidade de pessoas indicada
//! \param graph - grafo que contém os caminhos disponíveis
//! \param start - vértice de origem
//! \param end - vértice destine
//! \param capacity - Quantidade de Pessoas
//! \return used_flow - quantidade de flow usado
//! \return 0 - caso haja erro, ou não exista caminho entre os 2 vértices
static int FindPath(Graph& graph,int start,int end, int capacity){

    //Vê se os valores dos vértices são válidas
    if(start <=0 || start>graph.getNumNodes() || end <=0 || end>graph.getNumNodes() || start==end)
        return 0;

    //Grafo Residual
    vector<vector<int>>gf( graph.getNumNodes()+1 , vector<int> (graph.getNumNodes()+1,0));

    //Copia o grafo original para o Grafo Residual
    for (int i = 1; i <=graph.getNumNodes() ; i++){
        for (auto e : graph.nodes[i].adj) {
            gf[i][e.dest]=e.cap-e.flux; //o fluxo inicial é 0, mas está assim para ser capaz de suportar o cenário 2.2
        }
    }

    //Vetor para guardar o caminho usado
    vector<int> parent(graph.getNumNodes()+1, 0);


    int v,u;//variavéis de apoio
    int max_flow = 0;//Guarda o fluxo máximo
    int used_flow=0;//Guarda o fluxo utilizado
    while (Graph::bfs2(gf,start,end,parent,graph.getNumNodes()+1)) {

        //Guarda a capacidade residual mínima do caminho
        int path_flow = INT_MAX;
        //Encontra a capacidade residual mínima do caminho encontrado no BFS
        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, gf[u][v]);
        }

        //variável auxiliar
        int added_flow;
        //Caso o fluxo máximo+fluxo novo caminho seja menor que o capacidade dada
        if((max_flow+path_flow)<=capacity)
            added_flow=path_flow;
        else//Caso a soma do fluxo do novo caminho com o fluxo máximo seja superior à capacidade, apenas usa-se a quantidade necessária
            added_flow=capacity-max_flow;

        //Atualiza a capacidade residual das arestas normais e
        // das arestas inversas ao longo do caminho
        for (v = end; v != start; v = parent[v]) {
            u = parent[v];
            gf[u][v] -= added_flow;
            gf[v][u] += added_flow;
        }
        //Se isto acontecer quer dizer que já se chegou à capacidade pedida
        if(added_flow!=path_flow){
            max_flow += path_flow;
            used_flow+=added_flow;
            break;
        }

        //Adiciona o fluxo adicionado ao fluxo usado
        used_flow+=added_flow;
        //adiciona o fluxo do caminho encontrado ao fluxo total
        max_flow += path_flow;
    }


    // Atualiza o fluxo das arestas do grafo original
    for (int i = 1; i <=graph.getNumNodes() ; i++){
        for (auto & e : graph.nodes[i].adj) {
            //Caso a aresta não tenha fluxo inicial
            if (e.flux==0)
            e.flux+=(e.cap-gf[i][e.dest]);
            else //Caso a aresta tenha fluxo inical, usado por causa do cenário 2.2
                e.flux+=((e.cap-e.flux)-gf[i][e.dest]);
        }
    }

    cout<<"Tamanho do grupo ''usado''"<<used_flow<<endl;
    cout<<"Tamanho do grupo máximo:"<<max_flow<<endl;
    if(used_flow!=0)
    return used_flow;
    else
        return max_flow;

}

//! Descobre se é possível aumentar a dimensão de um grupo por um número de unidades dado.
//! \param graph - grafo que contém o caminho inicial (arestas já preenchidas com fluxo)
//! \param initialcapacity - Tamanho Inicial do Grupo
//! \param addedcapacity - Tamanho que se pertende adicionar
//! \param start - vértice de origem
//! \param end - vértice de destino
static void UpdatePath(Graph& graph,int initialcapacity,int addedcapacity,int start,int end){

    //Tamanho que se pertende adicionar não pode ser negativo
    if(addedcapacity<0)
        return;
        //Descobre se é possível addicionar a capacidade desejada ao grafo
        int addedflux= FindPath(graph,start,end,addedcapacity);

        //Caso tenha sido capaz de adicionar a capacidade
        if(initialcapacity+addedflux==initialcapacity+addedcapacity){
            graph.printgraph2();
            cout<<"Adição concluída\n";
        }
        else{
            cout<<"Não é possível realizar a adição\n";
        }
        cout<<"Capacidade total pedida:"<<initialcapacity+addedcapacity<<endl;
        cout<<"Capacidade atingida:"<<initialcapacity+addedflux<<endl;

}

//! Consegue a duração mínima do caminho do vértice de origem ao vértice de destino
//! \param graph - grafo com as arestas a serem utilizadas
//! \param start - vértice de origem
//! \param end - vértice de destino
//! \return int - Duração mínima do caminho
//! \return vector<int> - Array com a data de início mais proxima de cada vértice do caminho tomado
static pair<int,vector<int> > EarliestStart(Graph graph,int start,int end){

    //Vetor para guardar o caminho usado
    vector<int> parent(graph.getNumNodes() +1, 0);

    //Vetor que guarda o a data de inicio mais próxima de cada vértice
    vector<int> ES(graph.getNumNodes() +1,0);

    vector<int> GrauE(graph.getNumNodes() +1,0);
    queue<int> S;//fila que guarda o vértice para ler

    if(start <=0 || start>graph.getNumNodes() || end <=0 || end>graph.getNumNodes() || start==end)
        return {0,parent};

    for (int i = start; i <=graph.getNumNodes() ; i++) {
        for (auto e : graph.nodes[i].adj) {
            //Se o flux for maior que zero quer dizer que é um dos caminhos a ser considerado no gráfico
            if(e.flux>0)
                GrauE[e.dest]=GrauE[e.dest]+1;
        }
    }

    for (int i =start; i <=graph.getNumNodes()  ; i++) {
        if(GrauE[i]==0)
            S.push(i);
    }

    int DurMin=-1;// Guarda a duraçaõ mínima do caminho
    int vf=0;

   // Ciclo para descobrir a duração mínima do caminho
    while(S.size()!=0){
        int flag=0;
        int v=S.front();
        S.pop();

        if(DurMin<ES[v]){
            DurMin=ES[v];
            vf=v;
        }
        if(v==end)
            break;
        for (auto w : graph.nodes[v].adj) {
            //Se o flux for maior que zero quer dizer que é um dos caminhos a ser considerado no gráfico
            if(w.flux>0){
                if(ES[w.dest]<ES[v]+w.horas){
                    ES[w.dest]=ES[v]+w.horas;
                    parent[w.dest]=v;
                }
                GrauE[w.dest]=GrauE[w.dest]-1;
                if(GrauE[w.dest]==0)
                    S.push(w.dest);
            }

        }

    }

    return {DurMin,ES};
}
//! Descobre o máximo tempo de espera e o(s) nó(s) em que isso acontece
//! \param graph - grafo a ser utilizado
//! \param start - vértice de origem
//! \param end - vértice de destino
static void cenario2_5(Graph graph,int start,int end){

    //Guarda o valor da duração mínima do caminho
    int DurMin= EarliestStart(graph,start,end).first;

    if(DurMin==-1){
        cout<<"Dados inválidos,ou vértices não existem ou não existe ligação entre os dois\n";
        return;
    }

    vector<int> ES=EarliestStart(graph,start,end).second; // Recebe o array que contem o Earliest Start de cada nó

   //Guarda o tempo de espera máximo de cada nó
    vector<int> NodeWaitTime(graph.getNumNodes()+1,0);

    //Calcula o máximo tempo de espera de cada nó
    for (int i = start; i <=graph.getNumNodes() ; i++) {
        for (auto e : graph.nodes[i].adj) {
            //Se o flux for maior que zero quer dizer que é um dos caminhos a ser considerado no gráfico
            if(e.flux>0){
                int max=ES[e.dest]-ES[i]-e.horas; // Tempo de espera= ES[nó atual] - (ES[nó anterior] + duração da aresta)
                if(NodeWaitTime[e.dest]<max){
                    NodeWaitTime[e.dest]=max;
                }
            }

        }
    }
    int MaxWaitTime=INT_MIN;
    //Descobre o maior tempo de espera dos nós considerados
    for(int i=start; i<=graph.getNumNodes();i++){
        if(MaxWaitTime<=NodeWaitTime[i])
            MaxWaitTime=NodeWaitTime[i];
    }
    vector<int> NodesStoped;//Vetor para guardar os nós com o menor tempo de espera

    //Guarda no vetor os nós em que o tempo de espera deles é o mesmo que o Maior tempo de Espera
    for(int i=start; i<=graph.getNumNodes();i++){
        if(MaxWaitTime==NodeWaitTime[i])
            NodesStoped.push_back(i);
    }
    cout<<"MAximo tempo de espera:"<<MaxWaitTime<<endl;
    cout<<"Isso aconteceu em:"<<NodesStoped.size()<<" nó(s)\n";
    cout <<" Nó(s):";
    for (auto i : NodesStoped) {
        cout<<i<<" ";
    }
    cout<<endl;


}
};

#endif //DA_T2_G_CENARIO2_H

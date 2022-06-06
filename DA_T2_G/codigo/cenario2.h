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

int MaxFlux(Graph& graph,int start, int end){

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


int FindPath(Graph& graph,int start,int end, int capacity){

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

    //Vetor para guardar o caminho usados
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
    //cout<<"\nCaminho:\n";
    //graph.printgraph2();
    cout<<"Tamanho do grupo ''usado''"<<used_flow<<endl;
    cout<<"Tamanho do grupo máximo:"<<max_flow<<endl;
    if(used_flow!=0)
    return used_flow;
    else
        return max_flow;

}
int FindMinCapacity(Graph graph, vector<int> path){


    int cont=0;
    int min=INT_MAX;//Guarda a capacidade minima do percurso dado
    int flag=0; //Se depois do segundo for continuar a 0, a aresta não existe
    // Descobre a capacidade minima do percurso dado
    for (int i = path[cont]; i <=graph.getNumNodes() ; i=path[cont]) {
        flag=0;
        //  cout<<"I:"<<i<<endl;
        //  cout<<"PATH INICIAL:"<<path[cont]<<endl;
        for ( auto  e : graph.nodes[i].adj) {
            // cout<<"CONT BEFORE:"<<cont<<endl;
            if(e.dest==path[cont+1]){
                flag=1;
                // cout<<"ENTROU NO 1º IF"<<endl;
                if(min>=e.cap){
                    min=e.cap;
                }
                cont++;
               //  cout<<i<<"-->"<<e.dest<<"  Cap:"<<e.cap<<endl;
                break;
            }
          //  cout<<i<<"-->"<<e.dest<<endl;
        }

        if(i==path[path.size()-1])
            break;
        if(flag!=1){
            cout<<"Caminho não é possível (uma das arestas não existe)\n";
            return 0;
        }
        // cout<<"CONT AFTER:"<<cont<<endl;
        // cout<<"PATH FINAL:"<<path[cont]<<endl;
    }
    return min;
}
//! Preenche, no grafo dado, as arestas dadas no path com o fluxo dado
//! \param graph- grafo
//! \param path - caminho dado
//! \param initialcapacity - fluxo que se quer usar
//! \return true - Foi possível preencher as arestas com o fluxo dado
//! \return false- Fluxo dado superior à capacidade minima do percurso dado
bool FillPath(Graph& graph,vector<int> path,int initialcapacity){


    int min= FindMinCapacity(graph,path);
    if(min==0)
        return false;
    int added_flow;//Serve para ver o fluxo que vai ser adicionado às arestas usadas

    // A capacidade inicial não pode ser maior que a capacidade mínima
    if(initialcapacity>min)
        return false;
    else if(min>initialcapacity)
            added_flow=initialcapacity;
    else
        added_flow=min;

    int cont=0;
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
void UpdatePath(Graph& graph,int initialcapacity,int addedcapacity,vector<int> path){

    if(addedcapacity==0)
        return;
    int start=path[0];
    int end=path[path.size()-1];

    int min= FindMinCapacity(graph,path);

    //Caso o fluxo adicional ainda caiba no caminho usado
    if(addedcapacity<=(min-initialcapacity)){
        cout<<"AdedCpacity:"<<addedcapacity<<" MIN-INCP="<<min-initialcapacity<<endl;
        int cont=0;
        //Prenche as arestas usadas com o fluxo extra
        for (int i = path[cont]; i <=graph.getNumNodes() ; i=path[cont]) {
            for ( auto & e : graph.nodes[i].adj) {
                if(e.dest==path[cont+1]){
                    e.flux+=addedcapacity;
                    cont++;
                    break;
                }
            }
            if(i==path[path.size()-1])
                break;
        }

        return;
    }
    else{

        int missingflux=min-initialcapacity; // FLUXO que ainda cabe no caminho usado
        int remaingflux=addedcapacity-missingflux; // FLUXO que sobra
        cout<<"MISSINGFLUX:"<<missingflux<<" REMAINGFLUX:"<<remaingflux<<endl;
        int cont=0;

        //Prenche as arestas usadas com o fluxo extra
        for (int i = path[cont]; i <=graph.getNumNodes() ; i=path[cont]) {

            for ( auto & e : graph.nodes[i].adj) {
                if(e.dest==path[cont+1]){
                    e.flux+=missingflux;
                    cont++;
                    break;
                }
            }
            if(i==path[path.size()-1])
                break;
        }

        int flux= FindPath(graph,start,end,remaingflux);
        if((initialcapacity+addedcapacity)==(flux+initialcapacity+missingflux)){
            graph.printgraph2();
            cout<<"Adição concluída\n";
        }
        else{
            cout<<"Não é possível realizar a adição\n";
        }

        cout<<"FLUX WANTED:"<<initialcapacity+addedcapacity<<endl;
        cout<<"Flux used:"<<flux+initialcapacity+missingflux<<endl;

    }



}

void CopyPathToGraph(Graph graph1,Graph& graph2){

    for (int i = 1; i <=graph1.getNumNodes() ; i++) {
        for (auto e : graph1.nodes[i].adj) {
            // if(e.dest<=lastnode)
            if(e.flux!=0)
                graph2.addEdge(i,e.dest,e.cap,e.horas);
        }
    }


}
pair<int,vector<int> > EarliestStart(Graph graph){

    vector<int> parent(graph.getNumNodes() +1, 0);
    vector<int> ES(graph.getNumNodes() +1,0);
    vector<int> GrauE(graph.getNumNodes() +1,0);
    queue<int> S;

    for (int i = 1; i <=graph.getNumNodes() ; i++) {
        for (auto e : graph.nodes[i].adj) {
                GrauE[e.dest]=GrauE[e.dest]+1;
        }
    }

    for (int i =1; i <=graph.getNumNodes()  ; i++) {
        if(GrauE[i]==0)
            S.push(i);
    }

    int DurMin=-1;
    int vf=0;
   // cout<<"S size:"<<S.size()<<endl;
    while(S.size()!=0){
        int v=S.front();
        S.pop();
        if(DurMin<ES[v]){
            DurMin=ES[v];
            vf=v;
        }
        for (auto w : graph.nodes[v].adj) {
                if(ES[w.dest]<ES[v]+w.horas){
                    ES[w.dest]=ES[v]+w.horas;
                    parent[w.dest]=v;
                }
                GrauE[w.dest]=GrauE[w.dest]-1;
                if(GrauE[w.dest]==0)
                    S.push(w.dest);
        }
    }
   // printpath(parent,vf,vf);
    return {DurMin,ES};
}

void cenario2_5(Graph graph,int wantednode){

    int DurMin= EarliestStart(graph).first;
    vector<int> ES=EarliestStart(graph).second; // Recebe o array que contem o Earliest Start de cada nó

    vector<int> NodeWaitTime(graph.getNumNodes()+1,0);
    //Calcula o máximo tempo de espera de cada nó
    for (int i = 1; i <=graph.getNumNodes() ; i++) {
        for (auto e : graph.nodes[i].adj) {
            int max=ES[e.dest]-ES[i]-e.horas; // Tempo de espera= ES[nó atual] - (ES[nó anterior] + duração da aresta)
                    if(NodeWaitTime[e.dest]<max){
                        NodeWaitTime[e.dest]=max;
                    }
        }
    }

    int MaxWaitTime=INT_MIN;
    for(int i=1; i<=graph.getNumNodes();i++){
        if(MaxWaitTime<=NodeWaitTime[i])
            MaxWaitTime=NodeWaitTime[i];
    }

    vector<int> NodesStoped;
    for(int i=1; i<=graph.getNumNodes();i++){
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

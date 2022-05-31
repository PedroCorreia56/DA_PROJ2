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

int MaxFlux(Graph graph,int start,int end, int capacity){

    vector<vector<int>>gf( graph.getNumNodes()+1 , vector<int> (graph.getNumNodes()+1,0));

    cout<<"GF[0][1]="<<gf[0][1]<<endl;
    cout<<"INITIAL:\n";
    cout<<"ARESTA\t\tFLUXO/CAPACIDADE"<<endl;
    for (int i = 1; i <=graph.getNumNodes() ; i++){
        for (auto e : graph.nodes[i].adj) {
            cout<<i<<":";
            gf[i][e.dest]=e.cap;
            cout<<"-->"<<e.dest<<"\t\t"<<e.flux<<"/"<<e.cap;
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
            cout<<v<<"<--";
            path_flow = min(path_flow, gf[u][v]);
        }
        cout<<v<<" CApacity="<<path_flow;
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
    graph.printgraph();
    cout<<"USED FLOW:"<<used_flow<<endl;
    cout<<"MAX FLOW:"<<max_flow<<endl;
    if(used_flow!=0)
    return used_flow;
    else
        return max_flow;

}

#endif //DA_T2_G_CENARIO2_H

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

void MaxFlux(Graph graph,int start,int end, int capacity){

    vector<vector<int>>f( graph.getNumNodes()+1 , vector<int> (graph.getNumNodes()+1));
    for (int i = 1; i <=graph.getNumNodes() ; i++){
        //cout<<i<<":";
        for (auto e : graph.nodes[i].adj) {
                f[i][e.dest]=0;
            //cout<<e.dest<<" ";
                f[e.dest][i]=0;
        }
       // cout<<endl;
    }
    Graph gf(graph.getNumNodes(),true);
    gf.DuplicateGraph(&gf,graph);
/*      //CHECKA SE DUPLICOU BEM
    for (int i = 1; i <=graph.getNumNodes() ; i++){
        cout<<i<<":";
        for (auto e : gf.nodes[i].adj) {
            cout<<e.dest<<" ";
        }
         cout<<endl;
    }
    */

    while(MaxGroupSize(gf,start,end)!=0){
        int cy=MaxGroupSize(gf,start,end);
        ARRANJAR FORMA DE GUARDAR O CAMINHO DO MAX GROUP SIZE

    }

}

#endif //DA_T2_G_CENARIO2_H

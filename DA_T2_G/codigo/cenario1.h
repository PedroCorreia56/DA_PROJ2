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
int MaxGroupSize(Graph graph,int start, int end){

    vector<int> capacidade(graph.getNumNodes()+1, INT_MIN);

    // To get the path at the end of the algorithm
    vector<int> parent(graph.getNumNodes()+1, 0);

    MaxHeap<int,int> heap(graph.getNumNodes(),-1);
    for (int i = 1; i <= graph.getNumNodes(); i++) {
        heap.insert(i,capacidade[i]);
    }
    capacidade[start]=INT_MAX;
    heap.increaseKey(start,INT_MAX);

    while(heap.getSize()!=0){
      int t= heap.removeMax();
        for (auto w : graph.nodes[t].adj) {
                    if(min(capacidade[t],w.cap)>capacidade[w.dest]){
                        capacidade[w.dest]=min(capacidade[t],w.cap);
                        parent[w.dest]=t;
                        heap.increaseKey(w.dest,capacidade[w.dest]);
                    }
        }
    }

    if(capacidade[end]==INT_MAX || capacidade[end]==INT_MIN){
        cout<<"MAX SIZE:0 (mesmo vertice ou não existe ligação do inicial para o final)\n";
        return 0 ;
    }
    cout<<"The path:\n";
    printpath(parent,end,end);
    return capacidade[end];

}

//! finding index of minimum distance
//!\param graph - graph
int minDist(Graph graph)
{
    int minimum=INT_MAX,ind;

    for(int k=1;k<=graph.getNumNodes();k++)
    {
        if(graph.nodes[k].visited==false && graph.nodes[k].distance<=minimum)
        {
            minimum=graph.nodes[k].distance;
            ind=k;
        }
    }
    return ind;
}


//! cenario 1.2
//!\param graph - graph
//!\param start - start
//!\param end - end
int ShortestPath(Graph graph,int start, int end){

       vector<int> parent(graph.getNumNodes()+1, 0);

      for (int i = 1; i <= graph.getNumNodes(); i++) {
          graph.nodes[i].distance=INT_MAX;
          graph.nodes[i].visited=false;
      }
      graph.nodes[start].distance=0;

    for (int i = 1; i <=graph.getNumNodes() ; i++) {
                int m= minDist(graph);
                graph.nodes[m].visited=true;
                for(auto k : graph.nodes[m].adj){
                    if(!graph.nodes[k.dest].visited && graph.nodes[m].distance!=INT_MAX && ((k.cap+graph.nodes[m].distance)<graph.nodes[k.dest].distance)){
                        graph.nodes[k.dest].distance=k.cap+graph.nodes[m].distance;
                        parent[k.dest]=m;
                    }
                }
    }

    if(graph.nodes[end].distance==INT_MAX || start==end){
        cout<<"Distance:0 (mesmo vertice ou não existe ligação do inicial para o final)\n";
        return 0;
    }

    cout<<"The path:\n";
    printpath(parent,end,end);
    return graph.nodes[end].distance;
   // cout<<"Distance:"<<graph.nodes[end].distance<<endl;
}
#endif //DA_T2_G_CENARIO1_H

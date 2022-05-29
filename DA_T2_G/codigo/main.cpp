//
// Created by pedro on 24/05/2022.
//

#include <stdio.h>
#include <fstream>
#include <cstring>
#include "../codigo/Graph.h"
#include "cenario1.h"
using namespace std;
int main(){

    string grafofile("../input/in12.txt");//Ficheiro com o grafo
    string line;//string que guarda as linhas do ficheiro

    ifstream input_file(grafofile);
    //Verificar se a stream está associada a um ficheiro
    if(!input_file.is_open()){
        cout<<"Erro ao abrir o ficheiro "<<endl;
    }

    //leitura do grafo
    std::getline(input_file,line);
    char *dup = strdup(line.c_str());
    int N=atoi(strtok(dup," "));//número de vértices
    int R=atoi(strtok(NULL," "));//número de ramos


    Graph grafo(N,true);
    while(std::getline(input_file,line)){
        dup = strdup(line.c_str());
            int i = atoi(strtok(dup," "));
            int j = atoi(strtok(NULL," "));
            int capacidade = atoi(strtok(NULL," "));
            int duracao= atoi(strtok(NULL," "));

            grafo.addEdge(i,j,capacidade,duracao);
            //cout<<"Incial: "<<i<<" Destino: "<<j<<" Capacidade:"<<capacidade<<" Duracao:"<<duracao<<endl;
            free(dup);
        }
    //cout<<"NOS:"<<grafo.getNumNodes()<<endl;
   MaxGroupSize(grafo,1,9);
   ShortestPath(grafo,1,9);
   // cout<<"Capacidade:"<<grafo.nodes.at(1).adj.begin()->cap<<" DEST:"<<grafo.nodes[1].adj.begin()->dest<<endl;

    return 0;
}



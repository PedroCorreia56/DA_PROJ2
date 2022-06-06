//
// Created by pedro on 24/05/2022.
//

#include <stdio.h>
#include <fstream>
#include <cstring>
#include <vector>
#include "../codigo/Graph.h"
#include "cenario1.h"
#include "cenario2.h"
using namespace std;

#include <bits/stdc++.h>
#include <sys/time.h>

int main(){

    string grafofile("../input/in01_b.txt");//Ficheiro com o grafo
    string line;//string que guarda as linhas do ficheiro

    ifstream input_file(grafofile);
    //Verificar se a stream está associada a um ficheiro
    if(!input_file.is_open()){
        cout<<"Erro ao abrir o ficheiro "<<endl;
        return 0;
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
            free(dup);
        }

    cout<<"Cenário 1:Grupos que não se separam\n1.1-Maximizar a dimensão do grupo\n1.2-Maximizar a dimensão do grupo e minimizar o número de transbordos\n";
    cout<<"Cenário 2:Grupos que podem separar-se\n2.1-Determinar um encaminhamento para um grupo, dada a sua dimensão\n"
          "2.2-Corrigir um encaminhamento, se necessário, para que a dimensão do grupo possa aumentar\n"
          "de um número de unidades dado\n2.3-Determinar a dimensão máxima do grupo e um encaminhamento\n"
          "2.4-Determinar quando é que o grupo se reuniria novamente no destino\n"
          "2.5-Determinar o tempo máximo de espera e os locais em que haveria elementos que esperam esse tempo\n";
    cout<<"Indique o cenário que deseja (ex:2.1):\n";
    double cen;
    cin>>cen;


    vector<int> parent(grafo.getNumNodes()+1, 0);//vetor usado para dar print a caminhos
    int start,end;//Vértices iniciais e finais, respetivamente
    int capacity;//Tamanho do grupo inicial
    if(cen==1.1)
    {
        cout<<"Indique o vértice de origem e o vértice de destino:";
        cin>>start>>end;

        time_t starta, enda;
        time(&starta);
        int maxgroupsize= MaxGroupSize(grafo,start,end).first;
        parent=MaxGroupSize(grafo,start,end).second;
        if(maxgroupsize==0){
            cout<<"A maior dimensão do grupo é:0 (mesmo vertice ou não existe ligação do inicial para o final)\n";
            return 0;
        }
        cout<<"A maior dimensão do grupo é:"<<maxgroupsize<<"\nCom o caminho:";
        printpath(parent,end,end);
        time(&enda);
        double time_taken = double(enda - starta);
        cout << "Time taken by program is : " << fixed
             << time_taken;
        cout << " sec " << endl;
        cout<<endl;

    }
    else if(cen==1.2){

        cout<<"Indique o vértice de origem e o vértice de destino:";
        cin>>start>>end;
        if(!cenario1_2(grafo,start,end)){
            cout<<"Erro, mesmo vértice ou não existe ligação do inicial para o final\n";
            return 0;
        }



    }
    else if(cen==2.1)
    {

        cout<<"Indique o vértice de origem,o vértice de destino e o tamanho do grupo que deseja:";
        cin>>start>>end>>capacity;

        cout<<"Tamanho do grupo pedido:"<<capacity<<endl;
        int usedflow= FindPath(grafo,start,end,capacity);
        if(usedflow==0){
            cout<<"Erro nos dados inseridos, nós não existem ou não existe ligação entre os dois\n";
            return 0;
        }
        grafo.printgraph2();
        if(usedflow<capacity){
            cout<<"O tamanho desse grupo não é aceite, atrás aparece o caminho para a capaciade máxima aceite para esse caminho\n";
        }

    }
    else if(cen==2.2){


    }
    else if(cen==2.3){
        cout<<"Indique o vértice de origem e o vértice de destino:";
        cin>>start>>end;

        int maxflux=MaxFlux(grafo,start,end);
        if(maxflux==0){
            cout<<"Erro nos dados inseridos, nós não existem ou não existe ligação entre os dois\n";
            return 0;
        }
        cout<<"Caminho:\n";
        grafo.printgraph2();
        cout<<"Dimensão Máxima do grupo:"<<maxflux<<endl;
    }
    else if(cen==2.4){


    }
    else if(cen==2.5){


    }
    else{
        cout<<"Não inseriu um cenário válido\n";
    }



    /*int max=MaxGroupSize(grafo,1,5000).first;
    cout<<"MAx grooup size:"<<max<<endl;
    cout<<"Path:";
    vector<int> parent(grafo.getNumNodes()+1, 0);
    parent=MaxGroupSize(grafo,1,5000).second;
    printpath(parent,5000,5000);
     */
    cenario1_2(grafo,1,5000);

   // teste(grafo,1,50);
    //cout<<"NOS:"<<grafo.getNumNodes()<<endl;
  // cout<<"MAX CAPACITY:"<<MaxGroupSize(grafo,9,5)<<endl;
 //  cout<<"Distance:"<<ShortestPath(grafo,9,5)<<endl;
   // cout<<"Capacidade:"<<grafo.nodes.at(1).adj.begin()->cap<<" DEST:"<<grafo.nodes[1].adj.begin()->dest<<endl;
  // int flux =FindPath(grafo,1,6,22);
   //cout<<"FLUX:"<<flux<<endl;



   /*
    int maxflux=MaxFlux(grafo,1,7);
    if(maxflux==0){
        cout<<"Erro nos dados inseridos\n";
        return 0;
    }
    grafo.printgraph2();
    cout<<"Max Flux:"<<maxflux<<endl;

    /*
  int p,c;
    vector<int> path;
    cout<<"Enter your path (press 0 to end):";
    cin>>p;
  while(p!=0){
      path.push_back(p);
      cin>>p;
  }
  cout<<"Enter the capacity:";
  cin>>c;
    if(!FillPath(grafo,path,c)){
        cout<<"Capacidade inicial dada não é possivel no caminho dado"<<endl;
        return 0;
    }
    grafo.printgraph2();
    int added;
    cout<<"Enter the capacity you want to add:";
    cin>>added;
    UpdatePath(grafo,c,added,path);
 //   grafo.printgraph2();
*/
/*
int start,end,groupsize;
    cout<<"Enter the starting node:";
    cin>>start;
    cout<<"Enter the last node:";
    cin>>end;
    cout<<"Enter the groupsize:";
    cin>>groupsize;
    if(!FindPath(grafo,start,end,groupsize)){
        cout<<"Algo deu errado\n";
        return 0;
    }
*/
    //Graph teste(grafo.getNumNodes(),true);
    //CopyPathToGraph(grafo,teste);
   // cout<<"GRAFO DE TESTES\n";
  //  teste.printgraph1();
 /*   int es= EarliestStart(grafo).first;
    if(es==0 || es==-1){
        cout<<"DEU ERRO\n";
        return 0;
    }
    cout<<"Earliest Start:"<<es<<endl;
    LatestFinish(grafo,5);
*/
    return 0;
}



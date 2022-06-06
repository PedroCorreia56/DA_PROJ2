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

    string grafofile("../input/in08_b.txt");//Ficheiro com o grafo
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
    int N=atoi(strtok(dup," "));  //número de vértices
    int R=atoi(strtok(NULL," ")); //número de ramos


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


        int maxgroupsize= MaxGroupSize(grafo,start,end).first;
        parent=MaxGroupSize(grafo,start,end).second;
        if(maxgroupsize==0){
            cout<<"A maior dimensão do grupo é:0 (mesmo vertice ou não existe ligação do inicial para o final)\n";
            return 0;
        }
        cout<<"A maior dimensão do grupo é:"<<maxgroupsize<<"\nCom o caminho:";
        printpath(parent,end,end);

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

        if(usedflow<capacity){
            cout<<"O tamanho desse grupo não é aceite, atrás aparece o caminho para a capaciade máxima aceite para esse caminho\n";
        }
        grafo.printgraph2();

    }
    else if(cen==2.2){

        cout<<"Indique o vértice de origem,o vértice de destino e o tamanho do grupo inicial que deseja:";
        cin>>start>>end>>capacity;


        int usedflow= FindPath(grafo,start,end,capacity);
        if(usedflow==0){
            cout<<"Erro nos dados inseridos, nós não existem ou não existe ligação entre os dois\n";
            return 0;
        }
        if(usedflow<capacity){
            cout<<"O tamanho desse grupo não é aceite, atrás aparece o caminho para a capaciade máxima aceite para esse caminho\n";
            return 0;
        }
        cout<<"Caminho Inicial:\n";
        grafo.printgraph2();
        cout<<"Indique quanto pretende adicionar ao grupo:";
        int addedcapacity;
        cin>>addedcapacity;
        UpdatePath(grafo,capacity,addedcapacity,start,end);
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
        cout<<"Indique o vértice de origem e o vértice de destino:";
        cin>>start>>end;
        int maxflux=MaxFlux(grafo,start,end);
        if(maxflux==0){
            cout<<"Erro nos dados inseridos, nós não existem ou não existe ligação entre os dois\n";
            return 0;
        }
        cout<<"Caminho a ser usado:\n";
        grafo.printgraph3();

        int temporeunir= EarliestStart(grafo,start,end).first;

        if(temporeunir==-1 || temporeunir==0){
            cout<<"Erro nos dados inseridos, nós não existem ou não existe ligação entre os dois\n";
            return 0;
        }
        cout<<"Tempo que se reunem: "<<temporeunir<<"h"<<endl;
    }
    else if(cen==2.5){
        cout<<"Indique o vértice de origem e o vértice de destino:";
        cin>>start>>end;

        int maxflux=MaxFlux(grafo,start,end);
        if(maxflux==0){
            cout<<"Erro nos dados inseridos, nós não existem ou não existe ligação entre os dois\n";
            return 0;
        }
        cout<<"Caminho a ser usado:\n";
        grafo.printgraph3();
        cenario2_5(grafo,start,end);

    }
    else{
        cout<<"Não inseriu um cenário válido\n";
    }

    return 0;
}



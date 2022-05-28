//
// Created by pedro on 24/05/2022.
//

#include <stdio.h>
#include <fstream>
#include <cstring>
#include "grafo2.h"
int main(){

    string grafofile("../input/in01.txt");//Ficheiro com o grafo
    string line;//string que guarda as linhas do ficheiro

    ifstream input_file(grafofile);
    //Verificar se a stream está associada a um ficheiro
    if(!input_file.is_open()){
        cout<<"Erro ao abrir o ficheiro "<<endl;
    }

    int temp=0;
    //leitura do grafo
    while(std::getline(input_file,line)){
        char *dup = strdup(line.c_str());

        if(temp==0){
            int N=atoi(strtok(dup," "));//número de vértices
            int R=atoi(strtok(NULL," "));//número de ramos
            criar grafo
            Grafo=///
            temp++;


        }
        else{
            int i = atoi(strtok(dup," "));
            int j = atoi(strtok(NULL," "));
            int capacidade = atoi(strtok(NULL," "));
            int duracao= atoi(strtok(NULL," "));
            free(dup);
            guardar as merdas no grafo
        }
    }
}


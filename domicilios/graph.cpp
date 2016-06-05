#include <fstream>
#include <string>

#include "graph.h"

using namespace std;

int archsSize (){
    int archs=0;
    string line;
    fstream count("medellin_arcos.txt", ios::in);
    
    getline (count,line);
    archs = stoi(line);
    
    count.close();
    
    return archs;
}

int edgesSize (){
    int size=0;
    string line;
    fstream count("medellin_arcos.txt", ios::in);
    while (getline (count,line)) {
        ++size;
    }
    //cout<<size-1<<endl;
    count.close();
    
    return size-1;
}

Edge nodos (string line){
    int cont=0;
    Edge node;
    
    char *aux;
    aux = new char(line.length()+1);
    strcpy(aux, line.c_str());
    
    char *token = strtok(aux, " ");
    while (token != NULL) {
        
        if (cont == 0) {
            node.origen = atoi(token);
            ++cont;
            token = strtok(NULL, " ");
        }
        if (cont == 1) {
            node.destino = atoi(token);
            ++cont;
        }
        if (cont == 2) {
            node.weight = atoi(token);
            token = strtok(NULL, " ");
        }
        
    }
    
    return node;
}
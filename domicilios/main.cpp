//
//  main.cpp
//  domicilios
//
//  Created by Jose Mejia y Santiago Baena on 5/31/16.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <array>

#include <limits> // for numeric_limits

#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

#include "dijkstra.h"
#include "graph.h"

using namespace std;

int main(){
    string line;
    int V = archsSize();  // Number of vertices in graph
    int E = edgesSize();  // Number of edges in graph
    int cont=0;
    int domiciliarios=0;
    int **ruta, **rutaOptima;
    int *inicio;
    int rutaMenor = 99999;
    
    adjacency_list_t adjacency_list(E);
    
    
    fstream arcos("medellin_arcos.txt", ios::in);
    
    while (getline (arcos,line)) {
        if (cont > 0) {
            adjacency_list[nodos(line).origen].push_back(neighbor(nodos(line).destino, nodos(line).weight));
        }
        ++cont;
    }
    arcos.close();
    
    cont = 0;
    fstream domicilios("test.txt", ios::in);
    while (getline (domicilios,line, '\n')) {
        
        
        if (cont == 0){
            
            domiciliarios = stoi(line);
            
            ruta = new int*[domiciliarios];
            rutaOptima = new int*[domiciliarios];
            inicio = new int[domiciliarios];
            
        }
        if (cont > 0) {
            int contAux = 0;
            istringstream iss(line);
            string aux;
            
            ruta[cont-1] = new int[sizeRuta(iss)];
            rutaOptima[cont-1] = new int[sizeRuta(iss)];
            istringstream set(line);
            while(getline (set, aux, ' ')){
                ruta[cont-1][contAux] = stoi(aux);
                ++contAux;
            };
            
        }
        ++cont;
        
    }
    domicilios.close();
    
    for (int i=0; i<domiciliarios; ++i) {
        inicio[i] = ruta[i][0];
    }
    
    for (int j=0; j<domiciliarios; ++j) {
        vector<int> min_distance;
        vector<int> previous;
        cout<<"Recorrido domiciliario No. "<<j+1<<":\t";
        do {
            if (ruta[j][0] == inicio[j]) {
                int weightRuta = 0;
                
                for (int i=1; i<=sizeof(ruta[j])/sizeof(int); ++i) {
                    DijkstraComputePaths(ruta[j][i-1], adjacency_list, min_distance, previous);
                    weightRuta += min_distance[ruta[0][i]];
                }
                for (int i=(sizeof(ruta[j])/sizeof(int))-1; i>=0; --i) {
                    DijkstraComputePaths(ruta[j][i+1], adjacency_list, min_distance, previous);
                    weightRuta += min_distance[ruta[j][i]];
                }
                
                if (weightRuta <= rutaMenor) {
                    rutaMenor = weightRuta;
                    for (int i=0; i<=sizeof(ruta[j])/sizeof(int); ++i) {
                        rutaOptima[j][i] = ruta[j][i];
                    }
                }
                
            }
        } while ( next_permutation(ruta[j],ruta[j]+3) );
        
        for (int i=0; i<=sizeof(rutaOptima[j])/sizeof(int); ++i) {
            cout<<rutaOptima[j][i]<<"\t";
        }
        cout<<endl<<"Distancia recorrida total = "<<rutaMenor<<endl<<endl;
        for (int i=1; i<=sizeof(rutaOptima[j])/sizeof(int); ++i) {
            
            DijkstraComputePaths(rutaOptima[j][i-1], adjacency_list, min_distance, previous);
            
            //el 4 que se usa en min_distance[4] es el destino
            cout << "from "<<rutaOptima[j][i-1]<<" to "<<rutaOptima[j][i]<<": ";
            
            //aqui tambien el 4 es el destino
            list<int> path = DijkstraGetShortestPathTo(rutaOptima[j][i], previous);
            copy(path.begin(), path.end(), ostream_iterator<int>(cout, " "));
            cout << endl;
            
        }
        for (int i=(sizeof(ruta[j])/sizeof(int))-1; i>=0; --i) {
            DijkstraComputePaths(rutaOptima[j][i+1], adjacency_list, min_distance, previous);
            
            //el 4 que se usa en min_distance[4] es el destino
            cout << "from "<<rutaOptima[j][i+1]<<" to "<<rutaOptima[j][i]<<": ";
            
            //aqui tambien el 4 es el destino
            list<int> path = DijkstraGetShortestPathTo(rutaOptima[j][i], previous);
            copy(path.begin(), path.end(), ostream_iterator<int>(cout, " "));
            cout << endl;
            
        }
        cout<<endl<<"--------------------------------------------"<<endl<<endl;
    }
    
    return 0;
}







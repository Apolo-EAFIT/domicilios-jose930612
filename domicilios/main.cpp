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
    /*
    for (int i=0; i<domiciliarios; ++i) {
        cout<<"Domiciliario No. "<<i+1<<endl;
        for (int j=0; j<=sizeof(ruta[i])/sizeof(int); ++j) {
            cout<<ruta[i][j]<<"\t";
        }
        cout<<endl;
    }
    */
    
    for (int i=0; i<domiciliarios; ++i) {
        inicio[i] = ruta[i][0];
    }
    
    
    vector<int> min_distance;
    vector<int> previous;
    /*
    for (int j=0; j<domiciliarios; ++j) {
        <#statements#>
    }
    */
    do {
        if (ruta[0][0] == inicio[0]) {
            int weightRuta = 0;
            //cout << ruta[0][0] << "\t" << ruta[0][1] << "\t" << ruta[0][2] << '\n';
            
            for (int i=1; i<=sizeof(ruta[0])/sizeof(int); ++i) {
                DijkstraComputePaths(ruta[0][i-1], adjacency_list, min_distance, previous);
                weightRuta += min_distance[ruta[0][i]];
                
                //el 4 que se usa en min_distance[4] es el destino
                //cout << "-Distance from "<<ruta[0][i-1]<<" to "<<ruta[0][i]<<": " << min_distance[ruta[0][i]] << endl;
                /*
                //aqui tambien el 4 es el destino
                list<int> path = DijkstraGetShortestPathTo(ruta[0][i], previous);
                cout << "Path : ";
                copy(path.begin(), path.end(), ostream_iterator<int>(cout, " "));
                cout << endl;
                */
            }
            for (int i=(sizeof(ruta[0])/sizeof(int))-1; i>=0; --i) {
                DijkstraComputePaths(ruta[0][i+1], adjacency_list, min_distance, previous);
                weightRuta += min_distance[ruta[0][i]];
                
                //el 4 que se usa en min_distance[4] es el destino
                //cout << "-Distance from "<<ruta[0][i+1]<<" to "<<ruta[0][i]<<": " << min_distance[ruta[0][i]] << endl;
                /*
                //aqui tambien el 4 es el destino
                list<int> path = DijkstraGetShortestPathTo(ruta[0][i], previous);
                cout << "Path : ";
                copy(path.begin(), path.end(), ostream_iterator<int>(cout, " "));
                cout << endl;
                 */
            }
            //cout<<"Distancia recorrida total = "<<weightRuta<<endl<<endl;
            if (weightRuta <= rutaMenor) {
                rutaMenor = weightRuta;
                for (int i=0; i<=sizeof(ruta[0])/sizeof(int); ++i) {
                    rutaOptima[0][i] = ruta[0][i];
                }
            }
            
        }
    } while ( next_permutation(ruta[0],ruta[0]+3) );
    
    
    
    cout<<"Distancia recorrida total = "<<rutaMenor<<endl<<endl;
    for (int i=1; i<=sizeof(rutaOptima[0])/sizeof(int); ++i) {
        //cout<<rutaOptima[0][i]<<"\t";
        DijkstraComputePaths(rutaOptima[0][i-1], adjacency_list, min_distance, previous);
        
        //el 4 que se usa en min_distance[4] es el destino
        cout << "from "<<rutaOptima[0][i-1]<<" to "<<rutaOptima[0][i]<<": " /*min_distance[rutaOptima[0][i]] << */;
        
         //aqui tambien el 4 es el destino
         list<int> path = DijkstraGetShortestPathTo(rutaOptima[0][i], previous);
         copy(path.begin(), path.end(), ostream_iterator<int>(cout, " "));
         cout << endl;
        
    }
    for (int i=(sizeof(ruta[0])/sizeof(int))-1; i>=0; --i) {
        DijkstraComputePaths(rutaOptima[0][i+1], adjacency_list, min_distance, previous);
        
        //el 4 que se usa en min_distance[4] es el destino
        cout << "from "<<rutaOptima[0][i+1]<<" to "<<rutaOptima[0][i]<<": " /*min_distance[rutaOptima[0][i]] << */;
        
         //aqui tambien el 4 es el destino
         list<int> path = DijkstraGetShortestPathTo(rutaOptima[0][i], previous);
         copy(path.begin(), path.end(), ostream_iterator<int>(cout, " "));
         cout << endl;
         
    }
    cout<<endl;
    
    
    /*
    for (int i=0; i<domiciliarios; ++i) {
        DijkstraComputePaths(ruta[i][0], adjacency_list, min_distance, previous);
        
        //el 4 que se usa en min_distance[4] es el destino
        cout << "Distance from "<<ruta[i][0]<<" to "<<ruta[i][1]<<": " << min_distance[ruta[i][1]] << endl;
        
        //aqui tambien el 4 es el destino
        list<int> path = DijkstraGetShortestPathTo(ruta[i][1], previous);
        cout << "Path : ";
        copy(path.begin(), path.end(), ostream_iterator<int>(cout, " "));
        cout << endl << endl;
    }
     */
    /*
    vector<int> min_distance;
    vector<int> previous;
    
    //el cero que se pasa en esta funcion es el origen
    DijkstraComputePaths(0, adjacency_list, min_distance, previous);
    
    //el 4 que se usa en min_distance[4] es el destino
    cout << "Distance from 0 to 4: " << min_distance[4] << endl;
    
    //aqui tambien el 4 es el destino
    list<int> path = DijkstraGetShortestPathTo(4, previous);
    cout << "Path : ";
    copy(path.begin(), path.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    */
    return 0;
}







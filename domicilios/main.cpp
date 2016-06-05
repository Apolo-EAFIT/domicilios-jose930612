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
    
    adjacency_list_t adjacency_list(E);
    
    
    fstream arcos("medellin_arcos.txt", ios::in);
    
    while (getline (arcos,line)) {
        if (cont > 0) {
            adjacency_list[nodos(line).origen].push_back(neighbor(nodos(line).destino, nodos(line).weight));
        }
        ++cont;
    }
    arcos.close();
    
    
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
    
    return 0;
}







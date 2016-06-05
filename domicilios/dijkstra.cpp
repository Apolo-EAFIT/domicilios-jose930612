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

void DijkstraComputePaths(int source, const adjacency_list_t &adjacency_list, vector<int> &min_distance, vector<int> &previous){
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    set<pair<int, int> > vertex_queue;
    vertex_queue.insert(make_pair(min_distance[source], source));
    
    while (!vertex_queue.empty()){
        int dist = vertex_queue.begin()->first;
        int u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());
        
        // Visit each edge exiting u
        const vector<neighbor> &neighbors = adjacency_list[u];
        for (vector<neighbor>::const_iterator neighbor_iter = neighbors.begin(); neighbor_iter != neighbors.end(); neighbor_iter++){
            int v = neighbor_iter->target;
            int weight = neighbor_iter->weight;
            int distance_through_u = dist + weight;
            
            if (distance_through_u < min_distance[v]) {
                vertex_queue.erase(make_pair(min_distance[v], v));
                
                min_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.insert(make_pair(min_distance[v], v));
            }
        }
    }
}


list<int> DijkstraGetShortestPathTo(int vertex, const vector<int> &previous){
    list<int> path;
    for ( ; vertex != -1; vertex = previous[vertex])
    path.push_front(vertex);
    return path;
}
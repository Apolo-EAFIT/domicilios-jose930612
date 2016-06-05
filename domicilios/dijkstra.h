#pragma once

#include <limits>
#include <vector>
#include <list>

using namespace std;

struct neighbor {
    int target;
    int weight;
    neighbor(int arg_target, int arg_weight) : target(arg_target), weight(arg_weight) {}
};

typedef vector<vector<neighbor> > adjacency_list_t;


const int max_weight = numeric_limits<double>::infinity();

void DijkstraComputePaths(int source, const adjacency_list_t &adjacency_list, vector<int> &min_distance, vector<int> &previous);

list<int> DijkstraGetShortestPathTo(int vertex, const vector<int> &previous);
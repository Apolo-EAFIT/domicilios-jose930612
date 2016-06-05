#pragma once
#include <stdio.h>

using namespace std;

struct Edge{
    int origen;
    int destino;
    int weight;
};


int archsSize ();
int edgesSize ();
Edge nodos (string line);

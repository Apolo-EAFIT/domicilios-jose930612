#pragma once
#include <stdio.h>
#include <sstream>

using namespace std;

struct Edge{
    int origen;
    int destino;
    int weight;
};

int archsSize ();
int edgesSize ();
int sizeRuta(istringstream &line);
Edge nodos (string line);

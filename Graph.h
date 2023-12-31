#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "LinkedList.h"
#include <fstream>
#include <sstream>

using namespace std;

class Graph{
    private:
        int V; // # of vertices
        int E; // # of edges

        vector<string> labelOfNodes; // array of labels of nodes

        unordered_map<int, LinkedList> adjList;

    public:
        //constructors
        Graph(string files[]); // [cities&codes, cities&adjCities, cities&costs]

        //copy constructor
        //Graph(const Graph& G);

        //destructor
        //~Graph();

        // -------- Methods ---------
        bool adjacent(int, int);
        Node* adjacentVertex(int, int);
        LinkedList neighbors(int);
        //bool add_vertex(int); // for file reading 
        //bool remove_vertex(int); // for file reading
        bool add_edge(int, int);
        bool remove_edge(int, int);
        //int get_vertex_value(int); no need
        int getV();
        int getE();
        string toString(int code);
        int get_edge_value(int, int);
        bool set_edge_value(int, int, int);
        bool set_edge_value(Node*, int);
        friend ostream& operator<<(ostream&, const Graph&);
};

#endif
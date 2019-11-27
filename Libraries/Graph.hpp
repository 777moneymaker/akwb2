#ifndef AKWB2_GRAPH_HPP
#define AKWB2_GRAPH_HPP

#include <iostream>
#include <vector>
#include "Vertex.hpp"

using namespace std;

class Graph{
private:
   int treshold, quality;
   vector<vector<Vertex> > sequences_vertices;
   vector<vector<char> > sequences;
   vector<vector<int> > qualities;

   void readQualities();

   void readSequence();

   void createSubstrings();

public:
   explicit Graph(int treshold = 4, int quality = 15);

   void printSequence();

   void printQualities();

   void printSubstrings();
};


#endif

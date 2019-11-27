#include <iostream>
#include <fstream>
#include <tuple>
#include "Libraries/Vertex.hpp"
#include "Graph.hpp"

using namespace std;


int main(){
   auto *G = new Graph();
   G->printSequence();
   G->printQualities();
   return 0;
}

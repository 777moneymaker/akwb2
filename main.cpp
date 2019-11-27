#include <iostream>
#include <tuple>
#include "Graph.hpp"

using namespace std;


int main(){
    auto *G = new Graph(6);
    G->printSubstrings();
    return 0;
}

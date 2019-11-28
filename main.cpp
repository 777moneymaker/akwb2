#include <iostream>
#include <tuple>
#include "Graph.hpp"

using namespace std;


int main(){
    auto *G = new Graph(4, 20);
    G->printSubstrings();
    return 0;
}

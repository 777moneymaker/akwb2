#include <iostream>
#include "Vertex.hpp"

using namespace std;

Vertex::Vertex(string seq){
    this->seq = seq;
}

void Vertex::setSequence(string seq){
    this->seq = seq;
}

string Vertex::getSequence(){
    return this->seq;
}

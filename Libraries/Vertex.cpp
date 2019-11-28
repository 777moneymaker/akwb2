#include <iostream>
#include <vector>
#include "Vertex.hpp"

using namespace std;

Vertex::Vertex(string seq, vector<int> qual_list){
    this->seq = seq;
    this->qual_list = qual_list;
}

void Vertex::setSequence(string seq){
    this->seq = seq;
}

string Vertex::getSequence(){
    return this->seq;
}

vector<int> Vertex::getQualities(){
    return this->qual_list;
}

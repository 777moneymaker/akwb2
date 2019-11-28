#include <iostream>
#include <vector>
#include "Vertex.hpp"

using namespace std;

Vertex::Vertex(string sequence, vector<int> qual, int number){
    this->seq = sequence;
    this->qual_list = qual;
    this->seq_number = number;
}

Vertex* Vertex::getSelf(){
    return this;
}

bool Vertex::doesMatch(string sequence){
    if(this->seq.size() not_eq sequence.size()){
        return false;
    }else{
        return this->seq == sequence;
    }
}

bool Vertex::doesMatchWithMiss(string sequence){
    int count = 0;
    for(int i = 0; i < sequence.size(); i++){
        if(this->seq[i] == sequence[i])
            count++;
    }
    return count >= seq.size() - 1;
}

void Vertex::setSequence(string sequence){
    this->seq = sequence;
}

string Vertex::getSequence(){
    return this->seq;
}

vector<int> Vertex::getQualities(){
    return this->qual_list;
}

int Vertex::getSeqNumber(){
    return this->seq_number;
}

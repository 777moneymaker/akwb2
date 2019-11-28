#include <iostream>
#include <vector>
#include "Vertex.hpp"
#include "Graph.hpp"

using namespace std;

Vertex::Vertex(string sequence, vector<int> qual, int number, int q){
    this->seq = sequence;
    this->qual_list = qual;
    this->seq_number = number;
    this->quality = q;

}

Vertex* Vertex::getSelf(){
    return this;
}

Vertex* Vertex::searchForMutations(){
    string temp_seq = this->seq;
    int min = 40;
    int min_index = 0;
    for(int i = 0; i < this->qual_list.size(); i++){
        if(this->qual_list[i] < min){
            min = this->qual_list[i];
            min_index = i;
        }
    }
    if(this->qual_list[min_index] < this->quality){
        temp_seq[min_index] = '_';
    }
    cout<<temp_seq << " ";
    return new Vertex(temp_seq, this->getQualities(), this->getSeqNumber());
}

bool Vertex::doesMatch(string sequence){
    if(this->seq.size() not_eq sequence.size()){
        return false;
    }else{
        return this->seq == sequence;
    }
}

bool Vertex::doesMatchWithErrors(string sequence){
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

#include <iostream>
#include <vector>
#include <algorithm>
#include "Vertex.hpp"

using namespace std;

Vertex::Vertex(string sequence, int pos, vector<int> qual, int number, int q, int tresh){
    this->seq = sequence;
    this->seq_del = sequence;
    this->position = pos;
    this->qual_list = qual;
    this->seq_number = number;
    this->quality = q;
    this->treshhold = tresh;
    this->mutateVertex();

}

Vertex *Vertex::getSelf(){
    return this;
}

void Vertex::mutateVertex(){
    string temp_seq = this->seq;
    if(this->treshhold > 5){
        for(int i = 0; i < this->seq.size(); i++){
            if(this->qual_list[i] < this->quality){
                temp_seq[i] = '_';
            }
        }
        this->seq_del = temp_seq;
        return void();
    }else{
        int min = 40;
        int min_index = 0;
        int count = 0;
        for(int i = 0; i < this->seq.size(); i++){
            for(int j = 0; j < this->qual_list.size(); j++){
                if(count == 1)
                    return void();
                min_index = 0;
                min = 40;
                if(this->qual_list[i] < min){
                    min = this->qual_list[i];
                    min_index = i;
                }
            }
            if(this->qual_list[min_index] < this->quality){
                temp_seq[min_index] = '_';
                count++;
                this->qual_list.erase(find(this->qual_list.begin(), this->qual_list.end(), min));
            }
            if(temp_seq not_eq this->seq_del){
                this->seq_del = temp_seq;
            }
        }
    }
    return void();
}

void Vertex::setSequence(string sequence){
    this->seq = sequence;
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
    for(int i = 0; i < (int)sequence.size(); i++){
        if(this->seq_del[i] == sequence[i]){
            count++;
        }
    }
    return count >= seq.size() - 1;
}

string Vertex::getSequence(){
    return this->seq;
}

string Vertex::getDelSequence(){
    return this->seq_del;
}

vector<int> Vertex::getQualities(){
    return this->qual_list;
}

int Vertex::getSeqNumber(){
    return this->seq_number;
}

int Vertex::getPosition(){
    return this->position;
}
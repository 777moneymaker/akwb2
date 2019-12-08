#include <iostream>
#include <vector>
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

int Vertex::getSeqNumber(){
    return this->seq_number;
}

int Vertex::getPosition(){
    return this->position;
}

bool Vertex::getComparsionStatus(){
    return this->compared_as_mutated;
}

bool Vertex::doesMatch(string sequence){
    return this->seq == sequence;
}

bool Vertex::doesMatchWithErrors(string sequence){
    int count = 0;
    for(int i = 0; i < (int)sequence.size(); i++){
        if(this->seq_del[i] == sequence[i] or this->seq_del[i] == 'X' or sequence[i] == 'X'){
            count++;
        }
    }
    return this->treshhold > 5 ? count >= seq.size() - 2 : count >= seq.size() - 1;
}

string Vertex::getSequence(){
    return this->seq;
}

string Vertex::getDelSequence(){
    return this->seq_del;
}

void Vertex::mutateVertex(){
    string temp_seq = this->seq;
    int min_index = 0, min = 0, count = 0;
    if(this->treshhold > 5){
        count = 0;
        for(int i = 0; i < (int)this->seq.size(); i++){
            min = this->quality, min_index = -1;
            for(int j = 0; j < (int)this->qual_list.size(); j++){
                if(count == 2)
                    break;
                if(this->qual_list[j] < min){
                    min = this->qual_list[j];
                    min_index = j;
                    this->qual_list[j] = 100;
                }
            }
            if(count == 2)
                break;
            if(min_index == -1)
                continue;
            temp_seq[min_index] = 'X';
            count++;

        }
        this->seq_del = temp_seq;
        return void();
    }else{
        count = 0;
        for(int i = 0; i < (int)this->seq.size(); i++){
            min = this->quality, min_index = 0;
            for(int j = 0; j < (int)this->qual_list.size(); j++){
                if(count)
                    break;
                if(this->qual_list[j] < min){
                    min = this->qual_list[j];
                    min_index = j;
                    this->qual_list[j] = 100;
                }
            }
            if(count)
                break;
            temp_seq[min_index] = 'X';
            count++;
        }
    }
    this->seq_del = temp_seq;
    return void();
}

void Vertex::setComparsion(bool cmp){
    this->compared_as_mutated = cmp;
}
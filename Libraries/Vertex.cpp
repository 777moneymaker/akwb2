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

void Vertex::setComparsion(bool cmp){
    this->compared_as_mutated = cmp;
}

bool Vertex::getComparsionStatus(){
    return this->compared_as_mutated;
}

void Vertex::mutateVertex(){
    string temp_seq = this->seq;
    int min_index = 0, min = 40, count = 0;
    if(this->treshhold > 5){
        count = 0;
        for(int i = 0; i < (int)this->seq.size(); i++){
            min = 40, min_index = 0;
            for(int j = 0; j < (int)this->seq.size(); j++) {
                if(count == 2)
                    return void();
                if(this->qual_list[i] < min) {
                    min = this->qual_list[i];
                    min_index = i;
                }
            }
            if((this->qual_list[min_index] < this->quality) and temp_seq[min_index] != 'X'){
                temp_seq[min_index] = 'X';
                count++;
                this->qual_list.erase(find(this->qual_list.begin(), this->qual_list.end(), min));
            }
        }
        this->seq_del = temp_seq;
        return void();
    }else{
        count = 0;
        for(int i = 0; i < (int)this->seq.size(); i++){
            min = 40, min_index = 0;
            for(int j = 0; j < (int)this->qual_list.size(); j++){
                if(count == 1)
                    return void();
                if(this->qual_list[i] < min){
                    min = this->qual_list[i];
                    min_index = i;
                }
            }
            if(this->qual_list[min_index] < this->quality){
                temp_seq[min_index] = 'X';
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

bool Vertex::doesMatch(string sequence){
    return this->seq == sequence;
}

bool Vertex::doesMatchWithErrors(string sequence){
    int count = 0;
    for(int i = 0; i < (int)sequence.size(); i++){
        if(this->seq_del[i] == sequence[i]){
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

int Vertex::getSeqNumber(){
    return this->seq_number;
}

int Vertex::getPosition(){
    return this->position;
}
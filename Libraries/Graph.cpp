//
// Created by Miłosz Chodkowski on 27/11/2019.
//

#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

Graph::Graph(int t, int q, string f_file, string q_file){
    this->treshhold = t;
    this->quality = q;
    this->fasta_file = f_file;
    this->qual_file = q_file;
    this->readSequence();
    this->readQualities();
    this->createSubstrings();
}

void Graph::alignSequences(){
    int size = this->vertices.size();
    vector<vector<int> > matrix(size);
    for(auto &line : matrix){
        line.resize(size, 0);
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i == j)
                continue;
            if(this->vertices[i].doesMatch(vertices[j].getSequence())){
                matrix[i][j] = 1;
                matrix[j][i] = 1;
            }
        }
    }
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            if(i == j)
                continue;
            if(this->vertices[i].doesMatchWithErrors(this->vertices[j].getDelSequence())){
                this->vertices[j].setComparsion(true);
                matrix[i][j] = 1;
                matrix[j][i] = 1;
            }
        }
    }
    int index = 0, val = 1;
    vector<Vertex> current_clique, best_clique;

    for(int i = 0; i < size; i++){
        current_clique.clear();
        index = 0, val = 1;
        // upper side of matrix
        for(int j = 0; j < size; j++){
            if(i == j)
                continue;
            if(matrix[i][j] == 1){
                if(this->vertices[index].getSeqNumber() != this->vertices[j].getSeqNumber()){
                    index = j;
                    if(val == 1){
                        current_clique.push_back(this->vertices[i]);
                        val++;
                    }
                    matrix[i][j] = numeric_limits<int>::max(); // set to infinity (int max number)
                    current_clique.push_back(this->vertices[j]);

                }
            }
            if(current_clique.size() > best_clique.size()){
                best_clique = current_clique;
            }
        }
    }


    cout << endl << "CLIQUE: " << endl;
    for(auto &c : best_clique){
        if(c.getComparsionStatus()) {
            cout << c.getDelSequence();
        }else{
            cout << c.getSequence();
        }
        cout << " seq no.: " << c.getSeqNumber()
             << " pos: " << c.getPosition() << endl;
    }

    fstream file("output.txt", ios::out);
    for(int i = 0; i < (int)best_clique.size(); i++){
        for(int j = 0; j < (int)this->sequences[i].size(); j++){
            if(j == best_clique[i].getPosition() - 1){
                file << "   ";
            }
            if(j == best_clique[i].getPosition() - 1 + this->treshhold){
                file << "   ";
            }
            file << this->sequences[i][j];
        }
        file << endl;
    }
}

void Graph::createSubstrings(){
    try{
        vector<char> base_stack;
        vector<int> qual_stack;
        string seq;
        vector<int> v_qualities;
        int pos;
        for(int i = 0; i < (int)this->sequences.size(); i++){
            pos = 1;
            base_stack.clear();
            qual_stack.clear();
            //this->sequences_vertices.emplace_back(vector<Vertex>());
            for(auto &c : this->sequences[i]){
                base_stack.push_back(c);
            }
            for(auto &q: this->qualities[i]){
                qual_stack.push_back(q);
            }
            while(not(base_stack.empty())){
                if(base_stack.size() < Graph::treshhold or qual_stack.size() < Graph::treshhold){
                    break;
                }
                for(int j = 0; j < this->treshhold; j++){
                    seq.push_back(base_stack[j]);
                    v_qualities.push_back(qual_stack[j]);
                }
                this->vertices.emplace_back(seq, pos, v_qualities, i + 1, this->getQuality(), this->getTreshhold());
                pos++;
                //this->vertices.push_back(new Vertex(seq, v_qualities, i + 1, this->getQuality()));
                seq = "";
                v_qualities.clear();
                qual_stack.erase(qual_stack.begin());
                base_stack.erase(base_stack.begin());
            }
        }
    } catch(exception &e){
        cerr << e.what();
    }
}

void Graph::readQualities(){
    fstream file("qualities.qual", ios::in);
    string single_quality;
    int row = -1;
    while(!file.eof()){
        file >> single_quality;
        if(single_quality == ">"){
            this->qualities.emplace_back(vector<int>());
            row++;
        }else{
            this->qualities[row].push_back(stoi(single_quality));
        }
    }
}

void Graph::readSequence(){
    string base;
    int row = -1;
    fstream file("sample.fasta", ios::in);
    while(!file.eof()){
        file >> base;
        if(base[0] == '>'){
            this->sequences.emplace_back(vector<char>());
            row++;
            continue;
        }else{
            for(auto c : base){
                this->sequences[row].push_back(c);
            }
        }
    }
}

int Graph::getQuality(){
    return quality;
}

int Graph::getTreshhold(){
    return this->treshhold;
}
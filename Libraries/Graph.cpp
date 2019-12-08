/***
 *      _____ _____ _____                                                 _
 *     |___  |___  |___  | __ ___   ___  _ __   ___ _   _ _ __ ___   __ _| | _____ _ __
 *        / /   / /   / / '_ ` _ \ / _ \| '_ \ / _ \ | | | '_ ` _ \ / _` | |/ / _ \ '__|
 *       / /   / /   / /| | | | | | (_) | | | |  __/ |_| | | | | | | (_| |   <  __/ |
 *      /_/   /_/   /_/ |_| |_| |_|\___/|_| |_|\___|\__, |_| |_| |_|\__,_|_|\_\___|_|
 *                                                  |___/
 */
#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

Graph::Graph(int t, int q, string f_file, string q_file){
    this->treshhold = t;
    this->quality = q;
    this->readSequence();
    this->readQualities();
    this->createSubstrings();
}

int Graph::getQuality(){
    return quality;
}

int Graph::getTreshhold(){
    return this->treshhold;
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
                matrix[i][j] = 1;
                matrix[j][i] = 1;
                this->vertices[j].setComparsion(true);
            }
        }
    }
    int index = 0, count = 1;
    vector<Vertex> current_clique, best_clique;

    for(int i = 0; i < size; i++){
        current_clique.clear();
        index = 0;
        for(int j = 0; j < size; j++){
            if(i == j)
                continue;
            if(matrix[i][j] == 1){
                if(this->vertices[index].getSeqNumber() != this->vertices[j].getSeqNumber()){
                    index = j;
                    if(count == 1){
                        current_clique.push_back(this->vertices[i]);
                        count++;
                    }
                    current_clique.push_back(this->vertices[j]);
                    matrix[i][j] = 0;

                }
            }
            if(current_clique.size() > best_clique.size()){
                best_clique = current_clique;
            }
        }
    }


    cout << endl << "CLIQUE: " << endl;
    for(auto &v : best_clique){
        if(v.getComparsionStatus()){
            cout << v.getDelSequence();
        }else{
            cout << v.getSequence();
        }
        cout << " seq no.: " << v.getSeqNumber()
             << " pos: " << v.getPosition() << endl;
    }

    fstream file("output.txt", ios::out);
    for(auto &v : best_clique){
        if(v.getComparsionStatus()){
            file << v.getDelSequence();
        }else{
            file << v.getSequence();
        }
        file << " seq no.: " << v.getSeqNumber()
             << " pos: " << v.getPosition() << endl;
    }
    file << endl;
    for(int i = 0; i < (int)best_clique.size(); i++){
        file << ">seq no. " << best_clique[i].getSeqNumber() << endl;
        for(int j = 0; j < (int)this->sequences[i].size(); j++){
            if(j == best_clique[i].getPosition() - 1){
                file << "___";
            }
            if(j == best_clique[i].getPosition() - 1 + this->treshhold){
                file << "___";
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
    string quality;
    int row = -1;
    while(!file.eof()){
        getline(file, quality);
        if(quality[0] == '>'){
            this->qualities.emplace_back(vector<int>());
            row++;
            continue;
        }else{
            stringstream ss(quality);
            int num;
            while(ss >> num){
                this->qualities[row].push_back(num);
            }
        }
    }
}

void Graph::readSequence(){
    string base;
    int row = -1;
    fstream file("sample.fasta", ios::in);
    while(!file.eof()){
        getline(file, base);
        if(base[0] == '>'){
            this->sequences.emplace_back(vector<char>());
            row++;
            continue;
        }else{
            for(auto c : base){
                if(c != ' ')
                    this->sequences[row].push_back(c);
            }
        }
    }
}
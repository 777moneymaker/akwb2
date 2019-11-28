//
// Created by Miłosz Chodkowski on 27/11/2019.
//

#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

Graph::Graph(int treshold, int quality){
    this->treshold = treshold;
    this->quality = quality;
    this->readSequence();
    this->readQualities();
    this->createSubstrings();
    this->connectVertices();
}

void Graph::printMatches(int seq_number){
    if(seq_number < 1 or seq_number > 7){
        cerr << "Wrong!";
        return;
    }
    cout << this->sequences_vertices[seq_number - 1][seq_number -1].getSequence() << " adj list: " << endl;
    for(auto &v : this->sequences_vertices[seq_number - 1][seq_number -1].adj_list){
        cout << v->getSequence() << " " << v->getSeqNumber() << " ";
    }
}

void Graph::connectVertices(){
    for(int i = 0; i < this->sequences_vertices.size(); i++){
        for(auto &v : this->sequences_vertices[i]){
            v.adj_list.clear();
            for(int j = 1; j < this->sequences_vertices.size(); j++){
                if(i == j)
                    continue;
                for(auto &x : this->sequences_vertices[j]){
                    if(v.doesMatch(x.getSequence())){
                        if(not(count(v.adj_list.begin(), v.adj_list.end(), &x))){
                            v.adj_list.push_back(x.getSelf());
                        }
                    }
                }
            }
        }
    }
}

void Graph::createSubstrings(){
    try{
        vector<char> base_stack;
        vector<int> qual_stack;
        string seq;
        vector<int> v_qualities;
        for(int i = 0; i < (int)this->sequences.size(); i++){
            base_stack.clear();
            qual_stack.clear();
            this->sequences_vertices.emplace_back(vector<Vertex>());
            for(auto &c : this->sequences[i]){
                base_stack.push_back(c);
            }
            for(auto &q: this->qualities[i]){
                qual_stack.push_back(q);
            }
            while(not(base_stack.empty())){
                if(base_stack.size() < treshold or qual_stack.size() < treshold){
                    break;
                }
                for(int j = 0; j < this->treshold; j++){
                    seq.push_back(base_stack[j]);
                    v_qualities.push_back(qual_stack[j]);
                }
                this->sequences_vertices[i].push_back(Vertex(seq, v_qualities, i + 1));
                seq = "";
                v_qualities.clear();
                qual_stack.erase(qual_stack.begin());
                base_stack.erase(base_stack.begin());
            }
        }
    }catch(exception &e){
        cerr << e.what();
    }
}

void Graph::printSubstrings(){
    for(auto &line : this->sequences_vertices){
        for(auto &v : line){
            cout << v.getSequence() << " ";
            for(auto &q : v.getQualities()){
                cout << q << " ";
            }
        }
        cout << endl;
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
        if(base == ">"){
            this->sequences.emplace_back(vector<char>());
            row++;
        }else{
            for(auto c : base){
                this->sequences[row].push_back(c);
            }
        }
    }
}

void Graph::printQualities(){
    for(const auto &line : this->qualities){
        for(const auto &qual : line){
            cout << qual << " ";
        }
        cout << endl;
    }
}

void Graph::printSequence(){
    for(const auto &line : this->sequences){
        for(const auto &base : line){
            cout << base << " ";
        }
        cout << endl;
    }
}
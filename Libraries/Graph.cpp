//
// Created by Miłosz Chodkowski on 27/11/2019.
//

#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

Graph::Graph(int treshold, int quality){
    this->treshold = treshold;
    this->quality = quality;
    this->readSequence();
    this->readQualities();
    this->createSubstrings();
}

void Graph::createSubstrings(){
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
            this->sequences_vertices[i].push_back(Vertex(seq, v_qualities));
            seq = "";
            v_qualities.clear();
            qual_stack.erase(qual_stack.begin());
            base_stack.erase(base_stack.begin());
        }
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
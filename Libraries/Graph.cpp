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
    vector<char> stack;
    string seq;
    for(int i = 0; i < (int)this->sequences.size(); i++){
        stack.clear();
        this->sequences_vertices.emplace_back(vector<Vertex>());
        for(auto &c : this->sequences[i]){
            stack.push_back(c);
        }
        while(not(stack.empty())){
            if(stack.size() < treshold)
                break;
            for(int j = 0; j < this->treshold; j++){
                seq.push_back(stack[j]);
            }
            this->sequences_vertices[i].push_back(Vertex(seq));
            seq = "";
            stack.erase(stack.begin());
        }
    }
}

void Graph::printSubstrings(){
    for(auto &line : this->sequences_vertices){
        for(auto &v : line){
            cout << v.getSequence() << " ";
        }
        cout << endl;
    }
}

void Graph::readQualities(){
    fstream file("qualities.txt", ios::in);
    string quality;
    int row = -1;
    while(!file.eof()){
        file >> quality;
        if(quality == ">"){
            this->qualities.emplace_back(vector<int>());
            row++;
        }else{
            this->qualities[row].push_back(stoi(quality));
        }
    }
}

void Graph::readSequence(){
    string base;
    string temp;
    int row = -1;
    fstream file("sample.txt", ios::in);
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
//
// Created by Miłosz Chodkowski on 27/11/2019.
//

#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <vector>

Graph::Graph() {
    this->readSequence();
    this->readQualities();
}

void Graph::readQualities() {
    fstream file("qualities.txt", ios::in);
    string quality;
    int row = -1;
    vector<vector<int> > temp_qualities, qualities;
    while(!file.eof()){
        file >> quality;
        if(quality == ">"){
            row++;
        }else{
            temp_qualities.emplace_back(vector<int>());
            temp_qualities[row].push_back(stoi(quality));
        }
    }
    for(int i = 0; i < temp_qualities.size(); i++){
        qualities.emplace_back(vector<int>());
        for(auto c : temp_qualities[i]){
            qualities[i].push_back(c);
        }
    }
    this->qualities = qualities;
}

void Graph::readSequence() {
    string base;
    int row = -1;
    vector<vector<string> > temp_sequence, sequences;
    fstream file("sample.txt", ios::in);
    while(!file.eof()){
        file >> base;
        if(base == ">"){
            row++;
        }else{
            temp_sequence.emplace_back(vector<string>());
            temp_sequence[row].push_back(base);
        }
    }
    for(int i = 0; i < temp_sequence.size(); i++){
        sequences.emplace_back(vector<string>());
        for(auto &c : temp_sequence[i]){
            sequences[i].push_back(c);
        }
    }
    this->sequences = sequences;
}

void Graph::printQualities() {
    for(const auto &line : this->qualities){
        for(const auto &qual : line){
            cout << qual << " ";
        }
        cout<<endl;
    }
}

void Graph::printSequence() {
    for(const auto &line : this->sequences){
        for(const auto &base : line){
            cout << base << " ";
        }
        cout<<endl;
    }
}
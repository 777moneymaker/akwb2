#ifndef AKWB2_GRAPH_HPP
#define AKWB2_GRAPH_HPP

#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    vector<vector<string> > sequences;
    vector<vector<int> > qualities;
    void readQualities();
    void readSequence();
public:
    explicit Graph();
    void printSequence();
    void printQualities();
};


#endif

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <vector>

using namespace std;

class Vertex{
private:
    string seq = "0";
    vector<string> adj_list;

public:
    explicit Vertex(string seq="0");
    void setSequence(string seq);
    string getSequence();
};

#endif

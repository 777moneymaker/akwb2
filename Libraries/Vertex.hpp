#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <vector>

using namespace std;

class Vertex{
private:
   string seq = "0";
   int seq_number = 0;
   vector<int> qual_list;
public:
   vector<Vertex*> adj_list;

   explicit Vertex(string sequence = "0", vector<int> qual = vector<int>(0), int number=0);

   void setSequence(string sequence);

   bool doesMatch(string sequence);

   bool doesMatchWithMiss(string sequence);

   string getSequence();

   vector<int> getQualities();

   Vertex* getSelf();

   int getSeqNumber();
};

#endif

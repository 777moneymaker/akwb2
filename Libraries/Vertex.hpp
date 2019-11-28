#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <vector>

using namespace std;

class Vertex{
private:
   int quality = 0;
   int seq_number = 0;
   string seq = "0";
   vector<int> qual_list;
public:
   explicit Vertex(string sequence = "0", vector<int> qual = vector<int>(0), int number=0, int quality=20);

   vector<Vertex*> adj_list;

   vector<Vertex*> adj_list_with_errors;

   bool doesMatch(string sequence);

   bool doesMatchWithErrors(string sequence);

   void setSequence(string sequence);

   int getSeqNumber();

   string getSequence();

   vector<int> getQualities();

   Vertex* searchForMutations();

   Vertex* getSelf();


};

#endif

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <vector>

using namespace std;

class Vertex{
private:
   int quality = 0, treshhold = 0, seq_number = 0, position = 0;
   string seq = "0";
   string seq_del;
   vector<int> qual_list;
public:
   explicit Vertex(string sequence = "0", int pos = 0, vector<int> qual = vector<int>(0), int number = 0,
                   int quality = 20, int tresh = 4);

   bool doesMatch(string sequence);

   bool doesMatchWithErrors(string sequence);

   void mutateVertex();

   int getSeqNumber();

   int getPosition();

   string getSequence();

   string getDelSequence();

};

#endif

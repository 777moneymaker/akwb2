/***
 *      _____ _____ _____                                                 _
 *     |___  |___  |___  | __ ___   ___  _ __   ___ _   _ _ __ ___   __ _| | _____ _ __
 *        / /   / /   / / '_ ` _ \ / _ \| '_ \ / _ \ | | | '_ ` _ \ / _` | |/ / _ \ '__|
 *       / /   / /   / /| | | | | | (_) | | | |  __/ |_| | | | | | | (_| |   <  __/ |
 *      /_/   /_/   /_/ |_| |_| |_|\___/|_| |_|\___|\__, |_| |_| |_|\__,_|_|\_\___|_|
 *                                                  |___/
 */
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <vector>

using namespace std;

class Vertex{
private:
   int quality = 0, treshhold = 0, seq_number = 0, position = 0;
   vector<int> qual_list;
   string seq = "", seq_del;
   bool compared_as_mutated = false;

public:
   explicit Vertex(string sequence = "0", int pos = 0, vector<int> qual = vector<int>(0), int number = 0,
                   int quality = 20, int tresh = 4);

   int getSeqNumber();

   int getPosition();

   bool doesMatch(string sequence);

   bool doesMatchWithErrors(string sequence);

   bool getComparsionStatus();

   string getSequence();

   string getDelSequence();

   void mutateVertex();

   void setComparsion(bool cmp);
};

#endif

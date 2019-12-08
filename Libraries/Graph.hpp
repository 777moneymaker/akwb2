/***
 *      _____ _____ _____                                                 _
 *     |___  |___  |___  | __ ___   ___  _ __   ___ _   _ _ __ ___   __ _| | _____ _ __
 *        / /   / /   / / '_ ` _ \ / _ \| '_ \ / _ \ | | | '_ ` _ \ / _` | |/ / _ \ '__|
 *       / /   / /   / /| | | | | | (_) | | | |  __/ |_| | | | | | | (_| |   <  __/ |
 *      /_/   /_/   /_/ |_| |_| |_|\___/|_| |_|\___|\__, |_| |_| |_|\__,_|_|\_\___|_|
 *                                                  |___/
 */
#ifndef AKWB2_GRAPH_HPP
#define AKWB2_GRAPH_HPP

#include <iostream>
#include <vector>
#include "Vertex.hpp"

using namespace std;

class Graph{
private:
   int treshhold, quality;
   vector<vector<char> > sequences;
   vector<vector<int> > qualities;
   vector<Vertex> vertices;

   void readQualities();

   void readSequence();

   void createSubstrings();

public:
   explicit Graph(int treshhold = 4, int quality = 15, string f_file = "sample1.fasta",
                  string q_file = "qualities1.qual");

   int getQuality();

   int getTreshhold();

   void alignSequences();
};


#endif

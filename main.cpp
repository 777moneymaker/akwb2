#include <iostream>
#include <tuple>
#include "Graph.hpp"

using namespace std;

int main(){
    // every file
    const vector<tuple<string, string> > file_names = {
            make_tuple("sample1.fasta", "qualities1.qual"),
            make_tuple("sample2.fasta", "qualities2.qual"),
            make_tuple("sample3.fasta", "qualities3.qual"),
            make_tuple("sample4.fasta", "qualities4.qual"),
            make_tuple("sample5.fasta", "qualities5.qual")
    };
    // align sequences for each file
    auto *G = new Graph(4, 30, "sample1.fasta", "qualities1.qual");
    G->alignSequences();
    delete G;

    //for(auto &tup : file_names){
    //}
    return 0;
}

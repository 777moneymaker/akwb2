/***
 *      _____ _____ _____                                                 _
 *     |___  |___  |___  | __ ___   ___  _ __   ___ _   _ _ __ ___   __ _| | _____ _ __
 *        / /   / /   / / '_ ` _ \ / _ \| '_ \ / _ \ | | | '_ ` _ \ / _` | |/ / _ \ '__|
 *       / /   / /   / /| | | | | | (_) | | | |  __/ |_| | | | | | | (_| |   <  __/ |
 *      /_/   /_/   /_/ |_| |_| |_|\___/|_| |_|\___|\__, |_| |_| |_|\__,_|_|\_\___|_|
 *                                                  |___/
 */
#include <iostream>
#include <tuple>
#include "Libraries/Graph.hpp"

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
    int quality, treshhold;
    try{
        cout << "What treshold [4, 7]?: " << endl;
        cin >> treshhold;
        if(not(cin.good())){
            throw invalid_argument("Wrong number!");
        }
        if(treshhold < 4 or treshhold > 7)
            throw invalid_argument("Wrong number!");
        cout << "What quality [1, 40]?: " << endl;\
        cin >> quality;
        if(not(cin.good())){
            throw invalid_argument("Wrong number!");
        }
        if(quality < 1 or quality > 40)
            throw invalid_argument("Wrong number!");
    } catch(exception &e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
    auto *G = new Graph(treshhold, quality, "sample1.fasta", "qualities1.qual");
    G->alignSequences();
    delete G;

    return 0;
}

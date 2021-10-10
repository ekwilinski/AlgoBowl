// AlgoBowl
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

int main(int argc, char** argv) {
    ifstream f;
    f.open("input.txt");

    string numElements;
    getline(f,numElements);
    string numSets;
    getline(f,numSets);

    map<set<int>,int> subsets;

    while(!f.eof()) {
        stringstream s;
        string line;
        getline(f,line);
        s << line;
        set<int> subset;

        while(!s.eof()) {
            string num;
            s >> num;
            subset.emplace(stoi(num));
        }

        getline(f,line);
        subsets.emplace(subset,stoi(line));

        
    }   
    f.close();

    map<int,vector<pair<double,set<int>>>> elementRatios;

    for(const auto &p : subsets) {
            for(const auto &s : p.first) {
                elementRatios[s].push_back(make_pair((double)(p.second)/p.first.size(),p.first));
            }
    }

    
    return 0;

}
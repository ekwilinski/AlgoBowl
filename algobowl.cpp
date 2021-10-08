// AlgoBowl
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
using namespace std;
int main() {
    ifstream f;

    f.open("input.txt");

    string numElements;
    f >> numElements;
    string numSets;
    f >> numSets;

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

        f >> line;
        subsets.emplace(subset,stoi(line));
    }   
    f.close();
    return 0;

}
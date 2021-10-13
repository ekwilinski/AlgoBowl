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

bool sortbysec(const tuple<set<int>,double>& a, const tuple<set<int>, double>& b)
{
    return (get<1>(a) < get<1>(b));
}

int main(int argc, char** argv) {
    ifstream f;
    f.open("inputs/input_group300.txt");

    string numElements;
    getline(f,numElements);
    string numSets;
    getline(f,numSets);

    map<int,tuple<set<int>,int>> subsets;
    int ID = 1;

    while(!f.eof()) {
        stringstream s;
        string line;
        getline(f,line);

        if(line != "") {
            s << line;
            set<int> subset;

            while(!s.eof()) {
                string num;
                s >> num;
                subset.emplace(stoi(num));
            }

            getline(f,line);
            subsets.emplace(ID,make_tuple(subset,stoi(line)));
            ID++;
        }   
    }
    f.close();

    int inputWeight = 59;
    string inputIDs = "52 13 27 46 53 61 41 15 2 6 14 28 58 11 17 51 12";
    vector<int> IDs;

    set<int> targetSet;
    for(int i = 1; i <= stoi(numElements); i++) {
        targetSet.emplace(i);
    }

    //split input ID's into vector of ints
    istringstream iss(inputIDs);
    string item;
    while (getline(iss, item, ' ')) {
        IDs.push_back(stoi(item));
    }

    //loop through the IDs and check if union equals full set
    set<int> unionTargetCheck;
    int weight = 0;
    for(int Id : IDs) {
        set<int> nextSet = get<0>(subsets[Id]);
        weight+= get<1>(subsets[Id]);
        set_union(unionTargetCheck.begin(), unionTargetCheck.end(), nextSet.begin(),nextSet.end(), inserter(unionTargetCheck, unionTargetCheck.begin()));
    }

    if(unionTargetCheck == targetSet) {
        cout << "Valid Union" << endl;
    }
    else {
        cout << "invalid Union" << endl;
    }

    if(weight == inputWeight) {
        cout << "Valid Weight";
    }
    else {
        cout << "invalid Weight";
    }

}
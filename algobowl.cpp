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
    f.open("inputs/input_group339.txt");

    string numElements;
    getline(f,numElements);
    string numSets;
    getline(f,numSets);

    map<set<int>,tuple<int,int,double>> subsets;
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
            subsets.emplace(subset,make_tuple(stoi(line),ID,(double)(stoi(line))/subset.size()));
            ID++;
        }   
    }
        f.close();

    //solutionSet is a set of tuples with (subset, weight)
    set<tuple<set<int>,int>> solutionSet;
    //unionSolutionSet keeps track of making sure we have selected all ints
    set<int> unionSolutionSet;
    //targetSet is the target set to build
    set<int> targetSet;
    for(int i = 1; i <= stoi(numElements); i++) {
        targetSet.emplace(i);
    }


    int totalWeight = 0;
    while(unionSolutionSet != targetSet) {
        auto it = min_element(subsets.begin(), subsets.end(),[](const auto& l, const auto& r) { return get<2>(l.second) < get<2>(r.second); });
        set<int> nextSet = it->first;
        solutionSet.emplace(make_tuple(it->first,get<1>(it->second)));
        totalWeight += get<0>(it->second);
        set_union(unionSolutionSet.begin(), unionSolutionSet.end(), nextSet.begin(),nextSet.end(), inserter(unionSolutionSet, unionSolutionSet.begin()));
        subsets.erase(it);

        //recalculate ratio based on new subset
        for( auto &p : subsets) {
            set<int> newElements;
            set_difference(p.first.begin(),p.first.end(),unionSolutionSet.begin(),unionSolutionSet.end(),inserter(newElements,newElements.begin()));
            double newSize = newElements.size();
            tuple<int,int,double> temp = make_tuple(get<0>(p.second),get<1>(p.second), get<0>(p.second) / newSize);
            p.second = temp;
        }
    }

    cout << totalWeight << endl;
    for( const auto &p : solutionSet) {
        cout << get<1>(p) << " ";
    }
    return 0;
//10+8+13+2+15+12+6+18+3 = 87 input_rand.txt validated
}
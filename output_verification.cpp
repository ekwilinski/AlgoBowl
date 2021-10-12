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
    f.open("inputs/input_group301.txt");

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

    int inputWeight = 757;
    string inputIDs = "246 424 96 240 92 383 489 228 295 171 187 29 120 402 167 445 464 486 341 84 148 147 328 406 4 351 307 128 62 453 57 63 336 1 196 98 303 200 169 11 168 444 138 401 85 107 133 237 90 174 204 329 215 312 256 385 229 276 67 279 158 481 377 250 499 466 271 386 342 418 274 376 182 454 149 452 140 17 288 459 180 175 483 179 38 399 316 41 163 104 275 417 500 415 319 371 282 326 176 227 35 477 9 197 378 258 259 460 3 261 437 369 78 135 235 166 231 70 30 498 233 375 374 420 291 488 206 350 408 345 451 165";
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
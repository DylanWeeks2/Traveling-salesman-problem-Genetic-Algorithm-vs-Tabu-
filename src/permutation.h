//DYLAN WEEKS, 47343235, LAB 4
#ifndef permutation_h
#define permutation_h
#include <iostream>
#include <vector>
#include "reader.h"

using namespace std;
using namespace std::chrono;

class permutation {
public:
    bool operator == (permutation &check);
    vector<int> cityPath;
    float totalCost = 0;

};

#endif /* permutation_h */

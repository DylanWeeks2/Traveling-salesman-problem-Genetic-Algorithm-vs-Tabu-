//DYLAN WEEKS, 47343235, LAB 4
#ifndef individual_h
#define individual_h
#include <iostream>
#include <vector>
#include "reader.h"

using namespace std;

class individual {
public:
    bool operator == (individual &check);
    vector<int> cityPath;
    float totalCost = 0;

};

#endif /* individual_h */

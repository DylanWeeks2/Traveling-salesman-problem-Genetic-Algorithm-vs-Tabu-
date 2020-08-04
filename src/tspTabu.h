//DYLAN WEEKS, 47343235, LAB 4
#ifndef tspTabu_h
#define tspTabu_h
#include <iostream>
#include <vector>
#include "reader.h"
#include "algorithm.h"
#include "permutation.h"

using namespace std;
using namespace std::chrono;

class tspTabu: public algorithm
{
public:
    virtual void execute(reader &r);
    void tabu(reader &r);
    permutation setBest(reader &r);
    virtual void output();
    
private:
    permutation finalBest;
    vector<int> path;
    int position = 0;
    vector<permutation> tabuList;
    double executionTime;
    vector<int> cityPath;
    float totalCost = 0;
};

#endif /* tspTabu_h */

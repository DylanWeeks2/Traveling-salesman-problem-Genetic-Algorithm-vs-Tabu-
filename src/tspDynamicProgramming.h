//DYLAN WEEKS, 47343235, LAB 4
#ifndef tspDynamicProgramming_h
#define tspDynamicProgramming_h
#include "algorithm.h"
#include <vector>

using namespace std;
using namespace std::chrono;

class tspDynamicProgramming : public algorithm
{
public:
    virtual void execute(reader &r);
    virtual void output();
    void dp(int sentCity);
    int recursiveCall(int sentCity);
private:
    double executionTime;
    float totalCost = 0;
    vector<vector<float>> distanceMatrix;
    vector<int> verticies;
    vector<int> visitedCities;
    vector<int> cityPath;
};

#endif /* tspDynamicProgramming_h */

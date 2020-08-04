//DYLAN WEEKS, 47343235, LAB 4
#ifndef tspBruteForce_h
#define tspBruteForce_h
#include "algorithm.h"
#include <vector>

using namespace std;
using namespace std::chrono;

class tspBruteForce : public algorithm
{
public:
    virtual void execute(reader &r);
    void tsp(int startCity);
    float addCurrCost(float cost1, float cost2);
    virtual void output();
private:
    vector<int> verticies;
    vector<int> finalPath;
    vector<int> tempPath;
    double executionTime;
    float totalCost = INT_MAX;
    vector<vector<float>> distanceMatrix;
    int start = 0;
    
};

#endif /* tspBruteForce_h */

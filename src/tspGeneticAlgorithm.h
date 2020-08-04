//DYLAN WEEKS, 47343235, LAB 4
#ifndef tspGeneticAlgorithm_h
#define tspGeneticAlgorithm_h
#include <iostream>
#include <vector>
#include "algorithm.h"
#include "reader.h"
#include "individual.h"

using namespace std;
using namespace std::chrono;

class tspGeneticAlgorithm:public algorithm
{
public:
    virtual void execute(reader &r);
    individual setBest(reader &r);
    void geneticAlgorithm(reader &r);
    bool empty(individual offspring);
    virtual void output();
    
private:
    vector<individual> population;
    vector<int> parents;
    int fitness = 0; //0 = ELITISM, 1 = ROULETTE WHEEL
    double executionTime = 0.0;
    vector<int> cityPath;
    float totalCost = 0;
    vector<int> pathOfOffspring;
    individual finalPerson;
    float tempCost = INT_MAX;
    int mutation = 0; //0 = RANDOM MUTATION, 1 = ADJACENT MUTATION
    int crossover = 0; //0 = RANDOM CROSSOVER, 1 = CYCLIC CROSSOVER
};

#endif /* tspGeneticAlgorithm_h */

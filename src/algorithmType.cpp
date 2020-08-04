//DYLAN WEEKS, 47343235, LAB 4
#include <stdio.h>
#include "algorithmType.h"
#include "tspBruteForce.h"
#include "tspDynamicProgramming.h"
#include "algorithm.h"
#include "tspTabu.h"
#include "tspGeneticAlgorithm.h"


//SAME STRUCTURE AS I IMPLEMENTED IN LAB 3 BUT ADDED THE NEXT TWO ALGORITHMS
algorithm* algorithmType::type(int s)
{
    //CREATES ALL THE ALGOS THEN RUNS IF ELSE STATEMENTS
    algorithm *algo1 = new tspBruteForce();
    algorithm *algo2 = new tspDynamicProgramming();
    algorithm *algo3 = new tspTabu();
    algorithm *algo4 = new tspGeneticAlgorithm();
    
    if(s == 0)
    {
        return algo1;
    }
    else if(s == 1)
    {
        return algo2;
    }
    else if(s == 2)
    {
        return algo3;
    }
    else
    {
        return algo4;
    }
    
    //NEVER REACHES HERE
    return NULL;
}

//DYLAN WEEKS, 47343235, LAB 4
#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>
#include "reader.h"
#include "tspBruteForce.h"

using namespace std;
using namespace std::chrono;

void tspBruteForce::execute(reader &r)
{
    //SETS THE DISTANCE MATRIX PREVIOUSLY READ IN AND THE PATHS BASED ON NUMBER OF VERTICIES
    distanceMatrix =r.distanceMatrix;
    verticies = r.verticies;
    for(int i = 0; i < verticies.size(); i++)
    {
        tempPath.push_back(0);
        finalPath.push_back(0);
    }
    start = verticies[0];
    
    //CLOCKS THE TIME IT TAKES
    high_resolution_clock::time_point start = high_resolution_clock::now();
    tsp(verticies[0]);
    high_resolution_clock::time_point finish = high_resolution_clock::now();
    duration<double> timeSpan = duration_cast<duration<double>>(finish - start);
    executionTime = timeSpan.count();
}

void tspBruteForce::tsp(int startCity) // implement traveling Salesman Problem.
{
    //ERASES THE START CITY FROM VERTEX VECTOR
    verticies.erase(remove(verticies.begin(), verticies.end(), startCity), verticies.end());
    
    //HAVE TO DO A DO WHILE LOOP DUE TO THE NEXT_PERMUTATION STL LIBRARY FUNCTION
    do {
        //VALUE OF THE CURRENT CITY MIN
        float currCost = 0;
        int currCity = startCity;
        tempPath[0] = currCity;
        //SETS FIRST IN PATH TO THE START CITY
        
    
        for (int i = 0; i < verticies.size(); i++)
        {
            //UPDATES THE CURR COST BASED OF THE CURR CITY
            currCost = addCurrCost(currCost, distanceMatrix[currCity][verticies[i]]);
            
            
            //UPDATES CURR CITY TO NEXT CITY
            currCity = verticies[i];
            //ADDS TO TEMP PATH
            tempPath[i] = currCity;
            
        }
        //AFTER THE LOOPING OF CITIES, UPDATES CURR COST
        currCost = addCurrCost(currCost, distanceMatrix[currCity][startCity]);
        
        //CHECKS TO SEE IF TOTAL IS GREATER TAHN CURR AND IF SO UPDATE FINAL PATH AND COST
        if(totalCost > currCost)
        {
            totalCost = currCost;
            finalPath = tempPath;
        }
        
    }
    while (next_permutation(verticies.begin(), verticies.end()));
    //NEXT_PERMUTATION IS A STL LIBRARY TOOL THT I FOUND THAT ORDERS THE VERTICIES INTO THE NEXT LEXOGRAPHICALLY GREATER PERMUTATION OF THE VERTICIES, ALLOWS FOR N-1! OF THE ELEMENTS TO BE ARRANGED AND EXPLORED
}

float tspBruteForce::addCurrCost(float cost1, float cost2)
{
    //ADDS THE CURR COST UP
    return cost1 + cost2;
}

void tspBruteForce::output()
{
    //OUTPUT OF THE STATS OF THE PROGRAM
    cout << "**********************************************" << endl;
    cout << "****************TSP BRUTE FORCE***************" << endl;
    cout << "**********************************************" << endl;
    
    cout << "Execution Time = " << executionTime << " seconds" << endl;
    cout << "Shortest Distance = " << totalCost << endl;
    cout << "Shortest Path = ";
    cout << start + 1 << " -> ";
    for(int i = 0; i < finalPath.size(); i++)
    {
        if(i != finalPath.size() - 1)
        {
            cout << finalPath[i] + 1 << " -> ";
        }
        else
        {
            cout << finalPath[i] + 1 << endl;
        }
    }
    cout << endl;
}



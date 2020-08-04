//DYLAN WEEKS, 47343235, LAB 4
#include <stdio.h>
#include <iostream>
#include <vector>
#include "reader.h"
#include "tspDynamicProgramming.h"

using namespace std;
using namespace std::chrono;

void tspDynamicProgramming::execute(reader &r)
{
    //SETS THE DISTANCE MATRIX PREVIOUSLY READ IN AND THE PATHS BASED ON NUMBER OF VERTICIES
    distanceMatrix = r.distanceMatrix;
    verticies = r.verticies;
    for(int i = 0; i < verticies.size(); i++)
    {
        visitedCities.push_back(0);
    }
    
    //CLOCKS THE TIME IT TAKES
    high_resolution_clock::time_point start = high_resolution_clock::now();
    dp(verticies[0]);
    high_resolution_clock::time_point finish = high_resolution_clock::now();
    duration<double> timeSpan = duration_cast<duration<double>>(finish - start);
    executionTime = timeSpan.count();
}

int tspDynamicProgramming::recursiveCall(int sentCity)
{
    //SETS VALUES FOR THIS ITERATION OF RECURSIVE CALL
    float currentMin = 0;
    int nextCity = INT_MAX;
    float min = INT_MAX;
    

    for( int i = 0; i < verticies.size(); i++)
    {
        //CHECKS IF ALREADY VISITED
        if(visitedCities[i] == 0)
        {
            //CHECKS IF VALUE ISNT A VERTEX POINT IN DISTANCE MATRIX
            if(distanceMatrix[sentCity][i] > 0)
            {
                //CHECKS TO SEE IF DISTANCE VALUE IS LESS THAN THE MIN
                if(min > (distanceMatrix[i][sentCity] + distanceMatrix[sentCity][i]))
                {
                    //SETS THE NEXT MIN TO BE CHECKED
                    min = distanceMatrix[i][0] + distanceMatrix[sentCity][i];
                    
                    //SETS NEW CURRENT MINIMUM FORM THE SENT CITY
                    currentMin = distanceMatrix[sentCity][i];
                    
                    //SETS NEXT CIYT VALUE
                    nextCity = i;
                }
            }
        }
    }

    if(min != INT_MAX)
    {
        //SETS TOTAL COST VALUE
        totalCost = totalCost + currentMin;
    }

    //SENDS BACK SHORTEST PATH CITY VALUE
    return nextCity;
}

void tspDynamicProgramming::dp(int sentCity)
{
    int nextCity = 0;

    //SETS THE VALUE OF THE CURRENT CITY AS VISITED
    visitedCities[sentCity] = 1;

    //PUSHES BACK THE STARTING CITY OF CALL
    cityPath.push_back(sentCity + 1);
    
    //CALLS RECURSIVE FUNCTION TO GET VALUE OF NEXT CITY
    nextCity = recursiveCall(sentCity);

    if(nextCity == INT_MAX)
    {
        //PUSHES BACK VALUE OF NEXT CITY MEANING IT IS ON THE SHORTEST PATH
        nextCity = 0;
        
        
        //PUTS IN VECTOR WHICH HOLDS FINAL PATH
        cityPath.push_back(nextCity + 1);
        //ADDS TOGETHER THE TOTAL COST
        totalCost = totalCost + distanceMatrix[sentCity][nextCity];
        
        //RETURNS FROM RECURSIVE CALL IN THE FUNCTION DP
        return;
    }

    //RECALLS THIS FUNCTION AFTER FOUND SHORTEST PATH FROM PREVIOS SENT CITY
    dp(nextCity);
}

void tspDynamicProgramming::output()
{
    //OUTPUT OF THE STATS OF THE PROGRAM
    cout << "**********************************************" << endl;
    cout << "************TSP DYNAMIC PROGRAMMING***********" << endl;
    cout << "**********************************************" << endl;
    
    cout << "Execution Time = " << executionTime << " seconds" << endl;
    cout << "Shortest Distance = " << totalCost << endl;
    cout << "Shortest Path = ";
    for(int i = 0; i < cityPath.size(); i++)
    {
        if(i != cityPath.size() - 1)
        {
            cout << cityPath[i] << " -> ";
        }
        else
        {
            cout << cityPath[i] << endl;
        }
    }
    cout << endl;
}


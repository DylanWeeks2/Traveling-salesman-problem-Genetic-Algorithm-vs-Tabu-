//DYLAN WEEKS, 47343235, LAB 4
#include <iostream>
#include <vector>
#include "tspTabu.h"
#include "algorithm.h"
#include "reader.h"

using namespace std;
using namespace std::chrono;

void tspTabu::execute(reader &r)
{
    
    high_resolution_clock::time_point start = high_resolution_clock::now();
    tabu(r);
    high_resolution_clock::time_point finish = high_resolution_clock::now();
    duration<double> timeSpan = duration_cast<duration<double>>(finish - start);
    executionTime = timeSpan.count();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void tspTabu::tabu(reader &r)
{
    //CREATES PERMUTATION
    permutation BestPermutation = setBest(r);
    
    //TABULIST CREATED
    tabuList.push_back(BestPermutation);
     
    //CHECKS IF THE MOVE IS CONSIDERED TABU
    //SETS TOTAL NUMBER OF PERMUTATIONS ALLOWED TO MAX PERMUTATIONS (CHANGE THIS FOR DATA)
    for(int i = 0; i < 10000; i++)
    {
        //GETS NEIGHBORS OF CURRENT CANIDATE OF BEST PATH
        permutation newPermutation = BestPermutation;
        
        //CHECKS THE VERTICIES IN THE NEIGHBORHOOD
        //START AT ONE TO GET RID OF FIRST VERTEX
        for(int i = 1; i < r.verticies.size(); i++)
        {
            for(int j = 1; j < r.verticies.size(); j++)
            {
                //SWAPS THE VALUES
                //SIMPLE SWAP FUNCTIONALITY
                int tempVertex = newPermutation.cityPath[i];
                newPermutation.cityPath[i] = newPermutation.cityPath[j];
                newPermutation.cityPath[j] = tempVertex;
                
                
                //RESETS COST OF NEWPERMUTATION
                newPermutation.totalCost = 0;
                
                for(int x = 0; x < newPermutation.cityPath.size() - 1; x++)
                {
                    //CONTINOUSLY ADDS COST
                    newPermutation.totalCost = newPermutation.totalCost + r.getDistance(newPermutation.cityPath[x], newPermutation.cityPath[x + 1]);
                }
                 
                int counter = 0;
                for(int y = 0; y < tabuList.size(); y++)
                {
                    if(newPermutation == tabuList[y])
                    {
                        counter ++;
                    }
                }
                if(counter == 0)
                {
                    //IF THE SENT VALUE IS IN TABULIST THEN CHECK TOTAL COSTS
                    if(newPermutation.totalCost < BestPermutation.totalCost)
                    {
                        //SETS NEW COST VALUE
                        BestPermutation = newPermutation;
                    }
                }
            }
        }

         
        //BEST PERMUTATION IS NOW TABU SO PUSHES ONTO THE TABULIST
        tabuList.push_back(BestPermutation);

        //CHECKS TABU LIST VS MAX LIST SIZE (CHANGE THIS FOR DATA)
        if(tabuList.size() > 100)
        {
            //REMOVES THE OLDEST MEMBER IN TABULIST
            tabuList.erase(tabuList.begin() + 0);
        }
    }
    
    
     
    //CHECKS TABU LIST SIZE TO SEE IF LESS THAN PERMUTATION SIZE
    for(int i = 0; i < tabuList.size(); i++)
    {
        if(tabuList[i].totalCost < 10000) //(CHANGE THIS FOR DATA)
        {
            //SETS THE INDEX TO TABULIST VALUE
            position = i;
        }
    }
    
    //SETS THE BEST PERMUTATION TO THE TABULISTVALUE
    BestPermutation = tabuList[position];
    //SETS FINAL PERMUTATION
    finalBest = BestPermutation;
     
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

permutation tspTabu::setBest(reader &r)
{
    //SETS THE PERMUTATION VALUE
    permutation s;
    
    //SETS THE CITIES TO CHECK THROUGH
    for(int i = 0; i <= r.verticies.size(); i++)
    {
        if(i == 0 || i == 1)
        {
            continue;
        }
        else
        {
            s.cityPath.push_back(i);
        }
    }
    
    //RANDOMIZES THE CITIES
    random_shuffle(s.cityPath.begin(), s.cityPath.end());
    
    //INSERTS AT BEGGINING CITY 1
    s.cityPath.insert(s.cityPath.begin(), 1);
    
    //INSERTS FINAL POINT AS CITY 1
    s.cityPath.push_back(1);
    
    //FINDS THE COST
    for(int i = 0; i < s.cityPath.size() - 1; i++)
    {
        s.totalCost = s.totalCost + r.getDistance(s.cityPath[i], s.cityPath[i + 1]);
    }
    return s;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void tspTabu::output()
{
     
    //SETS THE CITY PATH VECTOR TO LATER BE PRINTED OUT
    for (int i = 0; i < finalBest.cityPath.size(); i++)
    {
        cityPath.push_back(finalBest.cityPath[i]);
    }
     
    //GRABS THE TOTAL COST FROM SOLVER CLASS
    totalCost = finalBest.totalCost;
     
    //OUTPUT OF THE STATS OF THE PROGRAM
    cout << "**********************************************" << endl;
    cout << "********************TSP TABU******************" << endl;
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



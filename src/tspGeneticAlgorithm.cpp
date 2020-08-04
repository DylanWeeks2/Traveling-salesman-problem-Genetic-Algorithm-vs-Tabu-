//DYLAN WEEKS, 47343235, LAB 4
#include <iostream>
#include <vector>
#include "tspGeneticAlgorithm.h"
#include "individual.h"
#include "algorithm.h"
#include "reader.h"

void tspGeneticAlgorithm::execute(reader &r)
{
    high_resolution_clock::time_point start = high_resolution_clock::now();
    geneticAlgorithm(r);
    high_resolution_clock::time_point finish = high_resolution_clock::now();
    duration<double> timeSpan = duration_cast<duration<double>>(finish - start);
    executionTime = timeSpan.count();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void tspGeneticAlgorithm::geneticAlgorithm(reader &r)
{
    
    
    ///
    //CREATES POPULATION
    ///
    
    
    for(int i = 0; i < 2; i++)
       {
           //CREATES TWO PARENTS
           parents.push_back(0);
       }
       for(int i = 0; i < 2000; i++) //POPULATION SIZE IS LOOP AMOUNT TO CHECK FOR
       {
           individual newPerson = setBest(r);
           population.push_back(newPerson);
       }
    

    //LOOP PERFORMS SELECTION AND CROSSOVER
    for(int i = 0; i < 500; i++)
    {
        
        ///
        //SELECTION
        //CHANGE INT FITNESS IN .H FILE TO CHANGE TECHNIQUE
        ///
        
        //FITNESS = ELITITSM
        if(fitness == 0)
        {
            //SETS UP THE VARIBLES
            double bestCost = 0.0;
            int one = 0;
            int two = 0;
            
            //LOOP TO FIND TEH BEST FIT VALUES
            for(int i = 0; i < population.size(); i++)
            {
                //CHECKS THE COST OF EACH IONDIVIDUAL
                if(population[i].totalCost > bestCost)
                {
                    //SWAPS
                    two = one;
                    one = i;
                    
                }
            }
            
            //RESETS THE PARENTS TO BEST FIT VALEUS FOR PARENTS
            parents[0] = one;
            parents[1] = two;
        }
        
        //FITNESS = ROULETTE WHEEL
        else if(fitness == 1)
        {
            //HOLDS THE SUM IN THSI FLOAT
            float s = 0;
            
            for(int i = 0; i < population.size(); i++)
            {
                //CALCULATES SUM
                s  = s + population[i].totalCost;
                
            }
            
            vector<float> test;
            for(int i = 0; i < population.size(); i++)
            {
                
                //PUSHES BACK THE NOST VALUE OF THE NEWEST PATH
                test.push_back(population[i].totalCost/s);
                
            }
            
            //CREATES TWO RANDOM VALUES FOR MARBLES
            //ALSO CREATES sumOfProbablity TO CHECK FOR
            double marbleOne = rand();
            double marbleTwo = rand();
            int sumOfProbability = 0;
            
            //THIS TAKES EACH INDIVIDUAL AND THEN SEPERATES APART OF THE ROULETTE WHEEL ACCORDING TO HOW MUCH IS DESERVED OF THEM
            for(int i = 0; i < test.size(); i++)
            {
                //CALCULATES THE FITNESS OF MARBLE
                sumOfProbability = sumOfProbability + test[i];
                
                //SIMULATES A MARBLE ROLE FOR MARBLE ONE
                if(marbleOne < sumOfProbability)
                {
                    if(parents[0] == 0)
                    {
                        parents[0] = i;
                    }
                }
                //SIMULATES MARBLE ROLE INTO ROULETTE WHEEL FOR MARBLE TWO
                else if(sumOfProbability > marbleTwo)
                {
                    if(parents[1] == 1)
                    {
                        parents[1] = i;
                    }
                }
            }
        }
        
        
        ///
        //CROSSOVER
        ///
        
        //CREATES OFFSPRING
        individual offspring = setBest(r);
        
        
        //RANDOM CROSSOVER
        if(crossover == 0)
        {
            int counter = rand() % (offspring.cityPath.size() - 1) + 1;
            
            //LOOP TO CROSSOVER THE PARENTS PATHS AND CREATE NEW OFFSPRING
            for(int i = 0; i < population[parents[0]].cityPath.size(); i++)
            {
                //CHECKS IF INDIVIDUALS PATH OF PARENT 1 IS GREATER THEN THE RANDOM GENERATED COUNTER OF OFFSPRING
                if(i < counter)
                {
                    //SETS OFFSPRING PATH
                    pathOfOffspring.push_back(population[parents[0]].cityPath[i]);
                }
                else
                {
                    //SETS OFFSPRING PATH
                    pathOfOffspring.push_back(population[parents[1]].cityPath[i]);
                }
            }
        }
        
        //CYCLIC CROSSOVER
        else if (crossover == 1)
        {
            //CREATES COUNTER
            int counter2 = 0;
            vector<int> temp(population[parents[0]].cityPath.size(), 0);
            pathOfOffspring = temp;
            int position = 0;
            
            
            for(int i = 0; i < pathOfOffspring.size(); i++)
            {
                //SETS FIRST VALUE TO PARENT ONE FIRST VALUE
                if(i == 0)
                {
                    pathOfOffspring[i] = population[parents[0]].cityPath[i];
                    //AFTER THAT MUST RUN LOOP TO REPLACE PARENT 2 FIRST VALUE
                    for(int j = 0; j < pathOfOffspring.size(); j++)
                    {
                        if(population[parents[0]].cityPath[j] == population[parents[0]].cityPath[i])
                        {
                            //PLACES IN PARENT 1 POSITION OF SAME VALUE
                            pathOfOffspring[j] = population[parents[1]].cityPath[i];
                            //RECORDS POSITION
                            position = j;
                            break;
                        }
                    }
                }
                //CHECKS FOR IF THE SAME REPET CYCLE IS CONTINUED
                else if(population[parents[1]].cityPath[position] != pathOfOffspring[position] && counter2 == 0)
                {
                    for(int j = 0; j < pathOfOffspring.size(); j++)
                    {
                        if(population[parents[0]].cityPath[j] == population[parents[1]].cityPath[position])
                        {
                            //PERFORMS THE SAME SWITHC
                            pathOfOffspring[j] = population[parents[1]].cityPath[position];
                            //RECORDS POSITION
                            position = j;
                            for(int x = 0; x < pathOfOffspring.size(); x++)
                            {
                                //CHECKS IF FINALLY THE LOOP OF SWITHCING IS OVER THEN ADDS THE COUNTER TO RECOGNIZE THE END OF CYCLIC CYCLE
                                if(population[parents[1]].cityPath[j] == pathOfOffspring[x])
                                {
                                    counter2++;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
                else
                {
                    for(int j = 0; j < pathOfOffspring.size(); j++)
                    {
                        //FROM HERE JUST ADDS THE PARENT 2 VALUES IN THE OPEN OFFSPRING POSITIONS
                        if(pathOfOffspring[j] == 0)
                        {
                            pathOfOffspring[j] = population[parents[1]].cityPath[j];
                        }
                    }
                }
            }
        }
        
        
        ///
        //MUTATION
        ///
        
        if(mutation == 0)
        {
            //CREATES RANDOM NUMBER BETWEEM 1 AND 100
            int mutation = rand() % 100 + 1;
            
            //USES 0.6 AS THE MUTATION RATE
            if(mutation < 0.6)
            {
                //CREATES TWO RANDOM GENES
                int geneOne = rand() % (offspring.cityPath.size() - 1) + 1;
                int geneTwo = rand() % (offspring.cityPath.size() - 1) + 1;
                    
                //SWAPS THE VALUES
                //SIMPLE SWAP FUNCTIONALITY
                int tempVertex = offspring.cityPath[i];
                offspring.cityPath[geneOne] = offspring.cityPath[geneTwo];
                offspring.cityPath[geneTwo] = tempVertex;
                    
                    
                //SETS NEW COST
                offspring.totalCost = 0;
                for(int i = 0; i < offspring.cityPath.size() - 1; i++)
                {
                    offspring.totalCost = offspring.totalCost + r.getDistance(offspring.cityPath[i], offspring.cityPath[i + 1]);
                }
            }
        }
        else if(mutation == 1)
        {
            //CREATES RANDOM NUMBER BETWEEM 1 AND 100
            int mutation = rand() % 100 + 1;
            
            //USES 0.6 AS THE MUTATION RATE
            if(mutation < 0.6)
            {
                //CREATES TWO RANDOM GENES
                int geneOne = rand() % (offspring.cityPath.size() - 1) + 1;
                int geneTwo = geneOne + 1;
                    
                //SWAPS THE VALUES
                //SIMPLE SWAP FUNCTIONALITY
                int tempVertex = offspring.cityPath[i];
                offspring.cityPath[geneOne] = offspring.cityPath[geneTwo];
                offspring.cityPath[geneTwo] = tempVertex;
                    
                    
                //SETS NEW COST
                offspring.totalCost = 0;
                for(int i = 0; i < offspring.cityPath.size() - 1; i++)
                {
                    offspring.totalCost = offspring.totalCost + r.getDistance(offspring.cityPath[i], offspring.cityPath[i + 1]);
                }
            }
        }
        
        //SETS THE OFFSPRING PATH AGIAN
        offspring.cityPath = pathOfOffspring;

        //CHECKS IF OFFSPRING IS EMPTY
        if(empty(offspring))
        {
            //ADDS OFFSPRING TO POPULATION
            population.push_back(offspring);
        }
    }
    
    ///
    //FINAL PART
    ///

    //LOOPS THROUGH FULL POPULATION
    for(int i = 0; i < population.size(); i++)
    {
        //CHECKS IF CURRENT INDIVIDUAL'S COST IS LESS THEN PREVIOUS
        if(population[i].totalCost < tempCost)
        {
            //SETS NEW TEMPCOST AND THEN STORES THAT POSITION VALUE TO USE FOR LATER
            tempCost = population[i].totalCost;
            finalPerson = population[i];
        }
    }

    //LOOP FOR SETTING THE PATH TO PRINT OF THE BEST CITY PATH
    for (int i = 0; i < finalPerson.cityPath.size(); i++)
    {
        cityPath.push_back(finalPerson.cityPath[i]);
    }
    
    //SETS FINAL COST
    totalCost = finalPerson.totalCost;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

individual tspGeneticAlgorithm::setBest(reader &r)
{
    //SETS THE PERMUTATION VALUE
    individual ind;
    
    //SETS THE CITIES TO CHECK THROUGH
    for(int i = 0; i <= r.verticies.size(); i++)
    {
        if(i == 0 || i == 1)
        {
            continue;
        }
        else
        {
            ind.cityPath.push_back(i);
        }
    }
    
    //RANDOMIZES THE CITIES
    random_shuffle(ind.cityPath.begin(), ind.cityPath.end());
    
    //INSERTS AT BEGGINING CITY 1
    ind.cityPath.insert(ind.cityPath.begin(), 1);
    
    //INSERTS FINAL POINT AS CITY 1
    ind.cityPath.push_back(1);
    
    //FINDS THE COST
    for(int i = 0; i < ind.cityPath.size() - 1; i++)
    {
        ind.totalCost = ind.totalCost + r.getDistance(ind.cityPath[i], ind.cityPath[i + 1]);
    }
    return ind;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

bool tspGeneticAlgorithm::empty(individual offspring)
{
    //CHECKS IF THE LAST CITY AINT START CITY OF 1
    if(offspring.cityPath[offspring.cityPath.size() - 1] != 1)
    {
        return false;
    }
    //CHECKS IF THE FIRST CITY AINT EQUAL 1
    else if(offspring.cityPath[0] != 1)
    {
        return false;
    }
    
    for(int i = 0; i < offspring.cityPath.size(); i++)
    {
        //CANT CHECK 0 OR 1 FOR i
        if(i == 0)
        {
            continue;
        }
        else if(i == 1)
        {
            continue;
        }
        else
        {
            int counter  = 0;
            
            //SECOND LOOP FOR COMPARISON OF OFFSPRING PATH
            for(int j = 0; j < offspring.cityPath.size(); j++)
            {
                //CONTINUES THORUGH VALUES 0 AND 1 FOR j
                if(j == 0)
                {
                    continue;
                }
                else if(j == 1)
                {
                    continue;
                }
                else
                {
                    //CHECKS FOR EQUALITY IN LOOP THEN INCREMENTS THE COUNTER
                    if(i == offspring.cityPath[j])
                    {
                        counter++;
                    }
                }
            }
            //IF COUNTER WAS INCREMENTED, THEN OFFSPRING ISNT EMPTY
            if(counter > 1)
            {
                return false;
            }
        }
    }
    
    //IF GOES THROUGH ALL THE TESTS THEN THE SENT OFFSPRING IS EMPTY
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void tspGeneticAlgorithm::output()
{
    //OUTPUT OF THE STATS OF THE PROGRAM
    cout << "**********************************************" << endl;
    cout << "*************TSP GENETIC ALGORITHM************" << endl;
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

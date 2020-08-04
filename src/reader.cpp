//DYLAN WEEKS, 47343235, LAB 4
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>
#include "reader.h"
#include "node.h"

using namespace std;

void reader::fileLoader()
{
    vector<float> positions;
    file.open("/Users/dylanweeks/Downloads/positions.txt");
    //OPENS FILE
    
    string line;
    string stringVertex;
    string p1,p2,p3;
    int vertex;
    float position1,position2,position3;
    while(file.good())
    {
        node newNode;
        file >> line;
        stringstream positionLine(line);
        getline(positionLine, stringVertex, ',');
        stringstream positionVertex(stringVertex);
        positionVertex >> vertex;
        verticies.push_back(vertex);
        newNode.addVertex(vertex);
        //SETS VERTICIES
        
        getline(positionLine, p1, ',');
        stringstream positionP1(p1);
        positionP1 >> position1;
        positions.push_back(position1);
        newNode.addPositions(position1);
        
        getline(positionLine, p2, ',');
        stringstream positionP2(p2);
        positionP2 >> position2;
        positions.push_back(position2);
        newNode.addPositions(position2);
        
        getline(positionLine, p3, '\n');
        stringstream positionP3(p3);
        positionP3 >> position3;
        positions.push_back(position3);
        newNode.addPositions(position3);
        //SETS ALL POSITIONS
        cities.push_back(newNode);
    }
    
    for(int i = 0; i < verticies.size(); i++)
    {
        verticies[i] = verticies[i] - 1;
    }
    
    vector<vector<float>> dM(verticies.size(), vector<float>(verticies.size()));
    float pos[verticies.size()-1][3];
    int vertexCount = 0;
    int graphCount = 0;
    
    //CREATES A 2D ARRAY OF FLOATS FOR JUST THE POSITIONS
    //THIS WAS MORE SO I COULD VISUALIZE HOW TO MAKE DISTANCE MATRIX EASIER
    for(int i = 0; i < positions.size(); i++)
    {
        if(i != 0 && i % 3 == 0)
        {
            vertexCount++;
            graphCount = 0;
        }
        pos[vertexCount][graphCount] = positions[i];
        graphCount++;
    }
    
    float distance = 0;
    
    //PUTS POSITIONS INTO DISTANCE MATRIX
    for(int i = 0; i < verticies.size(); i++)
    {
        for(int j = i + 1; j < verticies.size(); j++)
        {
            distance = sqrt(pow(pos[i][0] - pos[j][0], 2) + pow(pos[i][1] - pos[j][1], 2) + pow(pos[i][2] - pos[j][2], 2) * 1.0);
            dM[i][j] = distance;
            dM[j][i] = distance;
        }

        dM[i][i] = 0;
    }
    distanceMatrix = dM;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

float reader::getDistance(int cityOne, int cityTwo)
{
    //CREATES TWO NODES TO THEN EASIERLY FIND THE DISTANCE
    float distance = 0;
    node one = cities[cityOne - 1];
    node two = cities[cityTwo - 1];

    //MAKES SURE THE CITIES ARE VALID AND NOT EMPTY
    if(!empty(one))
    {
        if(!empty(two))
        {
            distance = sqrt(pow(one.positions[0]-two.positions[0], 2) + pow(one.positions[1]-two.positions[1], 2) + pow(one.positions[2]-two.positions[2], 2) * 1.0);
        }
    }
    
    return distance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

bool reader::empty(node sent)
{
    //CHECKS TO MAKE SURE IT AINT ZERO
    if(sent.vertex == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

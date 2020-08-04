//DYLAN WEEKS, 47343235, LAB 4
#ifndef reader_h
#define reader_h
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "node.h"

using namespace std;

class reader
{
public:
    void fileLoader();
    vector<vector<float>> distanceMatrix;
    vector<int> verticies;
    float getDistance(int cityOne, int cityTwo);
    bool empty(node sent);
    ifstream file;
    vector<node> cities;
};
#endif /* reader_h */



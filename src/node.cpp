//DYLAN WEEKS, 47343235, LAB 4
#include "node.h"
#include <vector>

using namespace std;

void node::addVertex(int v)
{
    vertex = v;
}

void node::addPositions(float pos)
{
    positions.push_back(pos);
}

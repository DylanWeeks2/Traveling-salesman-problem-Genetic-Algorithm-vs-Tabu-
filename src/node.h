//DYLAN WEEKS, 47343235, LAB 4
#ifndef node_h
#define node_h
#include <vector>

using namespace std;

class node
{
public:
    void addVertex(int v);
    void addPositions(float pos);
    int vertex;
    vector<float> positions;
};

#endif /* node_h */

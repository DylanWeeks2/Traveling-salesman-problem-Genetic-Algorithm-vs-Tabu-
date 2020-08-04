//DYLAN WEEKS, 47343235, LAB 4
#ifndef algorithm_h
#define algorithm_h
#include "reader.h"

using namespace std;

class algorithm
{
public:
    virtual void execute(reader &r) = 0;
    virtual void output() = 0;

};


#endif /* algorithm_h */



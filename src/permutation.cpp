//DYLAN WEEKS, 47343235, LAB 4
#include <iostream>
#include <vector>
#include "reader.h"
#include "permutation.h"

bool permutation::operator == (permutation &check)
{
    //BASIC OVERLOADED EQUALS OPERATOR
    if(this->cityPath == check.cityPath)
    {
        return true;
    }
    else
    {
        return false;
    }
}


//DYLAN WEEKS, 47343235, LAB 4
#include <iostream>
#include "algorithm.h"
#include "reader.h"
#include "algorithmType.h"
#include <vector>


int main(int argc, const char * argv[])
{
    algorithm *type;
    reader fileRead;
    fileRead.fileLoader();
    algorithmType algorithm;
    for(int i = 0; i < 4; i++)
    {
        type = algorithm.type(i);
        type -> execute(fileRead);
        type -> output();
    }
    return 0;
}



#include <iostream>
#include "mylib.h"
#include "config.hpp"
#include "nlohamnn/json.hpp"
/*
    You can find cmake global variables in the CMakeCache.txt file
*/

int main()
{
    std::cout<<"PROJECT_NAME:"<<projectName<<std::endl;
    std::cout<<"PROJECT_VERSION:"<<projectVersion<<std::endl;
    //std::cout<<projectVersionMajor<<projectVersionMinor<<projectVersionPatch<<std::endl;

    PrintHello();
    return 0;
}
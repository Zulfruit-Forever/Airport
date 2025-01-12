//Orignal Work of Zulfat Zigangirov U234N1241

#include <iostream>
#include <fstream>
#include <string>

#include "Prototype.h" 

int main()
{
    int timeH, timeM;

    do {
        std::cout << "Enter current time (XX XX, Hours Minutes):";
        std::cin >> timeH >> timeM;

    } while (correctTime(timeH, timeM) == "Error");





    //pretty much space here, yeah?
    menu();

    return 1; 
}

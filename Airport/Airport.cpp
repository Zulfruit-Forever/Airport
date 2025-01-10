//Orignal Work of Zulfat Zigangirov U234N1241

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "Header.h" 



int main()
{
    menu();

    return 1; 
}

std::string correctTime(int h, int m) {
    std::string corTime = "";
    //Maybe arrival time is not known yet
    if ((h == NULL && m == NULL)) 
        return "00:00";
    else if (h > 23 || h < 0 || m > 59 || m < 0)  return "Error"; //check for right input

    if (h < 9) corTime += "0";
    corTime +=std::to_string(h) + ":";
    if (m < 9) corTime += "0";
    corTime += std::to_string(m);
    return corTime;
}

//check for form factor of |ABC|ABC|NUM|NUM|NUM|
bool correctCode(std::string Code) {

    //size must be =5
    if (Code.size() != 5) return 0;

    //first 2 symbols 
    if (!(Code[0] >= 'A' && Code[0] <= 'Z' && Code[1] >= 'A' && Code[1] <= 'Z')) return 0;

    if (!(Code[2] >= '0' && Code[2] <= '9' &&
        Code[3] >= '0' && Code[3] <= '9' &&
        Code[4] >= '0' && Code[4] <= '9')) {
        return 0;
    }
}
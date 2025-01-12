#include <iostream>
#include <string>
#include <fstream>

#include "List.h"

//when i tried to do the separate cpp file with all List function implementation i forgot we have a list of type FligthRec
bool List<FlightRec>::exportTXT() {
	std::ofstream output;
	output.open("flights.txt", std::ofstream::app);



}
//separate cpp for functions of export and input

#include <iostream>
#include <string>
#include <fstream>

#include "List.h"



bool List<FlightRec>::exportTXT() {

	if (head == nullptr) {
		std::cout << "#Nothing to Export\n";
		return 0;//I just need to create an empry function...
	}

	std::ofstream output;
	output.open("flights.txt");

	Node<FlightRec>* temp = head;

	output <<"#Current time is :"<<correctTime(timeH,timeM)<< "\nDepartures\n";
	
	
		
	


	while (temp != nullptr) {
		if (temp->entry.Ftype == 0) {
			std::cout << "";
			output << temp->entry.FlightNO << " | "
				<< temp->entry.Destination << " | "
				<<  correctTime(temp->entry.Time.hour, temp->entry.Time.min) << " | "
				<< (temp->entry.Delay ? " Delayed " : " Not Delayed ") << " | "
				<< checkArrivalTime(temp) << "\n";

		}
		temp = temp->next;
	}
	temp = head;
	output << "#Current time is :" << correctTime(timeH, timeM) << "\nArrivals\n";
	while (temp != nullptr) {
		if (temp->entry.Ftype == 1) {
			std::cout << "";
			output << temp->entry.FlightNO << " | "
				<< temp->entry.Destination << " | "
				<< correctTime(temp->entry.Time.hour , temp->entry.Time.min) << " | "
				<< (temp->entry.Delay ? " Delayed " : " Not Delayed ") << " | "
				<< checkArrivalTime(temp) << "\n";

		}
		temp = temp->next;
	}





	output.close();
	
	return 1;
}

bool List<FlightRec>::importTXT() const{
	
	std::ifstream input;

	input.open("flights.txt");


	if (!input.is_open()) {//maybe flights does not exists right now
		std::cout << "#Error opening file for input\n";
		return false;
	}



	

	


	return 1;
}
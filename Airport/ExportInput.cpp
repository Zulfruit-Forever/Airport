//separate cpp for functions of export and input

#include <iostream>
#include <string>
#include <fstream>

#include "List.h"



bool List<FlightRec>::exportTXT() {
	std::ofstream output;
	output.open("flights.txt");

	Node<FlightRec>* temp = head;

	output <<"#Current time is :" << "\nDepartures\n";
	
	if (head == nullptr) return 0;//I just need to create an empry function...
		
	


	while (temp != nullptr) {
		if (temp->entry.Ftype == 0) {
			std::cout << "";
			output << temp->entry.FlightNO << " | "
				<< temp->entry.Destination << " | "
				<<  correctTime(temp->entry.Time.hour, temp->entry.Time.min) << " | "
				<< (temp->entry.Delay ? " Delayed " : " Not Delayed ") << " | "
				<< correctTime(temp->entry.ExpectedTime.hour, temp->entry.ExpectedTime.min) << "\n";

		}
		temp = temp->next;
	}
	temp = head;
	output << "\n#Current time is :" << "\nArrivals\n";
	while (temp != nullptr) {
		if (temp->entry.Ftype == 1) {
			std::cout << "";
			output << temp->entry.FlightNO << " | "
				<< temp->entry.Destination << " | "
				<< correctTime(temp->entry.Time.hour , temp->entry.Time.min) << " | "
				<< (temp->entry.Delay ? " Delayed " : " Not Delayed ") << " | "
				<< correctTime(temp->entry.ExpectedTime.hour, temp->entry.ExpectedTime.min )<< "\n";

		}
		temp = temp->next;
	}





	output.close();
	
	return 1;
}

bool List<FlightRec>::importTXT() const{



	return 1;
}
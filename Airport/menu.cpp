#include <iostream>
#include <string>
#include <iomanip>

#include "List.h"
#include "Prototype.h" 



void menu() {
    List<FlightRec> flights;

    FlightRec x3;
    char choice;
    int timeH, timeM;
    std::string ans;

    x3.Ftype = Departure;

    do {
        // menu
        std::cout << "\n#Menu Options#\n";
        std::cout << ((x3.Ftype == 0) ? "Departures" : "Arrivals") << " is selected\n";
        std::cout << "1. Add a new flight instance\n";
        std::cout << "2. Change arrival time\n";
        std::cout << "3. Modify flight time or delay status\n";
        std::cout << "4. Print all flights\n";
        std::cout << "5. Remove flight by FlightNumber\n";
        std::cout << "6. Change to the " << ((x3.Ftype == (0+1)%2) ? "Departure" : "Arrivals") << std::endl;
        std::cout << "7. Export to the File\n";
        std::cout << "8. Exit\n";

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case '1': { // Add a new flight


            // Add the FlightNumber
            do {
                std::cout << "Add the FlightNumber, 5 symbols, |ABC|ABC|NUM|NUM|NUM|\n";
                std::cin >> ans;

            } while (!correctCode(ans));

            x3.FlightNO = ans;

            // Add the Destination
            std::cout << "Add the Destination\n";
            std::cin >> x3.Destination;

            // Add the Time
            do {
                std::cout << "Add the Time in form of XX XX, hours minutes\n";
                std::cin >> timeH >> timeM;
                // correctTime(timeH, timeM);

            } while (correctTime(timeH, timeM) == "Error");
            // Insert values
            x3.Time.hour = timeH;
            x3.Time.min = timeM;

            // Check delay status
            do {
                std::cout << "Is Raice delayed? y/n\n";
                std::cin >> ans;

            } while (ans != "y" && ans != "n");

            x3.Delay = ("y" == ans);

            // Add the Expected Arrival time
            do {
                std::cout << "Add the Expected Arrival time\n";
                std::cin >> timeH >> timeM;

            } while (correctTime(timeH, timeM) == "Error");

            x3.ExpectedTime.hour = timeH;
            x3.ExpectedTime.min = timeM;

            // Insert the flight instance into the sorted list
            flights.insertSort(x3);

           
            std::cout << "Flight added successfully!\n";
            break;
        }
        case '2': { // Change arrival time

            if (x3.FlightNO.size() != 5) { std::cout << "\nAdd the Flight first:D\n"; break; }

            std::cout << "Enter the new Expected Arrival time (XX XX, hours minutes):\n";
            do {
                std::cin >> timeH >> timeM;

            } while (correctTime(timeH, timeM) == "Error");

            x3.ExpectedTime.hour = timeH;
            x3.ExpectedTime.min = timeM;
            std::cout << "Expected Arrival time updated successfully!\n";
            break;
        }

        case '3': { // Modify flight time or delay

            do {
                std::cout << "Enter the Flight Number to change the Time, Delay status\n";
                std::cin >> ans;

            } while (!correctCode(ans));

            flights.changeFlight(ans);

        }
        case '4': { // Print all flights
            flights.print();
            break;
        }
        case '5': {
            do {

                std::cout << "Add the FlightNumber for removal, 5 symbols, |ABC|ABC|NUM|NUM|NUM|\n";
                std::cin >> ans;

            } while (!correctCode(ans));

            flights.removeFlight(ans);

            break;

        }
        case '6': { //Change the enum type
            ((x3.Ftype == 0) ? x3.Ftype = Arrival : x3.Ftype = Departure);
        }
        case '7': {



        }
        case '8': { // Exit
            break;
        }

        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != '8');

    std::cout << "Exiting the program. Goodbye!\n";



}    


std::string correctTime(int h, int m) {
    std::string corTime = "";
    //Maybe arrival time is not known yet
    if ((h == 0 && m == 0)) return "00:00";

    if (h == 24 && m == 0)  return "24:00";

    if (h > 23 || h < 0 || m > 59 || m < 0)  return "Error"; //check for right input

    if (h < 9) corTime += "0";
    corTime += std::to_string(h) + ":";
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
    return 1;
}
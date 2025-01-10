#include <iostream>
#include "Header.h"


void menu() {
    List<FlightRec> flights;

    FlightRec x3;
    char choice;
    int timeH, timeM;
    std::string ans;

    do {
        // menu
        std::cout << "\nMenu Options:\n";
        std::cout << "1. Add a new flight instance\n";
        std::cout << "2. Change arrival time\n";
        std::cout << "3. Modify flight time or delay status\n";
        std::cout << "4. Print all flights\n";
        std::cout << "5. Remove flight by FlightNumber\n";
        std::cout << "6. Exit\n";
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
                // correctTime(timeH, timeM);

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

            if (x3.FlightNO.size() != 5) { std::cout << "\nAdd the Flight first:D\n"; break; }

            // Modify flight time
            std::cout << "Enter the new flight time (XX XX, hours minutes):\n";
            do {
                std::cin >> timeH >> timeM;

            } while (correctTime(timeH, timeM) == "Error");

            x3.Time.hour = timeH;
            x3.Time.min = timeM;

            // Modify delay status
            do {
                std::cout << "Is Raice delayed? y/n\n";
                std::cin >> ans;

            } while (ans != "y" && ans != "n");

            x3.Delay = ("y" == ans);
            std::cout << "Flight time and delay status updated successfully!\n";
            break;
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
        case '6': { // Exit
            break;
        }

        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);

    std::cout << "Exiting the program. Goodbye!\n";



}    
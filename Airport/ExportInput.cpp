//separate cpp for functions of export and input

#include <iostream>
#include <string>
#include <fstream>
#include "List.h"

bool List<FlightRec>::exportTXT() {
    if (head == nullptr) {
        std::cout << "# Nothing to export\n";
        return false;
    }

    std::ofstream output("flights.txt", std::ios::out);
    if (!output.is_open()) {
        std::cout << "# Error: Unable to open file for writing\n";
        return false;
    }

    Node<FlightRec>* temp = head;

    // Export departures
    output << "Current time is: " << correctTime(timeHC, timeMC) << "\nDepartures\n";
    while (temp != nullptr) {
        if (temp->entry.Ftype == Departure) {
            output << "### Flight Number: " << temp->entry.FlightNO << "\n"
                << "Destination: " << temp->entry.Destination << "\n"
                << "Time: " << temp->entry.Time.hour << ":"
                << (temp->entry.Time.min < 10 ? "0" : "") << temp->entry.Time.min << "\n"
                << "Delay? " << (temp->entry.Delay ? "Delayed" : "No Delay") << "\n"
                << "Expected Time: " << temp->entry.ExpectedTime.hour << ":"
                << (temp->entry.ExpectedTime.min < 10 ? "0" : "") << temp->entry.ExpectedTime.min << "\n\n";
        }
        temp = temp->next;
    }

    // Export arrivals
    temp = head;
    output << "Arrivals\n";
    while (temp != nullptr) {
        if (temp->entry.Ftype == Arrival) {
            output << "### Flight Number: " << temp->entry.FlightNO << "\n"
                << "Destination: " << temp->entry.Destination << "\n"
                << "Time: " << temp->entry.Time.hour << ":"
                << (temp->entry.Time.min < 10 ? "0" : "") << temp->entry.Time.min << "\n"
                << "Delay? " << (temp->entry.Delay ? "Delayed" : "No Delay") << "\n"
                << "Expected Time: " << temp->entry.ExpectedTime.hour << ":"
                << (temp->entry.ExpectedTime.min < 10 ? "0" : "") << temp->entry.ExpectedTime.min << "\n\n";
        }
        temp = temp->next;
    }

    output.close();
    return true;
}

bool List<FlightRec>::importTXT() {
    std::ifstream input("flights.txt", std::ios::in);
    if (!input.is_open()) {
        std::cout << "# Error: Unable to open file for reading\n";
        return false;
    }

    clear(); 

    std::string line;
    FlightRec flight;
    bool isDeparture = false;

    while (std::getline(input, line)) {
        // Определяем тип рейсов
        if (line.find("Departures") != std::string::npos) {
            isDeparture = true;
            continue;
        }
        else if (line.find("Arrivals") != std::string::npos) {
            isDeparture = false;
            continue;
        }

     
        if (line.find("### Flight Number:") != std::string::npos) {
            flight.Ftype = isDeparture ? Departure : Arrival;
            flight.FlightNO = line.substr(line.find(":") + 2);
            std::getline(input, line);
            flight.Destination = line.substr(line.find(":") + 2);
            std::getline(input, line);
            sscanf_s(line.c_str(), "Time: %d:%d", &flight.Time.hour, &flight.Time.min);
            std::getline(input, line);
            flight.Delay = (line.find("Delayed") != std::string::npos);
            std::getline(input, line);
            sscanf_s(line.c_str(), "Expected Time: %d:%d", &flight.ExpectedTime.hour, &flight.ExpectedTime.min);
            if (!flight.FlightNO.empty() && !flight.Destination.empty()) {
                insertSort(flight);
            }
            else {
                std::cout << "# Error: Invalid flight data encountered\n";
            }
        }
    }

    input.close();
    return true;
}
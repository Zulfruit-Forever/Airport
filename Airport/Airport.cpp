//Orignal Work of Zulfat Zigangirov U234N1241

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "Header.h" 


enum FlightType { Departure, Arrival };
struct TimeRec {
    int hour; // 0 to 23
    int min; // 0 to 59
};
struct FlightRec {
    std::string FlightNO;
    std::string Destination;
    TimeRec Time;
    FlightType Ftype;
    bool Delay;
    TimeRec ExpectedTime; // if the flight is delayed
};
template <class T>
struct Node {
    T entry;
    Node<T>* next;
    Node<T>* previous = nullptr;
    
    // constructors
    Node();
    Node(T, Node<T>* = nullptr);

};

template <class T>
Node<T>::Node() {
    if (this != nullptr) {
        next = nullptr;
        previous = nullptr;
    }
    else
        std::cout << "\nBad Alloc";
  
}

template <class T>
Node<T>::Node(T item, Node<T>* n) {
    if (this != nullptr) {
        entry = item;
        next = n;
    }
    else
        std::cout << "\nBad Alloc";
}


template <class T>
class List {
public:  
    List() {head = nullptr;}

    //this func must automatically sort the flights by time
    void insertSort(FlightRec& x) {

         Node<FlightRec>* temp = new Node<FlightRec>(x);

         Node<FlightRec>* current = head;

         if (head == nullptr) {
             head = temp;
         }
         else {//head points to something
             //sorting algo
             //sum in minutes
             int sumTemp = temp->entry.Time.hour * 60 + temp->entry.Time.min;
             int sumCurNext;
             int sumCur;
            
             Node<T>* previousNode = current;

             while (current != nullptr) {
                 sumCur = current->entry.Time.hour * 60 + current->entry.Time.min;

                 //temp node time is bigger than the current time and there is no next node
                 if ((sumTemp > sumCur) && (current->next == nullptr)) {
                     current->next = temp;
                     temp->previous = current;
                     break;
                 }
                 sumCurNext = current->next->entry.Time.hour * 60 + current->next->entry.Time.min;

                 //temp node time is bigger than the current time and there is NEXT node exists and its bigger than temp Node
                 if ((sumTemp > sumCur) && (sumCurNext > sumTemp)) {
                     current->next->previous = temp;

                     temp->next = current->next;
                     
                     current = temp;

                 }
                 else {
                     previousNode = current;//now this nodes point to the same place, 
                     current->previous = previousNode;
                     current = current->next;
                 }
                     
             }
         }
    }
    void removeFlight(std::string fligthNum) {

        Node<FlightRec>* removal = nullptr;
        Node<FlightRec>* temp = head;

        while (temp != nullptr) {
           
            if (temp->entry.FlightNO == fligthNum) {

                //previos node doest exists
                if (temp->previous == nullptr) {
                    head = head->next;
                    removal = temp; break;
                }
                //previos node exists
                else {
                    //temp->next maybe does not exists
                    if (temp->next != nullptr) {
                        temp->previous->next = temp->next;
                        removal = temp; break;
           
                    }
                    else {
                        temp->previous->next = nullptr;
                        removal = temp;  break;
                    }


                }
                   

                std::cout << "\nFlight :" << fligthNum << " removed";

            }
            temp = temp->next;
            if (temp == nullptr)
                std::cout << "\n#That Flight Couldnt be Found\n";
        }
        //exterminatus for the node 
        delete removal;
        removal = nullptr;

    }

    bool flightNumExistance(std::string fligthNum) {


    }


    void print() const{
        Node<FlightRec>* temp = head;

        if (head==nullptr) {
            //easter egg with the printf
            printf("\nThere is nothing to print\n");
            return;
        }
        while (temp!= nullptr) {
            //Flight Number
            //long cout for Flight Number  Destination  Time
            std::cout << "\nFlight Number: " << temp->entry.FlightNO
                << std::endl << "Destination: " << temp->entry.Destination //Destination
                << std::endl << "Time: " << correctTime(temp->entry.Time.hour ,temp->entry.Time.min)   //Time
                << std::endl << "Delay? " << ((temp->entry.Delay == true) ? " Delayed " : "")
                << std::endl << "Expected Time: " << correctTime(temp->entry.ExpectedTime.hour, temp->entry.ExpectedTime.min)
                << std::endl;  //Is Delayed?

            temp = temp->next;

        }
    }
private:
    Node<T>* head;
};


int main()
{
    List<FlightRec> flights;

    FlightRec x3 ;
    char choice;
    int timeH,timeM;
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

            } while (correctTime(timeH, timeM)=="Error");

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

    } while (choice!=6);

    std::cout << "Exiting the program. Goodbye!\n";



}    //check for form factor of |ABC|ABC|NUM|NUM|NUM|
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


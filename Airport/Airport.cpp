//Orignal Work of Zulfat Zigangirov U234N1241

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "Header.h" 



//List<FlightRec> flights;

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
    Node<T>* current = nullptr;
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
  
}

template <class T>
Node<T>::Node(T item, Node<T>* n) {
    if (this != nullptr) {
        entry = item;
        next = n;
    }
}


template <class T>
class List {
public:  
    List() {head = nullptr;}

    //Node& myNodes;
    /*
    bool CompareTimes() {



    }*/
    //this func must automatically sort the flights by time
    void insertSort(FlightRec& x) {

         Node<FlightRec>* temp = new Node<FlightRec>(x);

         Node<FlightRec>* current = head;

         if (head == nullptr) {
             head = temp;
         }
         else {//head points to something
             //sorting algo
             while (current != nullptr) {
                 //temp node time is bigger than the current time
                 if ((temp->entry.Time.hour * 60 + temp->entry.Time.min) > (current->entry.Time.hour * 60 + current->entry.Time.min)) {
                     temp->next = current->next;
                     //temp node time is bigger than the current->next
                     if ((current->next->entry.Time.hour * 60 + current->next->entry.Time.min) > (temp->entry.Time.hour * 60 + temp->entry.Time.min) {



                     }
                     current->next = temp;
                 }
                 current = current->next;
             }
             temp->next = head;
             head = temp;

         }

 
  
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
                << std::endl << "Time: " << temp->entry.Time.hour << ":" << temp->entry.Time.min   //Time
                << std::endl << "Delay? " << ((temp->entry.Delay == true) ? " Delayed " : "")
                << std::endl << "Expected Time: " << temp->entry.ExpectedTime.hour << ":" << temp->entry.ExpectedTime.min
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
        std::cout << "5. Exit\n";
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

            } while (!correctTime(timeH, timeM));
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

            } while (!correctTime(timeH, timeM));

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

            } while (!correctTime(timeH, timeM));

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

            } while (!correctTime(timeH, timeM));

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

        case '5': { // Exit
            break;
        }

        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice!=5);

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

bool correctTime(int h, int m) {
    //Maybe arrival time is not known yet
    if (!(h == NULL || m == NULL));
    else if (h > 23 || h < 0 || m > 59 || m < 0) return 0;//check for right input

    return 1;
}


#include "Prototype.h"

//Here is the List Class with all insides
#ifndef LIST_H
#define LIST_H



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
    List() { head = nullptr; }

    int timeHC = 0, timeMC = 0;
    //this func must automatically sort the flights by time

    bool exportTXT();
    bool importTXT();

    void insertSort(FlightRec& x) {

        Node<FlightRec>* temp = new Node<FlightRec>(x);

        Node<FlightRec>* current = head;

        if (head == nullptr){   
            head = temp;
            temp->previous = head;
        }
        else {//head points to something
            //sorting algo
            //sum in minutes
            int sumTemp = temp->entry.Time.hour * 60 + temp->entry.Time.min;

            Node<T>* previousNode = current;

            while (current != nullptr) {
                int sumCur = current->entry.Time.hour * 60 + current->entry.Time.min;

                //temp node time is bigger than the current time 
                if (sumTemp >= sumCur) {
                    //next node doesnt exists
                    if (current->next == nullptr) {
                        current->next = temp;
                        temp->previous = current;
                        break;

                    }
                    int sumCurNext = current->next->entry.Time.hour * 60 + current->next->entry.Time.min;
                    if (sumCurNext > sumTemp) {
                        temp->next = current->next;
                        current->next->previous = temp;
                        current->next = temp;
                        temp->previous = current;
                        break;

                    }
              
                }
                //temp is less than current
                else if (sumTemp < sumCur) {
                    
                    if (current->previous == head) {
                        temp->next = current;
                        head = temp;
                        current->previous = temp; 
                        break;
                    }
                    int sumCurPrev = current->next->entry.Time.hour * 60 + current->next->entry.Time.min;
                    if (sumCurPrev > sumTemp) {
                        temp->next = current;
                        temp->previous = current->previous;
                        current->previous->next = temp;
                        temp->previous = current->previous;
                        break;
                    }
                }
           
                
                current = current->next;
                //temp node time is bigger than the current time and there is NEXT node exists and its bigger than temp Node
               

            }
        }
    }
    std::string checkArrivalTime(Node<FlightRec>* temp) {

        if (temp==nullptr) return "Error";//maybe i should just used enum types? Maybe but its too late

        if((temp->entry.ExpectedTime.hour*60 + temp->entry.ExpectedTime.min ) < (timeHC *60+timeMC))
            return "Arrived";

        return correctTime(temp->entry.ExpectedTime.hour, temp->entry.ExpectedTime.min);
    }
    void removeFlight(std::string fligthNum) {

        Node<FlightRec>* removal = nullptr;
        Node<FlightRec>* temp = head;
        
        if (head->next == nullptr) {
            std::cout << "\n#Empty\n";
            return;
        }
            


        while (temp != nullptr) {

            if (temp->entry.FlightNO == fligthNum) {

                //previos node doest exists
                if (temp->previous == head) {
                    removal = temp;
                    head = temp->next;
                    temp->previous = head;
     
                }
                //previos node exists
                else {
                    //temp->next maybe does not exists
                    if (temp->next != nullptr) {
                        temp->previous->next = temp->next;
                        temp->next->previous = temp->previous;
                        removal = temp; 

                    }
                    else {//next points to nullptr
                        temp->previous->next = nullptr;
                        removal = temp; 
                    }

                }

                std::cout << "\nFlight :" << fligthNum << " removed";

            }
            temp = temp->next;
        }
        //exterminatus for the node 
        delete removal;
        removal = nullptr;

    }

    void print()  {
        Node<FlightRec>* temp = head;

        if (head == nullptr) {
            //easter egg with the printf
            printf("\nThere is nothing to print\n");
            return;
        }
        while (temp != nullptr) {
            //Flight Number
            //long cout for FlightRec 
                std::cout << "\nFlight Type: " << ((temp->entry.Ftype==0) ? "Departures": "Arrivals")
                << std::endl << "Flight Number: " << temp->entry.FlightNO
                << std::endl << "Destination: " << temp->entry.Destination //Destination
                << std::endl << "Time: " << correctTime(temp->entry.Time.hour, temp->entry.Time.min)   //Time
                << std::endl << "Delay? " << ((temp->entry.Delay == true) ? " Delayed " : " No Delay ")
                << std::endl << "Expected Time: " << checkArrivalTime(temp)
                << std::endl;  //Is Delayed?

            temp = temp->next;

        }
    }


    void changeFlight(std::string fligthNum) {
        Node<FlightRec> *temp=head;
     

        if (head == nullptr) { std::cout << "List is Empty\nAdd the Flights Firts\n";  return ; }



        while (temp != nullptr) {
            if (temp->entry.FlightNO == fligthNum) break;
            temp = temp->next;
        }
        if (temp == nullptr) {
            std::cout << "\nFlight is not found\n ";
            return;
        }
        char ch; 
        int timeH, timeM;
        
        // Modify flight time

        do {
            std::cout << "\n#Menu#\n1.Change the Flight Time \n2.Change the Raice Delay\n3.Change the Expected Time \n4.Exit\n";
            std::cin >> ch;


            switch (ch) {
                
            case '1': {


                
                do {
                    std::cout << "Enter the new flight time (XX XX, hours minutes):\n";
                    std::cin >> timeH >> timeM;

                } while (correctTime(timeH, timeM) == "Error");

                temp->entry.Time.hour = timeH;
                temp->entry.Time.min = timeM;
                break;
            }
            case '2': {
                char ans;
                // Modify delay status
                do {
                    std::cout << "Is Raice delayed? y/n\n";
                    std::cin >> ans;

                } while (ans != 'y' && ans != 'n');

                temp->entry.Delay = ('y' == ans);
                std::cout << "Delay status updated successfully!\n";

            }
            case '3': {

                std::cout << "Enter the Arrival Time (XX XX, hours minutes):\n";
                do {
                    std::cin >> timeH >> timeM;

                } while (correctTime(timeH, timeM) == "Error");

                temp->entry.ExpectedTime.hour = timeH;
                temp->entry.ExpectedTime.min = timeM;
                break;

            }
            case '4': {
                std::cout << "\n#Exiting The Choice Menu\n";
                break;
            }
            default: 
                std::cout << "\nWrnong Input\n";
            
            }
        } while (ch != '4');
            


    }
    void clear() {

        if (head== nullptr)return;

        Node<FlightRec>* temp = head;
        Node<FlightRec>* removal = nullptr;

        while (temp != nullptr) {
            removal = temp;
            temp = temp->next;
            delete removal;
            removal = nullptr;


        }
        head = nullptr;
    }
        

private:
    Node<T>* head;
};


#endif 



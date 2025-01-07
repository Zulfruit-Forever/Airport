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

    Node<T>* previous;
    
    // constructors
    Node();
    Node(T, Node<T>* = nullptr);

};

template <class T>
Node<T>::Node() {
    next = nullptr;
}

template <class T>
Node<T>::Node(T item, Node<T>* n) {
    entry = item;
    next = n;
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

         Node<FlightRec>* temp = new Node<FlightRec>(x, head);

         

         if (head == nullptr) {
             temp->next = head;
             head = temp;

         }
         else {//head points to something
             temp->next = head;
             head->next = temp;

         }

 
  
    }
    void print() const{
        Node<FlightRec>* temp = head;


       
        while (temp!= nullptr) {
            std::cout<<temp->entry.FlightNO;
            temp = temp->next;

        }



    }


private:
    Node<T>* head;
};


int main()
{
    List<FlightRec> flights;

   // FlightRec* x2 = new FlightRec;

    FlightRec x3 ;

    int timeH,timeM;
    
    

    std::cout << "Add the FlightNumber\n";
    std::cin >> x3.FlightNO;


    std::cout << "Add the Destination\n";
    std::cin >> x3.Destination;

    do {
        std::cout << "Add the Time in form of XX XX ,hours minutes\n";
        std::cin >> timeH>>timeM;
        //correctTime(timeH,timeM);

    } while (!correctTime(timeH,timeM));
    //Insert values
    x3.Time.hour = timeH; x3.Time.min = timeM;


    std::cout << "Add the FlightNumber\n";
    std::cin >> x3.Delay;


    std::cout << "Add the FlightNumber\n";
    std::cin >> x3.ExpectedTime.hour;


    flights.insertSort(x3);
    flights.print();








}

bool correctTime(int h, int m) {
    if (h > 23 || m > 59)return 0;




    return 1;
}


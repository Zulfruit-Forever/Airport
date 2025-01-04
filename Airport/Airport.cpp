//Orignal Work of Zulfat Zigangirov u234n1241

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>



List<FlightRec> flights;

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
    // constructors
    Node();
    Node(entry, Node<T>* = nullptr);
};
template <class T>
class List {
public:  
    List() {head = nullptr;}
   
    void insertVal(T,next);

private:
    Node<T>* head;
};




int main()
{
    FlightRec x1 = new FlightRec;



}


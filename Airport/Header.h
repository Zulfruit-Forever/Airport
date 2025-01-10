#pragma once

//Checkers
#ifndef PROTO_H
#define PROTO_H


std::string correctTime(int h, int m);
bool correctCode(std::string Code);
void menu();


#endif // Proto

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

    void print() const {
        Node<FlightRec>* temp = head;

        if (head == nullptr) {
            //easter egg with the printf
            printf("\nThere is nothing to print\n");
            return;
        }
        while (temp != nullptr) {
            //Flight Number
            //long cout for Flight Number  Destination  Time
            std::cout << "\nFlight Number: " << temp->entry.FlightNO
                << std::endl << "Destination: " << temp->entry.Destination //Destination
                << std::endl << "Time: " << correctTime(temp->entry.Time.hour, temp->entry.Time.min)   //Time
                << std::endl << "Delay? " << ((temp->entry.Delay == true) ? " Delayed " : "")
                << std::endl << "Expected Time: " << correctTime(temp->entry.ExpectedTime.hour, temp->entry.ExpectedTime.min)
                << std::endl;  //Is Delayed?

            temp = temp->next;

        }
    }

private:
    Node<T>* head;
};

#endif // MY_HEADER_H



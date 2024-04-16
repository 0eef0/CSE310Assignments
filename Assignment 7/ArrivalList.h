//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Name of Author: Ethan Roldan
// ASU ID: 1223945385
// Description: //---- is where you should add your own code
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Arrival represents an arrival address with distance and road
//category info. from a specific departure address
struct Arrival
{
    string arrAddress;
    double distance;        //miles from the departure address to this arrival address
    string roadCategory;    //Interstates, Arterials, Collectors or Local streets
    struct Arrival* next;
};

//class ArrivalList contains a linked list of Arrival objects
class ArrivalList
{
private:
    struct Arrival* head;

public:
    ArrivalList();
    ~ArrivalList();
    Arrival* getHead();
    Arrival* findArrival(string oneAddress);
    bool addArrival(string oneAddress, double distance, string roadCategory);
    void printArrivalList();
};


//*****************************************************************************************************
//Destructor. Before termination, the destructor is called to free the associated memory occupied by the
//existing linked list. It deletes all the Arrivals including the head and finally prints the number of
//Arrival deleted by it.
//----
//----
ArrivalList::~ArrivalList() {
    //int addressCount = 0;
    //cout<< "The number of deleted arrival addresses are: " << addressCount <<"\n";
}

//According to above class definition, define all functions accordingly
ArrivalList::ArrivalList() {
    head = nullptr;
}

Arrival* ArrivalList::getHead() {
    return head;
}

Arrival* ArrivalList::findArrival(std::string oneAddress) {
    Arrival* temp = head;
    while(temp != nullptr) {
        if(temp->arrAddress == oneAddress) {
            break;
        } else {
            temp = temp->next;
        }
    }
    return temp;
}

bool ArrivalList::addArrival(std::string oneAddress, double distance, std::string roadCategory) {
    Arrival* newArrival = new Arrival();
    newArrival->arrAddress = oneAddress;
    newArrival->distance = distance;
    newArrival->roadCategory = roadCategory;
    newArrival->next = nullptr;

    if(head == nullptr) {
        head = newArrival;
    } else if(newArrival->arrAddress.compare(head->arrAddress) < 0) {
        newArrival->next = head;
        head = newArrival;
        return true; // Insertion successful
    } else {
        Arrival* temp = head;
        while (temp->next != nullptr && newArrival->arrAddress.compare(temp->next->arrAddress) > 0) {
            temp = temp->next;
        }
        newArrival->next = temp->next;
        temp->next = newArrival;
        return true; // Insertion successful
    }
    return false; // Insertion failed
}


//Prints all the arrival address in the linked list starting from the head.
void ArrivalList::printArrivalList()
{
    if(head == nullptr) {
        cout << "Arrival list is empty";
    } else {
        Arrival *temp = head;
        while (temp != nullptr) {
            cout << temp->arrAddress
                 << fixed << setprecision(2) << "(" << temp->distance << "/" << temp->roadCategory << "),";
            temp = temp->next;
        }
    }
    //cout <<"\n";
}
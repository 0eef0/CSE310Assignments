//// ASU CSE310 Spring 2024 Assignment #1
//// Name: Ethan Roldan
//// ASU ID: 1223945385
//// Description: This file is the class declaration for the LinkedList
////              This includes all of the nodes and functions
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Car
{
    string model, make;
    int vin;
    double price;
    struct Car* next;
};

class LinkedList
{
private:
    struct Car* head;
    int size;      //a variable represents number of Cars inside the list
public:
    LinkedList();
    ~LinkedList();
    Car* getHead();
    int getSize();
    bool searchCar(int carVIN);
    bool insertCar(string model, string make, int vin, double price);
    bool deleteCar(int carVIN);
    void displayList();
};

//Constructor
LinkedList::LinkedList()
{
    head = nullptr;
    size = 0;
}

//Destructor
LinkedList::~LinkedList()
{
    while(head != nullptr) {
        Car* temp = head;
        head = head->next;
        delete temp;
    }
}

// Return the head node of the linked list
Car* LinkedList::getHead()
{
    return head;
}

//Return number of Cars inside the Linked list
int LinkedList::getSize()
{
    return size;
}

//This function does a linear search on the Car list with the given Car VIN
//it returns true if the corresponding Car is found, otherwise it returns false.
bool LinkedList::searchCar(int carVIN)
{
    // make a temp node that matches the head
    Car* temp = head;
    if(head == nullptr) { // if the head is null then the list is empty and return false
        return false;
    }
    // this while loop checks every element from the first to the second to last for the wanted vin and returns true if found
    while(temp->next != nullptr) {
        if(temp->vin == carVIN) {
            return true;
        }
        temp = temp->next;
    }
    // check the last node if it matches the wanted vin
    if(temp->vin == carVIN) {
        return true;
    }
    return false;
}

//Insert the parameter Car at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertCar(string model, string make, int vin, double price)
{
    // if the vin is already in the list then we return false and dont add it
    if(searchCar(vin)) {
        return false;
    }
    // initialize a new car with parameters
    Car* newCar = new Car();
    Car* temp = head;
    newCar->model = model;
    newCar->make = make;
    newCar->vin = vin;
    newCar->price = price;
    // make the new node the head and shift the rest back
    newCar->next = temp;
    head = newCar;
    size++;
    return true;
}

//Delete the Car with the given Car VIN from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteCar(int carVIN)
{
    // if the wanted vin is in the head then we remove the head by shifting the list forward
    // decrement the list size if deleted
    if(head->vin == carVIN) {
        head = head->next;
        size--;
        return true;
    }
    // initialize prev and curr nodes to iterate through the list
    // if wanted node is found then set the prev to curr.next
    // decrement the size if deleted
    Car* prev = head;
    Car* curr = head->next;
    while(curr != nullptr) {
        if(curr->vin == carVIN) {
            prev->next = curr->next;
            size--;
            return true;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return false;
}

//This function displays the content of the linked list.
void LinkedList::displayList()
{
    struct Car *temp = head;
    if(head == NULL)
    {
        //empty linked list, print nothing here
    }
    else
    {
        while(temp != NULL)
        {
            cout << left    << setw(18) << temp->model
                 << left    << setw(18) << temp->make
                 << right   << setw(8)  << temp->vin
                 << setw(10) << fixed << setprecision(2) << temp->price << "\n";
            temp = temp->next;
        }
    }
}
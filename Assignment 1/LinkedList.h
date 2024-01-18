// ASU CSE310 Spring 2024 Assignment #1
// Name: Ethan Roldan
// ASU ID: 1223945385
// Description:

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Car represents a Car information
struct Car
{
    string model, make;
    int vin; // vehicle identification number
    double price;
    struct Car *next;
};

// class LinkedList will contain a linked list of Cars
class LinkedList
{
private:
    struct Car *head;

public:
    LinkedList();
    ~LinkedList();
    bool findCar(int aVin);
    bool addCar(string model, string make, int vin, double price);
    bool removeByVin(int aVin);
    bool removeByModelAndMake(string model, string make);
    bool changeCarInfo(int aVin, string newModelAndMake);
    bool updateCarPrice(int aVin, double newPrice);
    void printCarListByMake(string make);
    void printCarList();
};

// Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    head = nullptr;
}

// Destructor
// Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
// It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
// Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
    // add your own code
    //----
    int carCount = 0;
    cout << "The number of deleted Car is: " << carCount << "\n";
}

// A function to identify if the parameterized Car is inside the LinkedList or not.
// Return true if it exists and false otherwise.
bool LinkedList::findCar(int aVin)
{
    if(head != nullptr) {
        Car *temp = head;
        while (temp != nullptr) {
            if (temp->vin == aVin) {
                return true;
            }
            temp = temp->next;
        }
    }
    return false;
}

// Creates a new Car and inserts it into the list at the right place.
// It also maintains an alphabetical ordering of Cars by their make and model, i.e.
// first by make, if two cars have same makes, then we will list them by model. Note: each Car
// has a unique vin, the vehicle identification number, but may have the same make and model.
// In case two Cars have same make and model, they should be inserted according to the
// increasing order of their vins.
// Return value: true if it is successfully inserted and false in case of failures.
bool LinkedList::addCar(string model, string make, int vin, double price)
{
    // if the Car already exist, return false
    if(head == nullptr) {
        head = (Car*) malloc(sizeof(Car));
        head->model = model;
        head->make = make;
        head->vin = vin;
        head->price = price;
        head->next = nullptr;
        return true;
    } else {
        Car* temp = head;
        while(temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = (Car*) malloc(sizeof(Car));
        temp->next->make = make;
        temp->next->model = model;
        temp->next->vin = vin;
        temp->next->price = price;
        temp->next->next = nullptr;
        return true;
    }
    return false;
}

// Removes the specified Car from the list, releases the memory and updates pointers.
// Return true if it is successfully removed, false otherwise.
bool LinkedList::removeByVin(int aVin)
{
    if(head == nullptr) {
        return false;
    }
    if(head->vin == aVin) {
        head = head->next;
        return true;
    } else {
        Car* prev = head;
        Car* curr = head->next;
        while(curr != nullptr) {
            if(curr->vin == aVin) {
                prev->next = curr->next;
                delete curr;
                return true;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
    return false;
}

// Removes the given Car from the list, releases the memory and updates pointers.
// Return true if it is successfully removed, false otherwise. Note: all Cars with
// the same model and make should be removed from the list.
bool LinkedList::removeByModelAndMake(string model, string make)
{
    if(head == nullptr) {
        return false;
    }
    bool removed = false;
    if(head->model == model && head->make == make) {
        head = head->next;
        removed = true;
    }
        Car* prev = head;
        Car* curr = head->next;
        while(curr != nullptr) {
            if(curr->model == model && curr->make == make) {
                prev->next = curr->next;
                removed = true;
                delete curr;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    return removed;
//    else
//    {
//        cout << "No such Car found.\n";
//        return false;
//    }
}

// Modifies the data of the given Car. Return true if it modifies successfully and
// false otherwise. Note: after changing a Car model and make, the linked list must still
// maintain the alphabetical order.
//bool LinkedList::changeCarInfo(int aVin, string newModelAndMake)
//{
//    // split newModelAndMake string to get model and make accordingly
//    // add your own code
//    //----
//
//    // add your own code
//    //----
//}

bool LinkedList::updateCarPrice(int aVin, double newPrice)
{
    if(head != nullptr) {
        Car *temp = head;
        while (temp != nullptr) {
            if (temp->vin == aVin) {
                temp->price = newPrice;
                return true;
            }
            temp = temp->next;
        }
    }
    return false;
}

// Prints all Cars in the list with the same make.
void LinkedList::printCarListByMake(string make)
{
    // add your own code
    //----

    if(head == nullptr) {
        cout << "The list is empty\n";
    } else {
        Car* temp = head;
        bool isCar = false;
        while(temp != nullptr) {
            if(temp->make == make) {
                cout << left << setw(12) << temp->model
                     << left << setw(12) << temp->make
                     << right << setw(8) << temp->vin
                     << setw(10) << fixed << setprecision(2) << temp->price << "\n";
                isCar = true;
            }
            temp = temp->next;
        }
        if(!isCar) {
            cout << "No Cars with the specified make found.\n";
        }
    }
}

// Prints all Cars in the linked list starting from the head node.
void LinkedList::printCarList()
{
    // add your own code
    //----
    if(head == nullptr) {
        cout << "The list is empty\n";
    } else {
        Car* temp = head;
        while(temp != nullptr) {
                cout << left << setw(12) << temp->model
             << left << setw(12) << temp->make
             << right << setw(8) << temp->vin
             << setw(10) << fixed << setprecision(2) << temp->price << "\n";

                temp = temp->next;
        }
    }
}
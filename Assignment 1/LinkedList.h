// ASU CSE310 Spring 2024 Assignment #1
// Name: Ethan Roldan
// ASU ID: 1223945385
// Description: This file is the class declaration for the LinkedList
//              This includes all of the nodes and functions

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
    head = nullptr; // initalize an empty head node
}

// Destructor
// Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
// It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
// Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
    int carCount = 0; // Car count starts at zero

    // while node is in the head, delete the head and shift the list forward
    while(head != nullptr) {
        Car* temp = head;
        head = head->next;
        delete temp;
        carCount++;
    }
    cout << "The number of deleted Car is: " << carCount << "\n";
}

// A function to identify if the parameterized Car is inside the LinkedList or not.
// Return true if it exists and false otherwise.
bool LinkedList::findCar(int aVin)
{
    // If the list is empty, return false
    if(head != nullptr) {
        // Initialize a temp node and iterate until a node with aVin is found
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
    // This checks if the VIN is already registered, if it is, then return false
    if(head != nullptr) {
        Car *temp = head;
        while (temp != nullptr) {
            if (temp->vin == vin) {
                return false;
            }
            temp = temp->next;
        }
    }

    // Make the new Car
    Car* newCar = (Car*) malloc(sizeof(Car));
    newCar->model = model;
    newCar->make = make;
    newCar->vin = vin;
    newCar->price = price;
    newCar->next  = nullptr;

    // If the head is empty, then the list is empty so make the new car the head
    if(head == nullptr) {
        newCar->next = head;
        head = newCar;
        return true;
    }
    // If the new car has a make less than the current head, then make it the new head
    if(make.compare(head->make) < 0) {
        newCar->next = head;
        head = newCar;
        return true;
    }
    // If the new car has a make equal to the current head, then check the model
    if(make.compare(head->make) == 0) {
        if(model.compare(head->model) < 0) {
            newCar->next = head;
            head = newCar;
            return true;
        }
        // If the models are the same then check the VIN
        if(model.compare(head->model) == 0) {
            if(vin < head->vin) {
                newCar->next = head;
                head = newCar;
                return true;
            }
        }
    }

    // If the car doesnt go to the head, then organize the new objects by make, then model, then VIN
    Car* curr = head;
    while(curr->next != nullptr && make.compare(curr->next->make) > 0) {
        curr = curr->next;
    }
    while (curr->next != nullptr && make.compare(curr->next->make) == 0 && model.compare(curr->next->model) > 0) {
        curr = curr->next;
    }
    while (curr->next != nullptr && model.compare(curr->next->model) == 0 && vin > curr->next->vin) {
        curr = curr->next;
    }
    newCar->next = curr->next;
    curr->next = newCar;
    return true;
}

// Removes the specified Car from the list, releases the memory and updates pointers.
// Return true if it is successfully removed, false otherwise.
bool LinkedList::removeByVin(int aVin)
{
    // If the list is empty, return false
    if(head == nullptr) {
        return false;
    }
    // If the head is the desired deletion, then delete it
    if(head->vin == aVin) {
        head = head->next;
        return true;
    } else {
        // If it is not the head, then iterate through until you find it, then delete it
        Car* prev = head;
        Car* curr = head->next;
        while(curr != nullptr) {
            if(curr->vin == aVin) {
                prev->next = curr->next;
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
    // If the list is empty, return false
    if(head == nullptr) {
        return false;
    }

    // This variable denotes whether or not an element has been removed
    bool removed = false;

    // If the desired remover is the head, them remove cars until it isnt anymore
    while(head != nullptr && head->model == model && head->make == make) {
        head = head->next;
        removed = true;
    }

    // if the desired deletion is in the middle, then iterate until theyre all deleted
    Car* prev = nullptr;
    Car* curr = head;
    while(curr != nullptr) {
        if(curr->model == model && curr->make == make) {
            removed = true;
            prev->next = curr->next;
        } else {
            prev = curr;
        }
        curr = curr->next;
    }

    if(!removed) cout << "No such Car found.\n";
    return removed;
}

// Modifies the data of the given Car. Return true if it modifies successfully and
// false otherwise. Note: after changing a Car model and make, the linked list must still
// maintain the alphabetical order.
bool LinkedList::changeCarInfo(int aVin, string newModelAndMake)
{
    // split newModelAndMake string to get model and make accordingly
    bool carFound = false;
    int space = newModelAndMake.find(" ");
    string model = newModelAndMake.substr(0, space);
    string make = newModelAndMake.substr(space + 1);
    double price;

    if(head == nullptr) {
        return false;
    }
    if(head->vin == aVin) {
        price = head->price;
        Car* temp = head;
        head = head->next;
        delete temp;
        carFound = true;
    } else {
        Car* prev = head;
        Car* curr = head->next;
        while(curr != nullptr) {
            if(curr->vin == aVin) {
                price = curr->price;
                prev->next = curr->next;
                delete curr;
                carFound = true;
                break;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }

    if(carFound) {
        Car *newCar = new Car();
        newCar->model = model;
        newCar->make = make;
        newCar->vin = aVin;
        newCar->price = price;
        newCar->next = nullptr;

        // if the Car already exist, return false
        if (head == nullptr) {
            newCar->next = head;
            head = newCar;
            return true;
        }
        if (make.compare(head->make) < 0) {
            newCar->next = head;
            head = newCar;
            return true;
        }
        if (make.compare(head->make) == 0) {
            if (model.compare(head->model) < 0) {
                newCar->next = head;
                head = newCar;
                return true;
            }
            if (model.compare(head->model) == 0) {
                if (aVin < head->vin) {
                    newCar->next = head;
                    head = newCar;
                    return true;
                }
            }
        }

        Car* i = head;
        while (i->next != nullptr && make.compare(i->next->make) > 0) {
            i = i->next;
        }
        while (i->next != nullptr && make.compare(i->next->make) == 0 && model.compare(i->next->model) > 0) {
            i = i->next;
        }
        while (i->next != nullptr && model.compare(i->next->model) == 0 && aVin > i->next->vin) {
            i = i->next;
        }

        newCar->next = i->next;
        i->next = newCar;
    }
    return carFound;
}

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
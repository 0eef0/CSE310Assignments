// Assignment: ASU CSE310 HW#3 Spring 2024
// Your Name: Ethan Roldan
// ASU ID: 1223945385
// ASU Email address: esroldan@asu.edu
// Description:
//********************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Each Car will have a unique Vin
struct Car
{
    string model, make;
    int vin;        //Vehicle Identification Number
    double price;
};

//class MaxHeap represents a max heap that contains Car objects. The underline data structure
//is a one dimensional array of Cars.
class MaxHeap
{
private:
    struct Car* carArr;	//an array of Cars
    int capacity, size;

public:
    MaxHeap(int capacity);
    ~MaxHeap();

    Car* getCarArr();
    int getSize();
    int getCapacity();
    int isFound(int aVin);
    bool heapIncreaseVIN(int index, Car oneCarWithNewVIN);
    bool heapInsert(int vin, string model, string make, double price);
    void heapify(int index);
    Car getHeapMax();
    void extractHeapMax();
    int leftChild(int parentIndex);
    int rightChild(int parentIndex);
    int parent(int childIndex);
    void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
MaxHeap::MaxHeap(int capacity)
{
    //Add your own code
    //----
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
    //Add your own code
    //----
    cout << "\nThe number of deleted cars is: " << carCount << endl;
}

//****************************************************
//increase the Car's VIN located at the specific index
bool MaxHeap::heapIncreaseVIN(int index, Car oneCarWithNewVIN)
{
    if (//---- )
                    {
                            cout << "\nIncrease VIN error: index out of range" << endl;
                    return false;
                    }

    //Add your own code
    //----
    //----

}

//Add your own code to finish other functions
//----
//----

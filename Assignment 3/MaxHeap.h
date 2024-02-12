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
    carArr = new Car[capacity];
    this->capacity = capacity;
    this->size = 0;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
    int carCount = 0;
    for(int i = 0; i < size; i++) {
        //delete carArr[i];
        carCount++;
    }
    delete[] carArr;
    cout << "The number of deleted cars is: " << carCount << endl;
}

Car* MaxHeap::getCarArr() {
    return carArr;
}

int MaxHeap::getSize() {
    return size;
}

int MaxHeap::getCapacity() {
    return capacity;
}

int MaxHeap::isFound(int aVin) {
    int ind = -1;
    for(int i = 0; i < size; i++) {
        if(carArr[i].vin == aVin) {
            ind = i;
            break;
        }
    }
    return ind;
}

bool MaxHeap::heapIncreaseVIN(int index, Car oneCarWithNewVIN) {
    int i = oneCarWithNewVIN.vin;
    if(carArr[index].vin > i) {
        return false;
    } else {
        carArr[index].vin = i;
        while(index >= 0 && carArr[parent(index)].vin < carArr[index].vin) {
            Car temp = carArr[parent(index)];
            carArr[parent(index)] = carArr[index];
            carArr[index] = temp;
            index = parent(index);
        }
    }
}

bool MaxHeap::heapInsert(int vin, std::string model, std::string make, double price) {
    bool duplicate = false;
    for(int i = 0; i < size; i++) {
        if(vin == carArr[i].vin) {
            duplicate = true;
        }
    }
    if(duplicate) {
        return false;
    }
    if(size >= capacity) {
        capacity *= 2;
        Car* temp = new Car[capacity];
        for(int i = 0; i < size; i++) {
            temp[i] = carArr[i];
        }
        delete [] carArr;
        carArr = temp;

        cout << "\nReach the capacity limit, double the capacity now.\n";
        cout << "\nThe new capacity now is " << capacity << "\n";
    }

    Car* newCar = new Car();
    newCar->vin = vin;
    newCar->model = model;
    newCar->make = make;
    newCar->price = price;

    carArr[size] = *newCar;
    size++;
    heapIncreaseVIN(size - 1, *newCar);

    return true;
}

void MaxHeap::heapify(int index) {
    int left = leftChild(index);
    int right = rightChild(index);
    int largest;
    if(index <= size && carArr[left].vin > carArr[index].vin) {
        largest = left;
    } else {
        largest = index;
    }
    if(index <= size && carArr[right].vin > carArr[index].vin) {
        largest = right;
    }
    if(largest != index) {
        Car temp = carArr[index];
        carArr[index] = carArr[largest];
        carArr[largest] = temp;

        heapify(largest);
    }
}

void MaxHeap::extractHeapMax() {
    Car max = carArr[0];
    carArr[0] = carArr[size - 1];
    size--;
    heapify(0);
}

int MaxHeap::leftChild(int parentIndex) {
    return parentIndex * 2;
}

int MaxHeap::rightChild(int parentIndex) {
    return parentIndex * 2 + 1;
}

int MaxHeap::parent(int childIndex) {
    return childIndex / 2;
}

void MaxHeap::printHeap() {
    if(size == 0) {
        cout << "Empty heap, no elements";
        return;
    }
    cout << "\nHeap capacity = " << capacity << "\n";
    cout << "\nHeap size = " << size << "\n\n";
    for(int i = 0; i < size; i++) {
        cout << left;
        cout << setw(8) << carArr[i].vin
             << setw(12) << carArr[i].model
             << setw(12) << carArr[i].make
             << setw(8) << fixed << setprecision(2) << carArr[i].price << endl;
    }
}
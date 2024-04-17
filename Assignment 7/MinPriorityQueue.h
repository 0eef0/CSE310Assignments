//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Name of Author: Ethan Roldan
// ASU ID: 1223945385
// Description: //---- is where you should add your own code
//********************************************************************

//include necessary header file here
//----
#include "ArrivalList.h"

using namespace std;

//represent each node of the graph which is a departure location
//with all the relevant info.
struct Departure
{
    string depAddress;
    double d;
    struct Departure* pi;
    ArrivalList* arrList;
};

//class MinPriorityQueue represents a Min-heap that contains Departure objects.
class MinPriorityQueue
{
private:
    struct Departure* departureArr;	//a Departure array
    int capacity, size;

public:
    MinPriorityQueue(int capacity); //
    ~MinPriorityQueue(); //

    Departure* getDepartureArr(); //
    int getSize(); //
    int getCapacity(); //
    int isFound(string oneDepAddress); //
    bool decreaseKey(int index, Departure oneDepartureWithNewDValue); //
    bool insert(Departure oneDeparture); //
    void heapify(int index); //
    Departure getHeapMin(); //
    void extractHeapMin(); //
    int leftChild(int parentIndex); //
    int rightChild(int parentIndex); //
    int parent(int childIndex); //
    void printHeap(); //
    void build_min_heap();

    //add other function definitions here if 100% necessary
    //----
};


//*********************************************************
void MinPriorityQueue::printHeap()
{

    cout << "\nHeap size = " << getSize() << "\n" << endl;

    cout << left;
    cout << setw(15) << "Departure"
         << setw(12) << "d Value"
         << setw(15) << "PI"
         << "Arrival List" << endl;

    for(int i = 0; i < size; i++) {
        string nodeParent;
        if(departureArr[i].pi == nullptr) {
            nodeParent = "No Parent";
        } else {
            nodeParent = departureArr[i].pi->depAddress;
        }
        cout << left;
        cout << setw(15) << departureArr[i].depAddress
             << setw(12) << fixed << setprecision(2) << departureArr[i].d
             << setw(15) << nodeParent;
        departureArr[i].arrList->printArrivalList();
        cout << endl;
    }
}

//************************************************************
//when you create the dummy node, initialize its d value to be
//50000 which represents infinite large
bool MinPriorityQueue::insert(Departure oneDeparture)
{
    if(size >= capacity) {
        capacity *= 2;
        Departure* temp = new Departure[capacity];
        for(int i = 0; i < size; i++) {
            temp[i] = departureArr[i];
        }
        delete[] departureArr;
        departureArr = temp;
    }

    departureArr[size] = oneDeparture;
    size++;
    decreaseKey(size - 1, oneDeparture);

    return true;
}

//****************************************************************************
//Given the original departureArr, the function build a min-heap by using d value
//void MinPriorityQueue::build_min_heap();
//{
//
//}

//According to above class definition, define all other functions accordingly
MinPriorityQueue::MinPriorityQueue(int capacity) {
    departureArr = new Departure[capacity];
    this->capacity = capacity;
    size = 0;
}

MinPriorityQueue::~MinPriorityQueue() {
    delete[] departureArr;
   // cout << "Deleted " << size << " departures";
}

int MinPriorityQueue::getSize() {
    return size;
}
int MinPriorityQueue::getCapacity() {
    return capacity;
}
Departure* MinPriorityQueue::getDepartureArr() {
    return departureArr;
}

int MinPriorityQueue::isFound(std::string oneDepAddress) {
    int index = -1;
    for(int i = 0; i < size; i++) {
        if(oneDepAddress.compare(departureArr[i].depAddress) == 0) {
            index = i;
            break;
        }
    }
    return index;
}

bool MinPriorityQueue::decreaseKey(int index, Departure oneDepartureWithNewDValue) {
    if (departureArr[index].d < oneDepartureWithNewDValue.d) {
        return false;
    } else {
        departureArr[index].d = oneDepartureWithNewDValue.d;
        departureArr[index].pi = oneDepartureWithNewDValue.pi;
        while (index > 0 && departureArr[parent(index)].d > departureArr[index].d) {
            // Swap the elements and update the index
            Departure temp = departureArr[index];
            departureArr[index] = departureArr[parent(index)];
            departureArr[parent(index)] = temp;
            index = parent(index); // Update the index
        }
        return true;
    }
}


int MinPriorityQueue::leftChild(int parentIndex) {
    return parentIndex * 2 + 1;
}

int MinPriorityQueue::rightChild(int parentIndex) {
    return parentIndex * 2 + 2;
}

int MinPriorityQueue::parent(int childIndex) {
    return (childIndex - 1) / 2;
}

Departure MinPriorityQueue::getHeapMin() {
    return departureArr[0];
}
void MinPriorityQueue::extractHeapMin() {
    if(size <= 0) {
        throw out_of_range("Heap is empty");
    }

    Departure temp = departureArr[0];
    departureArr[0] = departureArr[size - 1];
    departureArr[size - 1] = temp;
    size--;
    heapify(0);
}

void MinPriorityQueue::heapify(int index) {
    int left = leftChild(index);
    int right = rightChild(index);
    int smallest = index;
    if(left < size && departureArr[left].d < departureArr[smallest].d) {
        smallest = left;
    }
    if(right < size && departureArr[right].d < departureArr[smallest].d) {
        smallest = right;
    }
    if(smallest != index) {
        Departure temp = departureArr[index];
        departureArr[index] = departureArr[smallest];
        departureArr[smallest] = temp;

        heapify(smallest);
    }
}
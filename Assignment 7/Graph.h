//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Name of Author: Ethan Roldan
// ASU ID: 1223945385
// Description: This is the header file that defines a weighted directed graph
//********************************************************************

//include necessary header file here
//----
#include "MinPriorityQueue.h"

using namespace std;

class Graph
{
private:
    int numOfNode;
    MinPriorityQueue* departureHeap;     //adjacency list of the graph, it is a min-heap
    //of Departure objects based on d value
public:
    Graph(int numOfNode, MinPriorityQueue* departureHeap);
    ~Graph();
    MinPriorityQueue* getDepartureHeap();
    void printGraph();
    void initialize_single_source(string sourceDepAddress);
    void relax(Departure u, Departure v);
    int findOneDeparture(string aDepAddress);
    void dijkstra(string sourceDepAddress);
    void printDijkstraPath(string sourceDepAddress); // 679
    string createShortestPath(Departure u);

    //add any auxiliary functions here in case you need them
    //----
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfNode, MinPriorityQueue* departureHeap)
{
    this->numOfNode = numOfNode;
    this->departureHeap = departureHeap;
}

//*******************************************************************
//Destructor Graph::~Graph()
Graph::~Graph()
{

}

//*******************************************************************
//void printGraph();
//This function prints the graph. It traverse through the vertex list,
//then for each vertex, it print its adjacent list from head to tail.
void Graph::printGraph() {
    departureHeap->printHeap();
}

MinPriorityQueue* Graph::getDepartureHeap() {
    return departureHeap;
}

//According to above class definition, define all other functions accordingly
void Graph::initialize_single_source(std::string sourceDepAddress) {
    int index = departureHeap->isFound(sourceDepAddress);
    Departure temp = departureHeap->getDepartureArr()[index];
    temp.d = 0;
    departureHeap->decreaseKey(index, temp);
}

void Graph::printDijkstraPath(std::string sourceDepAddress) {
    cout << left;
    cout << setw(14) << "Arrival"
         << setw(20) << "Shortest Time(h)"
         << "Shortest Path" << endl;

    Departure* arr = departureHeap->getDepartureArr();

    dijkstra(sourceDepAddress);

    for(int i = numOfNode - 1; i >= 0; i--) {
        if(arr[i].d < 10000) {
            cout << left;
            cout << setw(14) << arr[i].depAddress
                 << setw(20) << setprecision(2) << arr[i].d
                 << createShortestPath(arr[i]) << endl;
        } else {
            cout << left;
            cout << setw(14) << arr[i].depAddress
                 << setw(20) << "None exist"
                 << "None exist" << endl;
        }
    }
}
void Graph::dijkstra(std::string sourceDepAddress) {
    initialize_single_source(sourceDepAddress);

    while(departureHeap->getSize() > 0) {
        Departure temp = departureHeap->getHeapMin();
        departureHeap->extractHeapMin();

        if(temp.arrList->getHead() != nullptr) {
            Arrival *arrList = temp.arrList->getHead();
            while (arrList != nullptr) {
                relax(temp, departureHeap->getDepartureArr()[departureHeap->isFound(arrList->arrAddress)]);
                arrList = arrList->next;
            }
            departureHeap->printHeap();
        } else {
            return;
        }
    }
}
void Graph::relax(Departure u, Departure v) {
    Arrival* temp = u.arrList->findArrival(v.depAddress);
    string roadType = temp->roadCategory;
    int speed = (roadType.compare("I") == 0) ? 65 : (roadType.compare("A") == 0) ? 55 : (roadType.compare("C") == 0) ? 45 : 25;
    if(temp->distance / speed + u.d < v.d) {
        v.d = temp->distance / speed + u.d;
        v.pi = &u;
        departureHeap->decreaseKey(departureHeap->isFound(v.depAddress), v);
    }
}
string Graph::createShortestPath(Departure u) {
    if(u.pi == nullptr) return u.depAddress;

//    string path = "";
//    if(u.pi == nullptr) {
//        return u.depAddress;
//    } else {
//        path += createShortestPath(*u.pi);
//    }
    cout << u.pi->depAddress;
    return "test";
}

int Graph::findOneDeparture(std::string aDepAddress) {
    return departureHeap->isFound(aDepAddress);
}
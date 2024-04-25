//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Name of Author: Ethan Roldan
// ASU ID: 1223945385
// Description: This is the header file that defines a weighted directed graph
//********************************************************************
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

// iterates through the heap and sets the given departure object address to zero
void Graph::initialize_single_source(std::string sourceDepAddress) {
    int index = departureHeap->isFound(sourceDepAddress);
    Departure temp = departureHeap->getDepartureArr()[index];
    temp.d = 0;
    departureHeap->decreaseKey(index, temp);
}

// this is the function that puts everything together and prints out the result
void Graph::printDijkstraPath(std::string sourceDepAddress) {
    // run dijkstra algorithm
    dijkstra(sourceDepAddress);

    // print header
    cout << left;
    cout << setw(14) << "Arrival"
         << setw(20) << "Shortest Time(h)"
         << "Shortest Path" << endl;

    // prepares an array to print out the results
    Departure* depList = departureHeap->getDepartureArr();
    Departure* sortDepList = new Departure[departureHeap->getSize()];
    for(int i = 0; i < departureHeap->getSize(); i++) sortDepList[i] = depList[i];

    for (int i = 0; i < departureHeap->getSize() - 1; ++i) {
        for (int j = 0; j < departureHeap->getSize() - i - 1; ++j) {
            if (sortDepList[j].d > sortDepList[j + 1].d) {
                swap(sortDepList[j], sortDepList[j + 1]);
            }
        }
    }

    // prints out the dijkstra results
    for(int i = 0; i < departureHeap->getSize(); i++) {
        if(sortDepList[i].d < 10000) {
            string path = "";
            Departure* curr = &sortDepList[i];
            while(curr != nullptr) {
                path = "->" + curr->depAddress + path;
                curr = curr->pi;
            }
            path.erase(0, 2);

            cout << left;
            cout << setw(14) << sortDepList[i].depAddress
                 << setw(20) << setprecision(2) << sortDepList[i].d
                 << path << endl;
        } else {
            cout << left;
            cout << setw(14) << sortDepList[i].depAddress
                 << setw(20) << "None exist"
                 << "None exist" << endl;
        }
    }
}

// dijkstra algorithm
void Graph::dijkstra(std::string sourceDepAddress) {
    // set given departure object to zero
    initialize_single_source(sourceDepAddress);

    // create a list of departures and a new priority queue
    Departure* depList = departureHeap->getDepartureArr();
    MinPriorityQueue* q = new MinPriorityQueue(numOfNode);

    // populate the new queue q
    for(int i = 0; i < numOfNode; i++) q->insert(depList[i]);
    q->build_min_heap();

    // dijkstra algorithm
    while(q->getSize() > 0) {
        Departure u = q->getHeapMin();
        q->extractHeapMin();

        ArrivalList* adj = u.arrList;
        Arrival* curr = adj->getHead();
        while(curr != nullptr) {
            if(departureHeap->isFound(curr->arrAddress) != -1) {
                Departure &v = depList[departureHeap->isFound(curr->arrAddress)];
                relax(u, v);

                if(q->isFound(v.depAddress) > -1 && v.d < q->getDepartureArr()[q->isFound(v.depAddress)].d) q->decreaseKey(q->isFound(v.depAddress), v);
            }
            curr = curr->next;
        }
    }
    delete q;
}

// given two departure objects, change the distance from u to v if shorter path found
void Graph::relax(Departure u, Departure v) {
    Departure* depList = departureHeap->getDepartureArr();
    Arrival* uA = u.arrList->findArrival(v.depAddress);
    string roadType = uA->roadCategory;
    int speed = (roadType.compare("I") == 0) ? 65 : (roadType.compare("A") == 0) ? 55 : (roadType.compare("C") == 0) ? 45 : 25;
    int uI = findOneDeparture(u.depAddress);
    int vI = findOneDeparture(v.depAddress);

    if(uA->distance / speed + depList[uI].d < depList[vI].d) {
        depList[vI].d = uA->distance / speed + depList[uI].d;
        depList[vI].pi = & depList[uI];
    }
}

int Graph::findOneDeparture(std::string aDepAddress) {
    return departureHeap->isFound(aDepAddress);
}
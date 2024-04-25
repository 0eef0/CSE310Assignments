//********************************************************************
// ASU CSE310 Assignment #8 Spring 2024
// Name of Author: Ethan Roldan
// ASU ID: 1223945385
// Description: This is the header file that defines an undirected graph
//              with an array of vertice and edges
//********************************************************************

//include necessary header file here
//----
#include "Edge.h"

using namespace std;

class Graph
{
private:
    int V, E;         //number of vertice and edges in the graph
    City* cityArr;    //an array of City objects
    Edge* edgeArr;    //an array of Edge objects

public:
    Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray);
    void destructor();
    void make_set(City* aCity);
    City* find_set(City* aCity);
    void link(City* aCity, City* bCity);
    void Union(City* aCity, City* bCity);
    void sortEdges();

    void MST_Kruskal();

    void mergeSort(int start, int end);
    void merge(int start, int mid, int end);
};

void Graph::make_set(City *aCity) {
    if(aCity->parent == nullptr) {
        aCity->parent = aCity;
        aCity->rank = 0;
    }
}
City* Graph::find_set(City *aCity) {
    if(aCity != aCity->parent) {
        aCity->parent = find_set(aCity->parent);
    }
    return aCity->parent;
}
void Graph::link(City *aCity, City *bCity) {
    if(aCity->rank > bCity->rank) {
        bCity->parent = aCity;
    } else {
        aCity->parent = bCity;
        if(aCity->rank == bCity->rank) bCity->rank++;
    }
}
void Graph::Union(City *aCity, City *bCity) {
    link(find_set(aCity), find_set(bCity));
}

void Graph::mergeSort(int start, int end) {
    if(start < end) {
        int mid = start + (end - start) / 2;
        mergeSort(start, mid);
        mergeSort(mid + 1, end);
        merge(start, mid, end);
    }
}

void Graph::merge(int start, int mid, int end) {
    int leftSize = mid - start + 1;
    int rightSize = end - (mid + 1) + 1;
    Edge* leftArr = new Edge[leftSize];
    Edge* rightArr = new Edge[rightSize];

    for(int i = 0; i < leftSize; i++) leftArr[i] = edgeArr[start + i];
    for(int j = 0; j < rightSize; j++) rightArr[j] = edgeArr[mid + 1 + j];

    int i = 0, j = 0;
    int k = start;
    while (i < leftSize && j < rightSize) {
        if (leftArr[i].getDistance() <= rightArr[j].getDistance()) {
            edgeArr[k] = leftArr[i];
            i++;
        } else {
            edgeArr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        edgeArr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < rightSize) {
        edgeArr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}


Graph::Graph(int numOfCities, int numOfEdges, City *cityArray, Edge *edgeArray) {
    this->V = numOfCities;
    this->E = numOfEdges;
    this->cityArr = cityArray;
    this->edgeArr = edgeArray;
}

//*******************************************************************
//This function performs the Kruskal algorithm on the graph.
void Graph::MST_Kruskal()
{
    cout << "MST Kruskal Algorithm Result\n" << endl;
    double totalDistance = 0.0;

    for(int i = 0; i < E; i++) make_set(&cityArr[i]);

    mergeSort(0, E - 1);

    for(int i = 0; i < E; i++) {
        Edge curr = edgeArr[i];

        if(find_set(curr.getCity1()) != find_set(curr.getCity2())) {
            edgeArr[i].printEdge();
            totalDistance += edgeArr[i].getDistance();
            Union(curr.getCity1(), curr.getCity2());
        }
    }

    cout << "=================================================" << endl;
    cout << "Total Distance: " << totalDistance << endl;
}
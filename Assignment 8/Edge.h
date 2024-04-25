//******************************************************************************
// ASU CSE310 Assignment #8 Spring 2024
// Name of Author: Ethan Roldan
// ASU ID: 1223945385
// Description: this header file defines an edge in the graph. Each edge
//              has 3 attributes, namely two Cities and the distance between them
//*******************************************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//City represents one vertex of the graph
struct City
{
    string cityName;
    int rank;
    struct City* parent;

    //constructor
    City(string name)
    {
        cityName = name;
        rank = 0;
        parent = nullptr;
    }

    //default constructor. C++ don't provide one, need it here.
    City()
    {
        cityName = "";
        rank = 0;
        parent = nullptr;
    }
};

//class Edge represents one edge of the graph which connects two City objects
class Edge
{
private:
    struct City* city1;
    struct City* city2;
    double distance;

public:
    Edge(City* city1, City* city2, double distance);
    Edge();  //default constructor
    ~Edge();
    City* getCity1();
    City* getCity2();
    double getDistance();
    void printEdge();
};

//finish each function according to above definition
Edge::Edge() {
    city1 = new City();
    city2 = new City();
    distance = 10000;
}
Edge::Edge(City *city1, City *city2, double distance) {
    this->city1 = city1;
    this->city2 = city2;
    this->distance = distance;

    //cout << "Creating Edge: " << city1->cityName << city2->cityName << distance << "\n";
}
Edge::~Edge() {

}

City* Edge::getCity1() {
    return city1;
}
City* Edge::getCity2() {
    return city2;
}
double Edge::getDistance() {
    return distance;
}


void Edge::printEdge()
{
    cout << left;
    cout << setw(15) << city1->cityName
         << setw(8) << "<--->"
         << setw(15) << city2->cityName
         << setw(3) << " = "
         << setw(8) << right << fixed << setprecision(2) << getDistance()
         << endl;
}
//************************************************************************
// ASU CSE310 Assignment #8 Spring 2024
// ASU ID: 1223945385
// Name: Ethan Roldan
// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph.
// //---- is where you need to add your own codes
//**************************************************************************

//include necessary header file here
#include "Graph.h"

using namespace std;

void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance);
int searchCity(City* oneCityArray, int size, string oneCityName);

int main()
{
    int V, E;        //number of vertices and edges

    //cout << "Enter number of vertices and edges: " << endl;
    cin >> V >> E;
    cin.ignore(20, '\n');

    //a City array used to store all vertices (Cities) of the graph
    City* cityArray = new City[V];

    //an array used to store all edges of the graph
    Edge* edgeArray = new Edge[E];

    int i =0, j=0; //index for cityArray and edgeArray

    //local variables
    City* city1;
    City* city2;
    Edge* aNewEdge;

    string oneLine;

    //cout << "Enter one departure and its arrival city info." << endl;
    getline(cin, oneLine);

    while(oneLine.compare("End") != 0)
    {
        //get one line of the input, extract the first token
        //create a City object if it does not exist in cityArray,
        //insert it inside the cityArray. This will be first vertex of the 'aNewEdge'
        string cityOneName = oneLine.substr(0, oneLine.find(','));
        oneLine.erase(0, oneLine.find(',') + 1);

        int cityOneIndex = searchCity(cityArray, V, cityOneName);
        if(cityOneIndex == -1) {
            cityOneIndex = i;
            cityArray[cityOneIndex] = City(cityOneName);
            i++;
        }
        //extract the arrival city info. check whether it exists in
        //cityArray or not, if not, create a new City, add it inside.
        //This city will be the second point of the 'aNewEdge'
        while(oneLine.find('(') != string::npos) {
            string cityTwoName = oneLine.substr(0, oneLine.find('('));
            oneLine.erase(0, oneLine.find('(') + 1);
            double dist = stod(oneLine.substr(0, oneLine.find(')')));
            oneLine.erase(0, oneLine.find(',') + 1);

            int cityTwoIndex = searchCity(cityArray, V, cityTwoName);
            if(cityTwoIndex == -1) {
                cityTwoIndex = i;
                cityArray[cityTwoIndex] = City(cityTwoName);
                i++;
            }

            edgeArray[j] = Edge(&cityArray[cityOneIndex], &cityArray[cityTwoIndex], dist);
            j++;
        }


        cout << "\n";


        //by using the two cities we got above, create a new edge, add
        //it inside edgeArray

        //get next line
        getline(cin, oneLine);
    } //repeat until the 'End'

    //Create a Graph object by using cityArray and edgeArray
    Graph* graph = new Graph(V, E, cityArray, edgeArray);

    //Run Kruskal MST algorithm on above graph
    graph->MST_Kruskal();
}

//****************************************************************
//By giving a string, for example 'Dallas(1456.5)', this function
//extract the arrival city name 'Dallas' and distance '1456.5'
//Note: the delimiter is left or right parenthesis
//****************************************************************
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance)
{
    //----
    //----
}

//*********************************************************************
//Given a city name, this function searches cityArray and it return the
//index of the City if it exists, otherwise it returns -1
//****************************************************************
int searchCity(City* oneCityArray, int arraySize, string oneCityName)
{
    int index = -1;
    for(int i = 0; i < arraySize; i++) {
        if(oneCityArray[i].cityName == oneCityName) {
            index = i;
        }
    }
    return index;
}
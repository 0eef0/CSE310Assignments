//********************************************************************
// ASU CSE310 Spring 2024 Assignment #7
// Name: Ethan Roldan
// ASU ID: 1223945385
// Description: This is the driver file that prompts users for a graph and then several vertices. Then it will run dijkstra on said vertices.
//********************************************************************
#include "Graph.h"

using namespace std;

void getDepartureInfo(string oneLine, string& depAddress, ArrivalList* arrList);

int main()
{
    int count;       //a variable for number of nodes
    string oneLine, sourceDepAddress;
    string answer = "yes";       //a variable to decide whether to run Dijkstra multiple times or not

    //cout << "Enter number of departure address: ";
    cin >> count;
    cin.ignore(20, '\n');

    //Create an array called 'departureArr' that holds 'count' number of Departure objects
    Departure* departureArr = new Departure[count];

    //Initialize departureArr. Note: you will need to initialize each of the instance variable
    //including arrival list
    for(int i = 0; i < count; i++)
    {
        departureArr[i].d = 10000.0 + i;  //***this is to make sure each node has different d value
        departureArr[i].pi = nullptr;
        departureArr[i].arrList = new ArrivalList();
    }

    //get input line by line and create the departureArr
    for(int i = 0; i < count; i++)
    {
        getline(cin, oneLine);
        getDepartureInfo(oneLine, departureArr[i].depAddress, departureArr[i].arrList);
    }

    //create a Graph object
    MinPriorityQueue* queue = new MinPriorityQueue(count);
    for(int i = 0; i < count; i++) {
        queue->insert(departureArr[i]);
    }
    Graph* graph;

    //print the graph adjacency list before running Dijkstra algorithm
    cout << "\nPrint the graph adjacency list before running Dijkstra algorithm" << endl;
    //----

    queue->printHeap();

    //Next you need to design a sentinel-value controlled while loop base on 'answer'
    //If user answer is 'yes', get departure address, run Dijkstra algorithm, print
    //shortest traveling time and path, then ask the user whether he want to continue or not...

    while(answer.compare("yes") == 0) {

        // initialize a new queue and graph for specific source vertice
        queue = new MinPriorityQueue(count);
        for(int i = 0; i < count; i++) {
            queue->insert(departureArr[i]);
        }
        graph = new Graph(count, queue);

        // Prompt user with a source address and run dijkstra algorithm on it
        cout << setfill(' ') << setw(25) << "\nEnter departure address: \n";
        getline(cin, oneLine);
        int index = queue->isFound(oneLine);
        if(index > -1) {
            cout << "\n\nPrint the Dijkstra algorithm running result\n";
            cout << "\nDeparture address: " << oneLine << "\n\n";
            graph->printDijkstraPath(departureArr[index].depAddress);
        } else {
            cout << oneLine << " does NOT exist";
        }

        // Prompt user whether or not they would like to run dijkstra on another vertice
        cout << "\n\nFind shortest path for another departure address(yes or no): \n";
        getline(cin, answer);

        // delete the graph and queue
        delete graph;
        delete queue;

    }

    cout << "Program terminate";
}

//********************************************************************************
//Give one line in input file, this function extract tokens and get departure address
//and all arrival info.

void getDepartureInfo(string oneLine, string& depAddress, ArrivalList* arrList)
{
    depAddress = oneLine.substr(0,1);
    oneLine.erase(0, 2);

    while(oneLine.find('/') != string::npos) {
        string rest = oneLine.substr(0, oneLine.find(','));
        string strAddress = rest.substr(0,1);
        double distance = stod(rest.substr(2, rest.find('/')));
        string roadCategory (1, rest.at(rest.find('/') + 1));

        arrList->addArrival(strAddress, distance, roadCategory);
        oneLine.erase(0, oneLine.find(',') + 1);
    }
    cout << "\n";
}
//************************************************************************
// ASU CSE310 Assignment #6 Spring 2024
// Author: Ethan Roldan
// ASU ID:  1223945385
// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.
//**************************************************************************

#include "RedBlackTree.h"

using namespace std;

//This function used to get the key of a Car which is the combination of vin, model & make
void getCarKey(string oneLine, int& vin, string& model, string& make);

//This function used to get all info. of a Car
void getCarInfo(string oneLine, int& vin, string& model, string& make, double& price);

int main()
{

    int vin;
    string model, make;
    double price;
    string command, oneLine, token;
    string delimiter = ",";

    int pos = 0;

    //Create a RedBlackTree object here, use it throughout the program
    //----
    //----
    RedBlackTree* tree = new RedBlackTree();

    do
    {
        getline(cin, oneLine);
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);
        command = token;
        oneLine.erase(0, pos + delimiter.length());

        if(command.compare("quit")==0)
        {
            cout << "Command: quit" << endl;
            delete tree;
            break;
        }
        else if(command.compare("tree_preorder")==0)
        {
            cout << "\nCommand: tree_preorder" << endl;
            tree->treePreorder();
        }
        else if(command.compare("tree_inorder")==0)
        {
            cout << "\nCommand: tree_inorder" << endl;
            tree->treeInorder();
        }
        else if(command.compare("tree_postorder")==0)
        {
            cout << "\nCommand: tree_postorder" << endl;
            tree->treePostorder();
        }
        else if(command.compare("tree_minimum")==0)
        {
            cout << "\nCommand: tree_minimum" << endl;
            tree->treeMinimum();

        }
        else if(command.compare("tree_maximum")==0)
        {
            cout << "\nCommand: tree_maximum" << endl;
            tree->treeMaximum();
        }
        else if(command.compare("tree_predecessor")==0)
        {
            getCarKey(oneLine, vin, model, make);
            cout << "\nCommand: tree_predecessor" << endl;
            tree->treePredecessor(vin, model, make);
        }
        else if(command.compare("tree_successor")==0)
        {
            getCarKey(oneLine, vin, model, make);
            cout << "\nCommand: tree_successor" << endl;
            tree->treeSucessor(vin, model, make);
        }
        else if(command.compare("tree_search")==0)
        {
            getCarKey(oneLine, vin, model, make);
            cout << "\nCommand: tree_search" << endl;
            tree->treeSearch(vin, model, make);
        }
        else if(command.compare("tree_insert")==0)
        {
            getCarInfo(oneLine, vin, model, make, price);

            cout << "\nCommand: tree_insert" << endl;
            cout << left;
            cout << setw(8)  << vin
                 << setw(12) << model
                 << setw(12) << make
                 << setw(10) << fixed << setprecision(2) << price << endl;

            tree->treeInsert(vin, model, make, price);
        }
    } while(true);  //continue until 'quit'
    return 0;
}

//*********************************************************************************
//This function from one line, extracts the vin, model, make of a Car.
//You should already know how to extract tokens from Assignment5.cpp file
void getCarKey(string oneLine, int& vin, string& model, string& make)
{
    vin = stoi(oneLine.substr(0, oneLine.find(',')));
    oneLine.erase(0,oneLine.find(',') + 1);

    model = oneLine.substr(0, oneLine.find(','));
    oneLine.erase(0,oneLine.find(',') + 1);

    make = oneLine;
}

//************************************************************************************************
//This function from one line, extract tokens and get all info. of a Car
void getCarInfo(string oneLine, int& vin, string& model, string& make, double& price)
{
    vin = stoi(oneLine.substr(0, oneLine.find(',')));
    oneLine.erase(0,oneLine.find(',') + 1);

    model = oneLine.substr(0, oneLine.find(','));
    oneLine.erase(0,oneLine.find(',') + 1);

    make = oneLine.substr(0, oneLine.find(','));
    oneLine.erase(0,oneLine.find(',') + 1);

    price = stod(oneLine);
}
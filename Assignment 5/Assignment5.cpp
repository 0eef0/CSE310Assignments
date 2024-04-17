// ASU CSE310 Assignment #5 Spring 2024
// Name of Author: Ethan Roldan
// ASU ID: 1223945385
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.
// ---- is where you need to add your own code

/*****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Car
//   object's hash value.
 // My hash function alternates between adding and subtracting the ASCII values of make+model+(vin/2) then getting the absolute value of that
//(2)Did your hash function work well? For each of the four test cases, list here
//   your hash function's performance ratio and the longest LinkedList size.
 // 1) 1.25 (4)
 // 2) 1.47 (8), 1.60 (8)
 // 3) 1.69 (8), 1.38 (6)
 // 4) 1.73 (30), 1.72 (29)
//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
 // I am honestly pretty satisfied with how my hash function turned out
********************************************************************************/

#include "Hash.h"
#include <sstream>

using namespace std;

//This function used to get a Car key which is the combination of model, make and vin
void getKey(string oneLine, string& command, string& model, string& make, int& vin);

int main()
{
    int size = 0 ;
    int numOfCommand = 0;
    string model, make;
    int vin;
    double price;

    //declare any other necessary variables here
    //----

    cout << "Enter the size of the hash table: ";
    cin >> size;
    cin.ignore(20, '\n');

    //Instantiate the hash table with the relevant number of slots
    //----
    Hash* hashTable = new Hash(size);
    double elems = 0;
    string firstToken;
    string command;

    do {
        //use this do..while loop to repeatly get one line Car info. and extract tokens
        //create one Car object and insert it inside the hashTable until seeing the message
        //"InsertionEnd" to terminate
        //----
        //----
        getline(cin, command);
        if(command.compare("InsertionEnd") == 0) {
            break;
        } else {
            model = command.substr(0, command.find(','));
            command = command.substr(command.find(',') + 1);
            make = command.substr(0, command.find(','));
            command = command.substr(command.find(',') + 1);
            vin = stoi(command.substr(0, command.find(',')));
            command = command.substr(command.find(',') + 1);
            price = stod(command);
            //cout << model << " " << make << " " << vin << " " << price << "\n";
            hashTable->hashInsert(model,make,vin,price);
            elems++;
        }

    } while(true);

    cout << "\nEnter number of commands: ";   //***need to comment out in submitting
    cin >> numOfCommand;
    cin.ignore(20, '\n');

    for(int i= 0; i < numOfCommand; i++)
    {
        //get one line command, extract the first token, if only one token
        getline(cin, firstToken);
        if(firstToken.compare("hashDisplay") == 0)
        {
            hashTable->hashDisplay();
        }
        else if(firstToken.compare("hashLoadFactor") == 0) {
            cout << '\n' << "The ideal load factor is: " << setprecision(2) << fixed << ((double) elems / size);
            cout << '\n' << "My hash table real load factor is: " << hashTable->hashLoadFactor() << ".00";
            cout << '\n' << "My hash table performance ratio is: " << setprecision(2) << fixed << (hashTable->hashLoadFactor() / ((double) elems / size)) << "\n\n";
        } else {//more than one token, check the command name, extract the remaining tokens
            //----
            //----
            getKey(firstToken, command, model, make, vin);
            if(command.compare("hashSearch") == 0) {
                hashTable->hashSearch(model,make,vin);
            } else if(command.compare("hashDelete") == 0) {
                hashTable->hashSearch(model,make,vin);
                hashTable->hashDelete(model,make,vin);
                elems--;
            } else {
                cout<<"Invalid command"<<endl;
            }
        }
    } //end for loop
    return 0;
}

//****************************************************************************************
//Given one line, this function extracts the model, make, vin info. of a Car
//This function is completed and given here as a study guide for extracting tokens
void getKey(string oneLine,string& command, string& model, string& make, int& vin)
{
    string delimiter = ",";
    int pos=oneLine.find(delimiter);
    string token = oneLine.substr(0,pos);
    command = token;
    oneLine.erase(0, pos+delimiter.length());

    pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
    model = token;
    oneLine.erase(0, pos+delimiter.length());

    pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
    make = token;
    oneLine.erase(0, pos+delimiter.length());

    pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
    vin = stoi(token);
    oneLine.erase(0, pos+delimiter.length());
}
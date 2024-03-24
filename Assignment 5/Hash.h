// ASU CSE310 Assignment #5 Spring 2024
// Name of Author: Ethan Roldan
// ASU ID: 1223945385
// Description: this is where you need to design functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay
// ---- is where you should add your own code

//only include necessary header file here
//----
#include "LinkedList.h"

using namespace std;

class Hash
{
private:
    LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
    int m;                     //slots number of the hash table
public:
    Hash(int size);
    ~Hash();
    bool hashSearch(string model, string make, int vin);
    bool hashInsert(string model, string make, int vin, double price);
    bool hashDelete(string model, string make, int vin);
    int hashLoadFactor();
    void hashDisplay();
    string makeHashKey(string model, string make, int vin);
    int hashFunction(string key);
};

//constructor
Hash::Hash(int size)
{
    hashTable = new LinkedList[size]; // initalize an array with size amount of hash slots
    m = size; // m represents amount of hash slots
}

//Destructor
Hash::~Hash()
{
    delete hashTable;
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashSearch(string model, string make, int vin)
{
    bool found; // initialze a found variable

    int searchSlot = hashFunction(makeHashKey(model,make,vin)); // find the hash slot we search in
    found = hashTable[searchSlot].searchCar(vin); // if the car is found, then set found to true

    // print the corresponding message depending or not the car was found
    if (found == true)
        cout << "\n" << left
             << setw(18) << model
             << setw(18) << make
             << setw(8)  << vin
             << " is found inside the hash table." << endl;
    else
        cout << "\n" << left
             << setw(18) << model
             << setw(18) << make
             << setw(8)  << vin
             << " is NOT found inside the hash table." << endl;
    return found;
}

//hashInsert inserts a Car with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string model, string make, int vin, double price)
{
    int newSlot = hashFunction(makeHashKey(model,make,vin)); // find the hash slot we add to

    // if the car vin is already registered, then return false
    if(hashTable[newSlot].searchCar(vin)) {
        return false;
    }

    // add the car and return true otherwise
    hashTable[newSlot].insertCar(model,make,vin,price);
    return true;
}

//hashDelete deletes a Car with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashDelete(string model, string make, int vin)
{
    int delSlot = hashFunction(makeHashKey(model,make,vin)); // use the hash function to find the slot we delete from
    bool del = hashTable[delSlot].deleteCar(vin); // delete the car, if the car is deleted, this is true. false otherwise

    // print corresponding message depending on whether or not the car was deleted
    if(del) {
        cout << "\n";
        cout << setw(18) << model
             << setw(18) << make
             << setw(8) << vin
             << " is deleted from hash table." << endl;
    } else {
        cout << "\n";
        cout << setw(18) << model
             << setw(18) << make
             << setw(8) << vin
             << " is NOT deleted from hash table." << endl;
    }
    return del;
}

//This function computes your hash table real load factor
//it is the longest linked list size
int Hash::hashLoadFactor()
{
    int max = -1; // initialize the longest list size
    // iterate through the hash table, if a list size is greater than the current max, replace the max
    for(int i = 0; i < m; i++) {
        if(hashTable[i].getSize() > max) {
            max = hashTable[i].getSize();
        }
    }
    return max;
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
    // iterate through each of the hash slots
    for(int i = 0; i < m; i++) {
        // if a hash slot is empty, then print that it's empty
        if(hashTable[i].getSize() == 0) {
            cout << "hashTable[" << i << "] is empty, size = 0\n" << '\n';
        } else { // if it is not empty, then call the display list function
            cout << "hashTable[" << i << "], size = " << hashTable[i].getSize() << '\n';
            hashTable[i].displayList();
            cout << '\n';
        }
    }
}

// Given a model, make and vin, this function makes a hash key ready for the hash function
string Hash::makeHashKey(string model, string make, int vin) {
    return model + make + to_string(vin/2);
}

//This is the hash function you need to design. Given a
//string key, the function should return the slot number
//where we will hash the key to
int Hash::hashFunction(string key)
{
    // Basic Hash function that adds all ASCII values of make + model + vin/2
    int temp = 0;
    for(int i = 0; i < key.length(); i++) {
        if(i % 2 == 0) { // Alternates adding and subtracting to the hash value
            temp += (int)key[i];
        } else {
            temp -= (int)key[i];
        }
    };
    if(temp < 0) { // If hash value is negative, take absolute value
        temp *= -1;
    }
    return temp % m;
}
// Assignment: ASU CSE310 HW#3 Spring 2024
// Name: Ethan Roldan
// ASU ID: 1223945385
// ASU Email Address: esroldan@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             	//---- is where you should add your own code
//********************************************************************************

//only include the necessary header file
//----
#include "MaxHeap.h"

using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);

int main()
{
	char input1 = 'Z';
	int vin, newVIN;
	string model, make;
    double price;
	int capacity, index = -1;   //array capacity and index
	bool success = false;

	//declare any other variables in case you need them
	//----
    int carInd;
    Car maxCar;
    Car oneCar;

	// instantiate an empty Heap
	MaxHeap* heap1 = nullptr;
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer

		// matches one of the cases
		switch (input1)
		{
			case 'C':	//create empty Heap with the relevant capacity
				cout << "\nPlease enter the heap capacity: ";
				cin >> capacity;
				cin.ignore(20, '\n');	//flush the buffer

                heap1 = new MaxHeap(capacity);

				break;

			case 'D':	//delete the heap, call the destructor explicitly
				cout << "\nDelete the heap\n" << endl;
				delete heap1;
                heap1 = new MaxHeap(5);
				break;

			case 'E':	//Extract the maximum node
                if (heap1 == nullptr)
                    cout << "\nEmpty heap, can NOT extract max" << endl;
                else
                {
                    cout << "\nBefore extract heap max operation:\n";
                    heap1->printHeap();
                    cout << "\nAfter extract heap max operation:\n";
                    heap1->extractHeapMax();
                    heap1->printHeap();
                }
				break;

			case 'F':	//Find a Car
				cout << "\nEnter the car VIN you want to search: ";
				cin >> vin;
				cin.ignore(20, '\n');	//flush the buffer

				carInd = heap1->isFound(vin);
                cout << "\nCar with VIN: " << vin << " is " << ((carInd < 0) ? "NOT " : "") << "found\n";

				break;

			case 'I':	//Insert a Car
				cout << "\nEnter the car model: ";
				cin >> model;

				cout << "\nEnter the car make: ";
				cin >> make;

				cout << "\nEnter the car VIN: ";
				cin >> vin;
				cout << "\nEnter the car price: ";
				cin >> price;
				cin.ignore(20, '\n');	//flush the buffer

				if(heap1->heapInsert(vin,model,make,price)) {
                    cout << "\nCar \"" << model << " " << make << "\" is added\n";
                } else {
                    cout << "\nDuplicated Car. Not added\n";
                    cout << "\nCar \"" << model << " " << make << "\" is NOT added\n";
                }

				break;

			case 'K':	//increase the vin
				cout << "\nEnter the old car VIN you want to increase: ";
				cin >> vin;
				cout << "\nEnter the new car VIN: ";
				cin >> newVIN;
				cin.ignore(20, '\n');	//flush the buffer

                carInd = heap1->isFound(vin);

                if(carInd < 0) {
                    cout << "\nThe old VIN you try to increase does not exist\n";
                }else if(newVIN < vin) {
                    cout << "\nIncrease VIN error: new vin is smaller than current vin\n";
                } else {
                    if(heap1->isDupe(newVIN)) {
                        cout << "\nThe new VIN you entered already exist, increase VIN operation failed\n";
                    } else {
                        Car* newCar = new Car();
                        newCar->vin = newVIN;
                        newCar->model = model;
                        newCar->make = make;
                        newCar->price = price;
                        cout << "\nBefore increase VIN operation:\n";
                        heap1->printHeap();
                        heap1->heapIncreaseVIN(carInd, *newCar);
                        cout << "\nCar with old VIN: " << vin << " is increased to new VIN: " << newVIN << "\n";
                        cout << "\nAfter increase VIN operation: \n";
                        heap1->printHeap();
                    }
                }

				break;

			case 'M':	//get maximum node
                if(heap1->getSize() == 0) {
                    cout << "Empty heap, can NOT get max node\n";
                    break;
                }
                maxCar = heap1->getCarArr()[0];
                cout << "\nThe maximum heap node is:\n";
                cout << left;
                cout << setw(8) << maxCar.vin
                     << setw(12) << maxCar.model
                     << setw(12) << maxCar.make
                     << setw(8) << fixed << setprecision(2) << maxCar.price << endl;

				break;

			case 'P':	//Print heap contents

			    heap1->printHeap();

				break;

			case 'S':	//HeapSort
				cout << "\nHeap sort. Cars will be sorted in increasing order of their VINs" << endl;
                heapSort(heap1);
                heap1->setSize(0);

				break;

			case 'Q':	//Quit
				delete heap1;
				break;

			case '?':	//Display Menu
				printMenu();
				break;

			default:
				cout << "Unknown action\n";
				break;
		}
	} while (input1 != 'Q');
	return 0;
}

//*****************************************************
//Given a max heap, we want to sort it in increasing order according to Car VIN, put the
//sorting result inside another array and print it out
void heapSort(MaxHeap* oneMaxHeap)
{
    int size = oneMaxHeap->getSize();
    Car* carArr = oneMaxHeap->getCarArr();
    for(int i = size - 1; i > 0; i--) {
        Car temp = carArr[i];
        carArr[i] = carArr[0];
        carArr[0] = temp;

        int j = 0;
        int index;

        do {
            index = (2 * j + 1);
            if (carArr[index].vin < carArr[index + 1].vin && index < (i - 1)) {
                index++;
            }
            if (carArr[j].vin < carArr[index].vin && index < i) {
                swap(carArr[j], carArr[index]);
            }
            j = index;
        } while (index < i);
    }
    for(int i = 0; i < size; i++) {
        cout << left;
        cout << setw(8) << carArr[i].vin
             << setw(12) << carArr[i].model
             << setw(12) << carArr[i].make
             << setw(8) << fixed << setprecision(2) << carArr[i].price << endl;
    }
}

//**The function displays the menu to a user**
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a Car by VIN\n";
	cout << "I\t\tInsert a Car\n";
	cout << "K\t\tIncrease the VIN\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}
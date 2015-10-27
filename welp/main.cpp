#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Car.h"
#include "Rating.h"

using namespace std;

// Prototype functions
void chooseCars();
void listCars(string);
void pickCar(string);
void displayCarPage();

int main()
{
	cout << "Welcome to Welp! Its like Yelp, but for cars.\n" << endl;

	string choice;
	do{
		cout << "*************MAIN MENU*************" << endl;
		cout << "Enter the name make and model (e.g. Honda Civic) to start searching \nEnter L to browse from our list of cars \nEnter Q to quit" << endl;

		cin >> choice;
		if (choice == "L")
		{
			chooseCars();
		}
	} while (choice != "Q");


	system("PAUSE");
	return 1;
}

void chooseCars()
{
	string choice;
	// TODO: Change this so the values arent fixed and it reads value from an array instead
	cout << "Here is our selection of car makes. Pick a number to start browsing models" << endl;
	do
	{
		cout << "\n*************BROWSE MENU*************" << endl;
		cout << "1) Tesla" << endl;
		cout << "2) BMW" << endl;
		cout << "3) Honda" << endl;
		cout << "4) Toyota" << endl;
		cout << "9) All" << endl;
		cout << "0) Back" << endl;

		cin >> choice;
		if (choice != "0")
		{
			listCars(choice);
		}
	} while (choice != "0");
}

void listCars(string carType)
{
	//TODO: Use arrays to create list instead

	string choice;
	if (carType == "1")
	{
		cout << "Print a list of all the Teslas" << endl;

		do{
			cout << "1) Tesla Model X" << endl;
			cout << "0) Back" << endl;

			cin >> choice;
			if (choice != "0")
			{
				pickCar(choice);
			}
		} while (choice != "0");
	}
	else if (carType == "2")
	{
		cout << "List of all the BMWs" << endl;
		cout << "1) BMW M5" << endl;
	}
	else if (carType == "3")
	{
		cout << "List of all the Hondas" << endl;
		cout << "1) Honda Civic" << endl;
	}
	else if (carType == "4")
	{
		cout << "List of all the Toyotas" << endl;
		cout << "1) Toyota Camry" << endl;
	}
	else if (carType == "9")
	{
		cout << "List of all cars" << endl;
	}


}

void pickCar(string carModel)
{

}

void displayCarPage()
{
	cout << "\n*************TESLA MODEL X*************" << endl;
	cout << "Body Type" << endl;
	cout << "Engine Type" << endl;
	cout << "MPG" << endl;
	cout << "Price" << endl;
	cout << "Rating" << endl;
}
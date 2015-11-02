#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "Car.h"
#include "Rating.h"

using namespace std;

// Prototype functions
void chooseCars();
void listCars(string);
void pickCar(string);
void displayCarPage();

Car* load();
int getArrayLength();

void enterRating();

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
				displayCarPage();
			}
		} while (choice != "0");
	}
	else if (carType == "2")
	{
		do{
			cout << "List of all the BMWs" << endl;
			cout << "1) BMW M5" << endl;

			cin >> choice;
			if (choice != "0")
			{
				displayCarPage();
			}
		} while (choice != "0");
	}
	else if (carType == "3")
	{
		do{
			cout << "List of all the Hondas" << endl;
			cout << "1) Honda Civic" << endl;
			cin >> choice;
			if (choice != "0")
			{
				displayCarPage();
			}
		} while (choice != "0");
	}
	else if (carType == "4")
	{
		do{
			cout << "List of all the Toyotas" << endl;
			cout << "1) Toyota Camry" << endl;
			cin >> choice;
			if (choice != "0")
			{
				displayCarPage();
			}
		} while (choice != "0");
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
    
    
    /****** implementation of user review/ratings *******/
    char choice;
    
    cout << "User, do you wish to enter your rating and/or review for the vehicle?\n";
    cin >> choice;
    
    if (choice == 'Y' || choice == 'y')
    {
        enterRating();
    }
}

int getArrayLength()
{
	string line;
	int length = 0;
	ifstream in("info.txt");
	if (in.is_open())
	{
		in.clear();
		in.seekg(0, ios::beg);
		while (getline(in, line))
		{
			length++;
		}
		in.close();
		return length;
	}
	else
	{
		cout << "Error: Unable to open file.\n\n";
		return -1;
	}
}

//Make/Model/MPG City/MPG Freeway/Car Type/Engine Type/Price
//Honda,Civic (Sedan),25,40,Sedan,Gasoline,25000
Car* load()
{
	Car* list = new Car[getArrayLength()];
	string line;
	int index = 0;

	int substr_start, offset;

	string make, model, type, engine;
	int mpgcity, mpgfree, msrp;

	char divider = ',';

	ifstream in("info.txt");
	if (in.is_open())
	{
		in.clear();
		in.seekg(0, ios::beg);
		while (getline(in, line))
		{
			substr_start = 0;
			offset = 0;
			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			make = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;


			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			model = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;


			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			mpgcity = atoi(line.substr(substr_start, offset).c_str());
			substr_start = substr_start + offset + 1;
			offset = 0;

			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			mpgfree = atoi(line.substr(substr_start, offset).c_str());
			substr_start = substr_start + offset + 1;
			offset = 0;

			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			type = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;

			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			engine = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;

			while (line[substr_start + offset] != NULL)
			{
				offset++;
			}
			msrp = atoi(line.substr(substr_start, offset).c_str());
			substr_start = substr_start + offset + 1;
			offset = 0;

			list[index] = Car(make, model, type, engine, mpgcity, mpgfree, msrp);
			index++;
		}

		in.close();
		return list;
	}
	else
	{
		cout << "Error: Unable to open the file.\n\n";
		exit(-1);
	}
}

void enterRating()
{
    
}


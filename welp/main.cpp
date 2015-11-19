#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <climits>
#include <vector>
#include "Car.h"
#include "Rating.h"
#include "BST.h"
#include "HashTable.h"
#include "Review.h"

using namespace std;

// Menu Function
void splashMenu(); // This is the splash menu for our app
void searchForCarsMenu(); // This is the menu for the search function
void searchForCarByNameMenu();
void chooseCars();
void listCars(string);
void pickCar(int index);
void displayCarPage();
void displayCarPage(Car car);
void displayCarPage(int index);
void listAllCars();
void sortByCategoryMenu();
void sortByMpgMenu();
void sortByMpgFreewayMenu();
void sortByPriceMenu();
int filterCars(string, Car*);
inline bool isInteger(const std::string & s);


Car* load();
int getArrayLength();
void loadMpgBST(Car* list, BST<int, Car> &bst);
void loadMpgFreewayBST(Car* list, BST<int, Car> &bst);
void loadPriceBST(Car* list, BST<int, Car> &bst);
void loadReviewTable(HashTable<Review> &table);
void loadAvgRatingBST(Car* list, HashTable<Review> &table, BST<double, Car> &bst);

void enterRating();

Car* carList;
string userName;
HashTable<Review> reviewTable;
BST<int, Car> mpgBST;
BST<int, Car> mpgFreewayBST;
BST<int, Car> priceBST;
BST<double, Car> avgRatingBST;

int main()
{
	splashMenu();

	reviewTable = HashTable<Review>();
	mpgBST = BST<int, Car>();
	priceBST = BST<int, Car>();
	avgRatingBST = BST<double, Car>();
	mpgFreewayBST = BST<int, Car>();


    carList = load();
	loadMpgBST(carList, mpgBST);
	loadPriceBST(carList, priceBST);
	loadMpgFreewayBST(carList, mpgFreewayBST);
	loadReviewTable(reviewTable);
	loadAvgRatingBST(carList, reviewTable, avgRatingBST);


	system("CLS");

	string choice;
	do{
		system("CLS");
		cout << "*************MAIN MENU*************" << endl;
		cout << "1. Browse our list of cars" << endl;
		cout << "2. Search for a car" << endl;
		cout << "3. Sort cars by category" << endl;
		cout << "4. Quit" << endl;
		cout << "Please select an option. ";
		getline(cin, choice);
		if (choice == "1")
		{
			chooseCars();
		}
		else if (choice == "2")
		{
			searchForCarsMenu();
		}
		else if (choice == "3")
		{
			sortByCategoryMenu();
		}
	} while (choice != "4");

	/////////////TESTING: Entering and revising reviews///////////////////
	Rating rate;

	string owner, description, newDescription, searchOwner;
	char aChoice, sChoice, dChoice;
	int stars;

	cout << "Would you like to leave a review? (Y/N) \n";
	cin >> aChoice;
	if (aChoice == 'Y')
	{
		cin.ignore();
		cout << "\nTell us your personal thoughts about this vehicle:\n";
		getline(cin, description);
		cout << "\nFrom a rating of 1-10, give the car its deserved rating:\n";
		cin >> stars;
		cout << "\nFinally, tell us your name:\n";
		cin.ignore();
		getline(cin, owner);

		rate.newReview(description, stars, owner);
	}

	cout << "\nSize of list: " << rate.get_size() << endl;
	cout << "\nWould you like to search for a review based on the owner's name? (Y/N) \n";
	cin >> aChoice;
	if (aChoice == 'Y')
	{
		cout << "\nWhat is the owner's name for the review that you would like to search for?\n";
		cin.ignore();
		getline(cin, searchOwner);
		if (rate.searchByOwner(searchOwner))
		{
			cout << endl;
			rate.print();

			//Were not going to allow anybody to just change an existing review,
			//this is just for testing.
			cout << "***** Would you like to update the information? (Y/N) ***** \n";
			cin >> aChoice;
			if (aChoice == 'Y')
			{
				cout << "*** Update the number of stars? (Y/N) \n";
				cin >> sChoice;
				if (sChoice == 'Y')
				{
					cout << "What level of stars would you like to give? \n";
					cin >> stars;
					rate.changeStars(stars);
				}
				cout << "*** Update the review? (Y/N) \n";
				cin >> dChoice;
				if (dChoice == 'Y')
				{
					cout << "Please, tell us your thoughts on the vehicle: \n";
					cin.ignore();
					getline(cin, newDescription);
					rate.changeDescription(newDescription);
				}
			}
		}
		else
		{
			cout << "The name on the review was not found!\n";
		}
	}
	cout << endl;

	rate.printAll();

	//Testing more function
	if (rate.off_end())
	{
		cout << "Iterator was not pointing to anything, but now testing begin() \n";
		rate.begin();
	}
	else
		cout << "Iterator pointing to an element\n";

	cout << "Testing currentOwner(): " << rate.currentOwner() << endl;

	cout << "Testing remove(): \n";
	rate.remove();

	rate.printAll();

	cout << endl;
	///////////END OF TESTING///////////////

	system("PAUSE");
	return 0;
}

void splashMenu()
{
	cout << "Welcome to Welp, Yelp for Cars!" << endl << endl;

	cout << "                       ______________" << endl;
	cout << "   Chris Banh  __..=='|'   |         ``-._" << endl;
	cout << "  \\=====_..--'/'''    |    | Han Tint     ``-._     Carlos Quirarte" << endl;
	cout << "  |'''''      ```---..|____|_______________[)>.``-.._____" << endl;
	cout << "  |\\_______.....__________|____________     ''  \\      __````---.._" << endl;
	cout << "./'     /.-'_'_`-.\\       |  ' '       ```````---|---/.-'_'_`=.-.__```-._" << endl;
	cout << "|.__  .'/ /     \\ \\`.      \\    Johnny Nguyen    | .'/ /     \\ \\`. ```-- `." << endl;
	cout << " \\  ``|| |   o   | ||-------\\-------------------/--|| |   o   | ||--------|" << endl;
	cout << "  \"`--' \\ \\ _ _ / / |______________________________| \\ \\ _ _ / / |..----```" << endl;
	cout << "         `-.....-'                  Kevin Ngo         `-.....-'" << endl;
	cout << endl << endl << endl;

	cout << "What is your username? ";
	getline(cin, userName);
}

void chooseCars()
{
	string choice;
	// TODO: Change this so the values arent fixed and it reads value from an array instead
	do
	{
		system("CLS");
		cout << "*************BROWSE MENU*************" << endl;
		cout << "Here is our selection of car makes. Pick a number to start browsing models" << endl;
		cout << "1) Honda" << endl;
		cout << "2) Toyota" << endl;
		cout << "3) Subaru" << endl;
		cout << "4) Ford" << endl;
		cout << "5) Acura" << endl;
		cout << "6) Chevrolet" << endl;
		cout << "7) Nissan" << endl;
		cout << "8) Tesla" << endl;
		cout << "9) BMW" << endl;
		cout << "10) Ford" << endl;
		cout << "11) All" << endl;
		cout << "0) Back" << endl;

		cin >> choice;
		if (choice != "0" && isInteger(choice))
		{
			int intChoice = atoi(choice.c_str());
			if (intChoice >= 0 && intChoice <= 11)
				listCars(choice);
		}
	} while (choice != "0");
}

void sortByCategoryMenu()
{
	string choice;
	// TODO: Change this so the values arent fixed and it reads value from an array instead
	do
	{
		system("CLS");
		cout << "*************CATEGORY MENU*************" << endl;
		cout << "What would you like to sort cars by?" << endl;
		cout << "1) MPG City" << endl;
		cout << "2) MPG Freeway" << endl;
		cout << "3) Price" << endl;
		cout << "4) Rating" << endl;
		cout << "0) Back" << endl;

		cin >> choice;
		if (choice != "0" && isInteger(choice))
		{
			int intChoice = atoi(choice.c_str());

			if (intChoice == 1)
			{
				sortByMpgMenu();
			}
			else if (intChoice == 2)
			{
				sortByMpgFreewayMenu();
			}
			else if (intChoice == 3)
			{
				sortByPriceMenu();
			}
			else if (intChoice == 4)
			{
				// TODO:
			}
		}
	} while (choice != "0");
}

void sortByMpgMenu()
{
	system("CLS");
	string choice;
	int intChoice;
	int count;

	do{
		system("CLS");
		count = 0;
		vector<Car> carVector;
		int min = INT_MIN; int max = INT_MAX;
		mpgBST.getVectorInOrder(min, max, carVector);

		cout << "*************SORTED MPG LIST*************" << endl;

		for (int i = 0; i < carVector.size(); i++)
		{
			count++;
			cout << count << ". ";
			cout << carVector[i].getMake() << " ";
			cout << carVector[i].getModel() << "/ MPG: ";
			cout << carVector[i].getMPGCity() << endl;
		}

		cout << "0. Back" << endl;

		// Input Validation by checking if its an integer and within the range of teh array
		cin >> choice;
		if (isInteger(choice) && choice != "0")
		{
			intChoice = atoi(choice.c_str());
			if (intChoice > 0 && intChoice <= count)
			{
				displayCarPage(carVector[intChoice - 1]);
			}
		}
	} while (choice != "0");
}

void sortByMpgFreewayMenu()
{
	system("CLS");
	string choice;
	int intChoice;
	int count;

	do{
		system("CLS");
		count = 0;
		vector<Car> carVector;
		int min = INT_MIN; int max = INT_MAX;
		mpgFreewayBST.getVectorInOrder(min, max, carVector);

		cout << "*************SORTED MPG FREEWAY LIST*************" << endl;

		for (int i = 0; i < carVector.size(); i++)
		{
			count++;
			cout << count << ". ";
			cout << carVector[i].getMake() << " ";
			cout << carVector[i].getModel() << "/ MPG Freeway: ";
			cout << carVector[i].getMPGFreeway() << endl;
		}

		cout << "0. Back" << endl;

		// Input Validation by checking if its an integer and within the range of teh array
		cin >> choice;
		if (isInteger(choice) && choice != "0")
		{
			intChoice = atoi(choice.c_str());
			if (intChoice > 0 && intChoice <= count)
			{
				displayCarPage(carVector[intChoice - 1]);
			}
		}
	} while (choice != "0");
}

void sortByPriceMenu()
{
	system("CLS");
	string choice;
	int intChoice;
	int count;

	do{
		system("CLS");
		count = 0;
		vector<Car> carVector;
		int min = INT_MIN; int max = INT_MAX;
		priceBST.getVectorInOrder(min, max, carVector);

		cout << "*************SORTED PRICE LIST*************" << endl;
		for (int i = 0; i < carVector.size(); i++)
		{
			count++;
			cout << count << ". ";
			cout << carVector[i].getMake() << " ";
			cout << carVector[i].getModel() << "/ Price: ";
			cout << carVector[i].getPrice() << endl;
		}

		cout << "0. Back" << endl;

		// Input Validation by checking if its an integer and within the range of teh array
		cin >> choice;
		if (isInteger(choice) && choice != "0")
		{
			intChoice = atoi(choice.c_str());
			if (intChoice > 0 && intChoice <= count)
			{
				displayCarPage(carVector[intChoice - 1]);
			}
		}
	} while (choice != "0");
}

void listCars(string carType)
{
	int intChoice;
	string choice;
	Car filteredCars[30];
	int filteredSize;


	if (carType == "1")
	{
		filteredSize = filterCars("Honda", filteredCars);
	}
	else if (carType == "2")
	{
		filteredSize = filterCars("Toyota", filteredCars);
	}
	else if (carType == "3")
	{
		filteredSize = filterCars("Subaru", filteredCars);
	}
	else if (carType == "4")
	{
		filteredSize = filterCars("Ford", filteredCars);
	}
	else if (carType == "5")
	{
		filteredSize = filterCars("Acura", filteredCars);

	}
	else if (carType == "6")
	{
		filteredSize = filterCars("Chevrolet", filteredCars);
	}
	else if (carType == "7")
	{
		filteredSize = filterCars("Nissan", filteredCars);
	}
	else if (carType == "8")
	{
		filteredSize = filterCars("Tesla", filteredCars);
	}
	else if (carType == "9")
	{
		filteredSize = filterCars("BMW", filteredCars);
	}
	else if (carType == "10")
	{
		filteredSize = filterCars("Ford", filteredCars);
	}
	else if (carType == "11")
	{
		listAllCars();
	}
}

int filterCars(string carMake, Car* filteredCars)
{
	system("CLS");
	string choice;
	int intChoice;
	int count;

	do{
		system("CLS");
		count = 0;

		cout << "\n*************CAR LIST*************" << endl;
		for (int i = 0; i < getArrayLength(); i++)
		{
			if (carList[i].getMake() == carMake)
			{
				count++;
				filteredCars[count - 1] = carList[i];
				filteredCars[1];
				cout << count << ". ";
				cout << carList[i].getMake() << " ";
				cout << carList[i].getModel() << endl;
			}
		}

		cout << "0. Back" << endl;

		// Input Validation by checking if its an integer and within the range of teh array
		cin >> choice;
		if (isInteger(choice) && choice != "0")
		{
			intChoice = atoi(choice.c_str());
			if (intChoice > 0 && intChoice <= count)
			{
				displayCarPage(filteredCars[intChoice - 1]);
			}

		}
	} while (choice != "0");

	return count;
}

void listAllCars()
{
	string choice;
//	string finalIndex = getArrayLength();


	do{
		system("CLS");
		cout << "*************ALL CARS MENU*************" << endl;
		// Print out list of all cars
		for (int i = 1; i < getArrayLength(); i++)
		{
			cout << i << ". ";
			cout << carList[i - 1].getMake() << " ";
			cout << carList[i - 1].getModel() << endl;
		}
		cout << "0. Quit" << endl;

		// Input validation by checking for integer and range
		cin >> choice;
		if (isInteger(choice))
		{
			int intChoice = atoi(choice.c_str());
			if (intChoice > 0 && intChoice < getArrayLength())
			{
				displayCarPage(intChoice - 1);
			}
		}
	} while (choice != "0");
}

void displayCarPage(Car car)
{
	cout << "\n*************" << car.getMake() << " " << car.getModel() << "*************" << endl;
	cout << "Engine Type: " << car.getEngine() << endl;
	cout << "MPG City: " << car.getMPGCity() << endl;
	cout << "MPG Freeway: " << car.getMPGFreeway() << endl;
	cout << "Price: " << car.getPrice() << endl;
	cout << "Rating: " << endl;

	/****** implementation of user review/ratings *******/
	char choice;

	cout << "User, do you wish to enter your rating and/or review for the vehicle? Y/N \n";
	cin >> choice;

	if (choice == 'Y' || choice == 'y')
	{
		enterRating();
	}
}

void displayCarPage(int index)
{
	system("CLS");
	cout << "*************" << carList[index].getMake() << " " << carList[index].getModel() << "*************" << endl;
	cout << "Engine Type: " << carList[index].getEngine() << endl;
	cout << "MPG City: " << carList[index].getMPGCity() << endl;
	cout << "MPG Freeway: " << carList[index].getMPGFreeway() << endl;
	cout << "Price: " << carList[index].getPrice() << endl;
	cout << "Rating: " << endl;


	/****** implementation of user review/ratings *******/
	char choice;

	cout << "User, do you wish to enter your rating and/or review for the vehicle? Y/N \n";
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
	ifstream in("Kars Data.txt");
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
		cout << "Error 1: Unable to open file \"Kars Data.txt\"" << endl << endl;
		return -1;
	}
}


inline bool isInteger(const std::string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
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

	char divider = '/';

	ifstream in("Kars Data.txt");
	if (in.is_open())
	{
		in.clear();
		in.seekg(0, ios::beg);
		while (getline(in, line))
		{
		    //Get the make
			substr_start = 0;
			offset = 0;
			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			make = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;

            //Get the model
			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			model = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;

            //Get the mpgcity
			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			mpgcity = atoi(line.substr(substr_start, offset).c_str());
			substr_start = substr_start + offset + 1;
			offset = 0;

            //Get the mpgfree
			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			mpgfree = atoi(line.substr(substr_start, offset).c_str());
			substr_start = substr_start + offset + 1;
			offset = 0;

            //Get the engine
			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			engine = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;

            //Get the price
			while (line[substr_start + offset] != NULL)
			{
				offset++;
			}
			msrp = atoi(line.substr(substr_start, offset).c_str());
			substr_start = substr_start + offset + 1;
			offset = 0;

			//make << model << engine << mpgcity <<  mpgfree << msrp
			list[index] = Car(make, model, engine, mpgcity, mpgfree, msrp);
			index++;
			// << "Added successfully" << endl;
		}
		in.close();
		return list;
	}
	else
	{
		cout << "Error 2: Unable to open the file \"Kars Data.txt\"." << endl << endl;
		exit(-1);
	}
}

void loadReviewTable(HashTable<Review> &table)
{
    string line;

	int substr_start, offset;

	string make, model, owner, description;
	int stars;

	char divider = '/';

	ifstream in("reviews.txt");
	if (in.is_open())
	{
		in.clear();
		in.seekg(0, ios::beg);
		while (getline(in, line))
		{
		    //Get the make
			substr_start = 0;
			offset = 0;
			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			make = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;

            //Get the model
			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			model = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;

            //Get the owner
			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			owner = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;

            //Get the stars
			while (line[substr_start + offset] != divider)
			{
				offset++;
			}
			stars = atoi(line.substr(substr_start, offset).c_str());
			substr_start = substr_start + offset + 1;
			offset = 0;

            //Get the description
			while (line[substr_start + offset] != NULL)
			{
				offset++;
			}
			description = line.substr(substr_start, offset);
			substr_start = substr_start + offset + 1;
			offset = 0;

			//owner >> description >> stars >> make >> model
            Review review = Review(owner, description, stars, make, model);
            table.addItem(make, model, review);
		}
		in.close();
	}
	else
	{
		cout << "Error 3: Unable to open the file \"reviews.txt\"." << endl << endl;
		exit(-1);
	}
}

void loadMpgBST(Car* list, BST<int, Car> &bst)
{
	int size = getArrayLength();
	for (int i = 0; i < size; i++)
	{
		bst.add(list[i].getMPGCity(), list[i]);
	}
}

void loadMpgFreewayBST(Car* list, BST<int, Car> &bst)
{
	int size = getArrayLength();
	for (int i = 0; i < size; i++)
	{
		bst.add(list[i].getMPGFreeway(), list[i]);
	}
}

void loadPriceBST(Car* list, BST<int, Car> &bst)
{
	int size = getArrayLength();
	for (int i = 0; i < size; i++)
	{
		bst.add(list[i].getPrice(), list[i]);
	}
}

void loadAvgRatingBST(Car* list, HashTable<Review> &table, BST<double, Car> &bst)
{
    int size = getArrayLength();
	for (int i = 0; i < size; i++)
	{
	    Car car = list[i];
	    double avg_rating = table.getAverageRatingBucket(car.getMake(), car.getModel());
		bst.add(avg_rating, car);
	}
}

//May delete this function to be replaced by the Rating's Class member function.
void enterRating()
{
	string description;
	int stars;
	string owner;
	char choice;
	Rating * newRating;

	/////////////// Review about the Car ///////////////

	do
	{
		cout << "Tell us your personal thoughts about this vehicle:\n";
		getline(cin, description);
		cout << "\nFrom a rating of 1-10, give the car its deserved rating:\n";
		cin >> stars;
		cout << "\nFinally, tell us your name:\n";
		cin.ignore();
		getline(cin, owner);

		newRating = new Rating(description, stars, owner);

		cout << "\nDo you wish to leave another review for this vehicle?\n";
		cin >> choice;
		cout << endl;

		if (choice != 'n' && choice != 'N')
			cin.ignore();
	} while (choice != 'n' && choice != 'N');
	cout << "Thank you for sharing your experience!\n";
}

/**
 * Search For Cars Menu
 *
 * This is the menu for the searching feature
 * There are 4 menu options:
 * 1. Search by Car Name
 * 2. Search by Car Manufacturer
 * 3. Search by Price Range
 * 4. Go Back
 */
void searchForCarsMenu()
{
	system("CLS");
	cout << "****Search for Cars*****" << endl;
	cout << "1. Search by car name" << endl;
	cout << "2. Search for cars by manufacturer" << endl;
	cout << "3. Search cars in a price range" << endl;
	cout << "4. Go Back.";
	cout << endl;
	cout << "What is your option? ";
	string choice;
	getline(cin, choice);

	if (choice == "1")
	{
		searchForCarByNameMenu();
	}
	else if (choice == "2")
	{

	}
	else if (choice == "3")
	{

	}
}

/**
 * Search for Car by Car Name Menu
 * 
 * This is a part of the search feature
 */
void searchForCarByNameMenu()
{
	system("CLS");
	cout << "*****Search for Car by Car Name*****" << endl;
	cout << "Please input a car name (i.e. Honda Accord) ";
	string name;
	getline(cin, name);

	// This is a linear search
	// TODO: Convert this to a binary search
	for (int i = 0; i < getArrayLength(); i++)
	{
		// If the car's name is found, then render the car page for the user
		if (name.compare(carList[i].getName()) == 0)
		{
			// README: Uncomment when we implement car ids
			displayCarPage(i);
		}
	}
}

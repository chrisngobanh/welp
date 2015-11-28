#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <climits>
#include <vector>
#include "List.h"
#include "Car.h"
#include "Rating.h"
#include "BST.h"
#include "HashTable.h"
#include "Review.h"

using namespace std;

// Menu Prototypes
void splashMenu(); // This is the splash menu for our app
void mainMenu();
void searchForCarsMenu(); // This is the menu for the search function
void searchForCarByNameMenu();
void searchForCarsByMakeMenu();
void searchForCarsByPriceMenu();
void browseForCarsMenu();
void listCars(string);
void pickCar(int index);
void displayCarPage(Car car);
void listAllCarsMenu();
void raitingMenu();
void sortByCategoryMenu();
void sortByMpgMenu();
void sortByMpgFreewayMenu();
void sortByPriceMenu();
void filterCarsMenu(string, Car*);

Car* load();
int getArrayLength();
void loadMpgBST(Car* list, BST<int, Car> &bst);
void loadMpgFreewayBST(Car* list, BST<int, Car> &bst);
void loadPriceBST(Car* list, BST<int, Car> &bst);
void loadReviewTable(HashTable<Review> &table);
void loadAvgRatingBST(Car* list, HashTable<Review> &table, BST<double, Car> &bst);
void loadCarMake(vector<string>& makeList, Car* cList);
void saveReviews(HashTable<Review> &Table, Car* list);


Car* carList;
string userName;
HashTable<Review> reviewTable;
BST<int, Car> mpgBST;
BST<int, Car> mpgFreewayBST;
BST<int, Car> priceBST;
BST<double, Car> avgRatingBST;
vector<string> carMakeVector;

// Handler Functions (Reusable Code)

/**
 * Get User Input Handler
 *
 * This function gets user input when called.
 * It returns the user input.
 * Ignores empty lines
 */
string getUserInput()
{
	string input;
	// Check if user input is empty. If it isn't, then end loop
	while (getline(cin, input))
	{
		if (input.size()) break;
	}
	return input;
}

/**
* Is Integer Handler
*
* This function takes a string and checks if it can be converted to an int
* Returns true if the string can be an int, and false if the string cannot be an int
*/
inline bool isInteger(const std::string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}


/**
 * Covert String To Int Handler
 *
 * This function converts a string to an int
 * If the string is not an int, then it returns -1
 * Otherwise, it'll return an int that is the string's int form
 */
int convertStringToInt(string input)
{
	if (!isInteger(input)) return -1;
	return atoi(input.c_str());
}

/**
* Clear Screen Handler
* 
* This function clears the screen by making a lot of empty new lines
* This method is cross platform
*/
void clearScreen()
{
	if (system("CLS")) system("clear");
}

// The rest of the program

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
	loadCarMake(carMakeVector, carList);

	mainMenu();

	saveReviews(reviewTable, carList);

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

	// Check if user input is empty. If it isn't, then end loop
	userName = getUserInput();
}

// This is the only menu that should have a loop
void mainMenu()
{
	bool isGood = false;
	do
	{
		clearScreen();
		cout << "*************MAIN MENU*************" << endl;
		cout << "1. Browse our list of cars" << endl;
		cout << "2. Search for a car" << endl;
		cout << "3. Sort cars by category" << endl;
		cout << "4. Quit" << endl;
		cout << "Please select an option. ";

		string choice = getUserInput();

		if (choice == "1")
		{
			browseForCarsMenu();
		}
		else if (choice == "2")
		{
			searchForCarsMenu();
		}
		else if (choice == "3")
		{
			sortByCategoryMenu();
		}
		else if (choice == "4")
		{
			isGood = true;
		}
	} while (!isGood);
}

void browseForCarsMenu()
{
	// TODO: Change this so the values arent fixed and it reads value from an array instead
	clearScreen();
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

	string choice = getUserInput();
	if (choice == "0") return;

	int intChoice = convertStringToInt(choice);

	if (intChoice >= 1 && intChoice <= 11)
	{
		listCars(choice);
	}
	else
	{
		// If the user input is bad, recall the function.
		browseForCarsMenu();
	}
}

void sortByCategoryMenu()
{
	// TODO: Change this so the values arent fixed and it reads value from an array instead
	clearScreen();
	cout << "*************CATEGORY MENU*************" << endl;
	cout << "What would you like to sort cars by?" << endl;
	cout << "1) MPG City" << endl;
	cout << "2) MPG Freeway" << endl;
	cout << "3) Price" << endl;
	cout << "4) Rating" << endl;
	cout << "0) Back" << endl;

	string choice = getUserInput();

	if (choice == "0") return;

	if (choice == "1")
	{
		sortByMpgMenu();
	}
	else if (choice == "2")
	{
		sortByMpgFreewayMenu();
	}
	else if (choice == "3")
	{
		sortByPriceMenu();
	}
	else if (choice == "4")
	{
		// TODO:
	}
	else
	{
		// If the user input is bad, recall the function.
		sortByCategoryMenu();
	}
}

void sortByMpgMenu()
{
	clearScreen();
	vector<Car> carVector;
	int min = INT_MIN;
	int max = INT_MAX;
	mpgBST.getVectorInOrder(min, max, carVector);

	cout << "*************SORTED MPG LIST*************" << endl;

	int count = 0;
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
	string choice = getUserInput();

	if (choice == "0") return;

	int intChoice = convertStringToInt(choice);
	if (intChoice >= 1 && intChoice <= count)
	{
		displayCarPage(carVector[intChoice - 1]);
	}
	else
	{
		// If the user input is bad, recall the function.
		sortByMpgMenu();
	}

}

void sortByMpgFreewayMenu()
{
	clearScreen();
	vector<Car> carVector;
	int min = INT_MIN;
	int max = INT_MAX;
	mpgFreewayBST.getVectorInOrder(min, max, carVector);

	cout << "*************SORTED MPG FREEWAY LIST*************" << endl;

	int count = 0;
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
	string choice = getUserInput();

	if (choice == "0") return;

	int intChoice = convertStringToInt(choice);

	if (intChoice >= 1 && intChoice <= count)
	{
		displayCarPage(carVector[intChoice - 1]);
	}
	else
	{
		// If the user input is bad, recall the function.
		sortByMpgFreewayMenu();
	}

}

void sortByPriceMenu()
{
	clearScreen();
	vector<Car> carVector;
	int min = INT_MIN;
	int max = INT_MAX;
	priceBST.getVectorInOrder(min, max, carVector);

	cout << "*************SORTED PRICE LIST*************" << endl;
	int count = 0;
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
	string choice = getUserInput();

	if (choice == "0") return;

	int intChoice = convertStringToInt(choice);
	if (intChoice >= 1 && intChoice <= count)
	{
		displayCarPage(carVector[intChoice - 1]);
	}
	else
	{
		// If user input is bad, recall the function.
		sortByPriceMenu();
	}

}

void listCars(string carType)
{
	Car filteredCars[30];

	// This could be greatly improved with an array of car makes
	if (carType == "1")
	{
		filterCarsMenu("Honda", filteredCars);
	}
	else if (carType == "2")
	{
		filterCarsMenu("Toyota", filteredCars);
	}
	else if (carType == "3")
	{
		filterCarsMenu("Subaru", filteredCars);
	}
	else if (carType == "4")
	{
		filterCarsMenu("Ford", filteredCars);
	}
	else if (carType == "5")
	{
		filterCarsMenu("Acura", filteredCars);
	}
	else if (carType == "6")
	{
		filterCarsMenu("Chevrolet", filteredCars);
	}
	else if (carType == "7")
	{
		filterCarsMenu("Nissan", filteredCars);
	}
	else if (carType == "8")
	{
		filterCarsMenu("Tesla", filteredCars);
	}
	else if (carType == "9")
	{
		filterCarsMenu("BMW", filteredCars);
	}
	else if (carType == "10")
	{
		filterCarsMenu("Ford", filteredCars);
	}
	else if (carType == "11")
	{
		listAllCarsMenu();
	}
}

void filterCarsMenu(string carMake, Car* filteredCars)
{
	clearScreen();
	cout << "*************CAR LIST*************" << endl;
	int count = 0;
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
	string choice = getUserInput();

	if (choice == "0") return;

	int intChoice = convertStringToInt(choice);

	if (intChoice >= 1 && intChoice <= count)
	{
		displayCarPage(filteredCars[intChoice - 1]);
	}
	else
	{
		filterCarsMenu(carMake, filteredCars);
	}


}

void listAllCarsMenu()
{
	//	string finalIndex = getArrayLength();
	clearScreen();
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
	string choice = getUserInput();
	
	if (choice == "0") return;

	int intChoice = convertStringToInt(choice);

	if (intChoice >= 1 && intChoice < getArrayLength())
	{
		displayCarPage(carList[intChoice - 1]);
	}
	else
	{
		listAllCarsMenu();
	}

}

void displayCarPage(Car car)
{
	clearScreen();
	cout << "*************" << car.getMake() << " " << car.getModel() << "*************" << endl;
	cout << "                       ______________" << endl;
	cout << "               __..=='|'   |         ``-._" << endl;
	cout << "  \\=====_..--'/'''    |    |              ``-._" << endl;
	cout << "  |'''''      ```---..|____|_______________[)>.``-.._____" << endl;
	cout << "  |\\_______.....__________|____________     ''  \\      __````---.._" << endl;
	cout << "./'     /.-'_'_`-.\\       |  ' '       ```````---|---/.-'_'_`=.-.__```-._" << endl;
	cout << "|.__  .'/ /     \\ \\`.      \\                     | .'/ /     \\ \\`. ```-- `." << endl;
	cout << " \\  ``|| |   o   | ||-------\\-------------------/--|| |   o   | ||--------|" << endl;
	cout << "  \"`--' \\ \\ _ _ / / |______________________________| \\ \\ _ _ / / |..----```" << endl;
	cout << "         `-.....-'                                    `-.....-'" << endl;
	cout << endl << endl << endl;
	cout << "Engine Type: " << car.getEngine() << endl;
	cout << "MPG City: " << car.getMPGCity() << endl;
	cout << "MPG Freeway: " << car.getMPGFreeway() << endl;
	cout << "Price: " << car.getPrice() << endl;
	cout << "Rating: " << endl;

	raitingMenu();
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
void raitingMenu()
{

	string description;
	int stars;
	string owner;
	Review newReview;

	cout << "\n*************Reviews Menu*************" << endl;
	cout << "1. View list of reviews" << endl;
	cout << "2. Add a review" << endl;
	cout << "3. Delete a review" << endl;
	cout << "4. Quit" << endl;

	cout << "What is your option? ";

	string choice = getUserInput();

	if (choice == "1")
	{
		cout << "Function to list reviews" << endl;
	}
	else if (choice == "2")
	{
		cout << "Function to add review" << endl;
	}
	else if (choice == "3")
	{

		cout << "Function to delete a review" << endl;
	}
	else if (choice == "4")
	{ 
		cout << "quit" << endl;
	}
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
	clearScreen();
	cout << "****Search for Cars*****" << endl;
	cout << "1. Search by car name" << endl;
	cout << "2. Search for cars by manufacturer" << endl;
	cout << "3. Search cars in a price range" << endl;
	cout << "4. Go Back.";
	cout << endl;
	cout << "What is your option? ";
	string choice = getUserInput();

	if (choice == "1")
	{
		searchForCarByNameMenu();
	}
	else if (choice == "2")
	{
		searchForCarsByMakeMenu();
	}
	else if (choice == "3")
	{
		searchForCarsByPriceMenu();
	}
}

/**
 * Search for Car by Car Name Menu
 *
 * This is a part of the search feature
 */
void searchForCarByNameMenu()
{
	clearScreen();
	cout << "*****Search for Car by Car Name*****" << endl;
	cout << "Please input a car name (i.e. Honda Accord) ";
	string name = getUserInput();

	// This is a linear search
	// TODO: Convert this to a binary search
	for (int i = 0; i < getArrayLength(); i++)
	{
		// If the car's name is found, then render the car page for the user
		if (name.compare(carList[i].getName()) == 0)
		{
			displayCarPage(carList[i]);
		}
	}
}

/**
 * Search for Car by Car Make Menu
 *
 * This is a part of the search feature
 */
void searchForCarsByMakeMenu()
{
	clearScreen();
	cout << "*****Search for Car by Car Manufacturer*****" << endl;
	cout << "Please input a car name (i.e. Tesla) ";
	string name = getUserInput();

	// This is a linear search
	// TODO: Convert this to a binary search
	// TODO: Wait until Johnny creates the array of car makes
	//for (int i = 0; i < getArrayLength(); i++)
	//{
	//	// If the car's name is found, then render the car page for the user
	//	if (name.compare(carList[i].getMake()) == 0)
	//	{
	//		// README: Uncomment when we implement car ids
	//		displayCarPage(i);
	//	}
	//}
}

void searchForCarsByPriceMenu()
{
	bool isGood = false;
	while (!isGood)
	{
		clearScreen();
		cout << "*****Search for Car by Price Range*****" << endl;
		cout << "Please input the min price (25000) ";
		string min = getUserInput();

		cout << "Please input the max price (50000) ";
		string max = getUserInput();

		int minInt = convertStringToInt(min);
		int maxInt = convertStringToInt(max);

		if (!(minInt > maxInt) && minInt != -1 && maxInt != -1)
		{
			vector<Car> cars;

			// This is a linear search
			// TODO: Convert this to a binary search
			for (int i = 0; i < getArrayLength(); i++)
			{
				// If car price is in range
				if (carList[i].getPrice() >= minInt && carList[i].getPrice() <= maxInt)
				{
					cars.push_back(carList[i]);
				}
			}

			if (cars.size() == 0)
			{
				cout << "No cars found. Please try again." << endl;
			}
		}
		else
		{
			cout << "Bad price range. Please try again." << endl;
		}


		cout << "Do you want to continue searching for cars by price? (y/n) ";
		string choice = getUserInput();

		if (choice == "")
		{
			choice = "n";
		}
		// Check if the first character in the answer is a y or Y. If false, stop the loop.
		if (!(choice.at(0) == 'y' || choice.at(0) == 'Y'))
		{
			isGood = true;
		}
	}


}

void loadCarMake(vector<string>& makeList, Car* cList)
{
	string Make;
	bool isDupe = true;
	int makeSize = 0;
	int size = getArrayLength();

	//Reads car makes from clist
	for (int i = 0; i < size; i++)
	{
		Make = cList[i].getMake();
		makeSize = makeList.size();

		// If carMake is empty then pushback Make
		if (makeSize == 0)
		{
			makeList.push_back(Make);
		}

		// If carMake is not empty then check if Make is a duplicate
		// Duplicates are ignored, while new Makes are added
		else
		{
			for (int j = 0; j < makeSize; j++)
			{
				if (Make == makeList[j])
				{
					isDupe = true;
					break;
				}
				else isDupe = false;
			}
			if (!isDupe) makeList.push_back(Make);
		}
	}
}

void saveReviews(HashTable<Review> &Table, Car* list)
{
	// Make/Model/Owner/Stars/Description

	int size = getArrayLength();
	int rSize = 0;
	string Make, Model;
	ofstream save("reviews.txt");
	List<Review> rList;

	if (save.is_open())
	{
		// Checks every car for reviews
		for (int i = 0; i < size; i++)
		{
			Make = list[i].getMake();
			Model = list[i].getModel();

			// If the car has no reviews, move to next car
			// Cars with reviews are outputted to 'reviews.txt'
			if (Table.indexIsFilled(Make, Model))
			{
				rList = Table.getValue(Make, Model);
				rList.begin();
				while (!rList.off_end())
				{
					save << rList.current().getMake() << "/" << rList.current().getModel() << "/" << rList.current().getOwner() << "/" << rList.current().getStars() << "/" << rList.current().getDescription() << endl;
					rList.scroll();
				}
			}

		}

		save.close();
	}
	else
	{
		cout << "Error : Unable to open file 'reviews.txt' ";
		exit(-1);
	}

}

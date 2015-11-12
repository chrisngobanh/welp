#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "Car.h"
#include "Rating.h"
#include "BST.h"

using namespace std;

// Prototype functions
void splashMenu(); // This is the splash menu for our app
void searchForCarsMenu();
void chooseCars();
void listCars(string);
void pickCar(int index);
void displayCarPage();
void displayCarPage(int index);
void listAllCars();
void filterCars(string);

Car* load();
void loadMpgBST(Car* list, BST<int, Car> &bst);
void loadPriceBST(Car* list, BST<int, Car> &bst);
int getArrayLength();

void enterRating();

Car* carList;
string userName;

int main()
{
	splashMenu();
	carList = load();
	BST<int, Car> mpgBST = BST<int, Car>();
	BST<int, Car> priceBST = BST<int, Car>();
	loadMpgBST(carList, mpgBST);
	loadPriceBST(carList, priceBST);

	string choice;
	do{
		system("CLS");
		cout << "*************MAIN MENU*************" << endl;
		cout << "1. Browse our list of cars" << endl; 
		cout << "2. Search for a car" << endl;
		cout << "3. Quit" << endl;
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
	} while (choice != "3");
    
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
		filterCars("Honda");
	}
	else if (carType == "2")
	{
		filterCars("Toyota");
	}
	else if (carType == "3")
	{
		filterCars("Subaru");

	}
	else if (carType == "4")
	{
		filterCars("Ford");

	}
	else if (carType == "5")
	{
		filterCars("Acura");

	}
	else if (carType == "6")
	{
		filterCars("Chevrolet");
	}
	else if (carType == "7")
	{
		filterCars("Nissan");

	}
	else if (carType == "8")
	{
		filterCars("Tesla");
	}
	else if (carType == "9")
	{
		listAllCars();
	}

	cin >> choice;
	int intChoice = stoi(choice);

	if (intChoice > 0 && intChoice < getArrayLength())
	{
		displayCarPage(intChoice);
	}

}
void filterCars(string carMake)
{
	system("CLS");
	cout << "*************CAR LIST*************" << endl;
	for (int i = 0; i < getArrayLength(); i++)
	{
		if (carList[i].getMake() == carMake)
		{
			cout << i << ". ";
			cout << carList[i].getMake() << " ";
			cout << carList[i].getModel() << endl;
		}
	}
}

void listAllCars()
{
	string choice;
	string finalIndex = to_string(getArrayLength());

	do{
		system("CLS");
		cout << "*************ALL CARS MENU*************" << endl;
		// Print out list of all cars
		for (int i = 0; i < getArrayLength(); i++)
		{
			cout << i << ". ";
			cout << carList[i].getMake() << " ";
			cout << carList[i].getModel() << endl;
		}
		cout << getArrayLength() << ". Quit" << endl;

		// Input validation
		cin >> choice;
		int intChoice = stoi(choice);

		if (intChoice > 0 && intChoice < getArrayLength())
		{
			displayCarPage(intChoice);
		}

	} while (choice != finalIndex);
}

void pickCar(int index)
{

}

void displayCarPage()
{
	system("CLS");
	cout << "*************TESLA MODEL X*************" << endl;
	cout << "Engine Type" << endl;
	cout << "MPG City" << endl;
	cout << "MPG Freeway" << endl;
	cout << "Price" << endl;
	cout << "Rating" << endl; //TODO: How do ratings?
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

void displayCarPage(int index)
{
	system("CLS");
	cout << "*************" << carList[index].getMake() << " " << carList[index].getModel() <<  "*************" << endl;
	cout << "Engine Type: " << carList[index].getEngine() << endl;
	cout << "MPG City: " << carList[index].getMPGCity() <<endl;
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
		cout << "Error: Unable to open file.\n\n";
		return -1;
	}
}

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

			//cout << make << model <<engine << " city: " << mpgcity << " Free: " <<  mpgfree << " price: " << msrp << endl;
			list[index] = Car(make, model, engine, mpgcity, mpgfree, msrp);
			index++;
			// << "Added successfully" << endl;
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

void loadMpgBST(Car* list, BST<int, Car> &bst)
{
	int size = getArrayLength();
	for (int i = 0; i < size; i++)
	{
		bst.add(list[i].getMPGCity(), list[i]);
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

	system("PAUSE");
}
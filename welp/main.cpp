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
#include "BST.h"
#include "HashTable.h"
#include "Review.h"
#include "MaxHeap.h"

#include "Util.h"
#include "FileIO.h"
#include "Browse.h"
#include "Sort.h"

using namespace std;

// Menu Prototypes
void splashMenu(); // This is the splash menu for our app
void mainMenu();
void searchForCarsMenu(); // This is the menu for the search function
void searchForCarByNameMenu();
void searchForCarsByMakeMenu();
void searchForCarsByPriceMenu();
void testHashEfficiency();
void specialPrintMenu();
void miscMenu();
void statsMenu();
void saveCars(Car* cList);
void enterReviewMenu(string make, string model);

string userName;
Car* carList;
vector<string> carMakeVector;
HashTable<Review> reviewTable;
HashTable<int> viewTable;
BST<int, Car> mpgBST;
BST<int, Car> mpgFreewayBST;
BST<int, Car> priceBST;
BST<double, Car> avgRatingBST;
MaxHeap<int, Car> viewHeap;

// The rest of the program

int main()
{
    splashMenu();

    reviewTable = HashTable<Review>();
	viewTable = HashTable<int>();
    mpgBST = BST<int, Car>();
    priceBST = BST<int, Car>();
    avgRatingBST = BST<double, Car>();
    mpgFreewayBST = BST<int, Car>();
    viewHeap = MaxHeap<int, Car>(getArrayLength());

    carList = load();
    loadMpgBST(carList, mpgBST);
    loadPriceBST(carList, priceBST);
    loadMpgFreewayBST(carList, mpgFreewayBST);
    loadReviewTable(reviewTable);
    loadAvgRatingBST(carList, reviewTable, avgRatingBST);
    loadCarMake(carMakeVector, carList);
    loadViewHeap();

    mainMenu();

    saveReviews(reviewTable, carList);
	saveCars(carList);

    system("PAUSE");
    return 0;
}

void splashMenu()
{
	cout << "*************************************************************************" << endl;
	cout <<  " __    __     _ " << endl;
	cout <<  "/ / /\\ \\ \\___| |_ __  "<< endl;
	cout <<  "\\ \\/ \\ / / _ \\ | '_ \\ " << endl;
	cout <<  " \\  /\\  /  __/ | |_) |" << endl;
	cout <<  "  \\/  \\/ \\___|_| .__/ " << endl;
	cout <<  "               |_|    " << endl;
	cout << endl << "A 'Yelp' for Cars" << endl;
	cout << "*************************************************************************" << endl << endl;

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

    userName = getUserInputAsString();
}

// This is the only menu that should have a loop
void mainMenu()
{
    bool isGood = false;
    while (!isGood) {
        clearScreen();
		cout << "********************* MAIN MENU *********************" << endl << endl;
        cout << "1. Browse our list of cars" << endl;
        cout << "2. Search for a car" << endl;
        cout << "3. Sort cars by category" << endl;
        cout << "4. Misc" << endl;
        cout << "0. Quit" << endl << endl;
        cout << "Please select an option: ";

        int choice = getUserInputAsInt(0, 4);

        switch (choice)
        {
            case 0:
                isGood = true;
                break;
            case 1:
                browseForCarsMenu();
                break;
            case 2:
                searchForCarsMenu();
                break;
            case 3:
                sortByCategoryMenu();
                break;
            case 4:
                miscMenu();
                break;
        }
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

/**
 * Search For Cars Menu
 * Author(s): Chris
 *
 * This is the menu for the searching feature
 * There are 4 menu options:
 * 1. Search by Car Name
 * 2. Search by Car Manufacturer
 * 3. Search by Price Range
 * 0. Go Back
 */
void searchForCarsMenu()
{
    bool isGood = false;
    while (!isGood)
    {
        clearScreen();
        cout << "******************** Search for Cars *******************" << endl << endl;
        cout << "1. Search by car name" << endl;
        cout << "2. Search for cars by manufacturer" << endl;
        cout << "3. Search cars in a price range" << endl;
        cout << "0. Back" << endl << endl;
        cout << "What is your option? ";

        int choice = getUserInputAsInt(0, 3);

        switch (choice)
        {
            case 0:
                isGood = true;
                break;
            case 1:
                searchForCarByNameMenu();
                break;
            case 2:
                searchForCarsByMakeMenu();
                break;
            case 3:
                searchForCarsByPriceMenu();
                break;
        }
    }
}

/**
 * Search for Car by Car Name Menu
 * Author(s): Chris
 *
 * This is a part of the search feature
 */

void searchForCarByNameMenu()
{
    bool isGood = false;
    while (!isGood)
    {
        clearScreen();
        cout << "*************** Search for Car by Car Name ***************" << endl << endl;
        cout << "Please input a car name (i.e. Honda Accord)" << endl;
        cout << ": ";
        string name = getUserInputAsString();

        // This is a linear search
        // TODO: Convert this to a binary search
        for (int i = 0; i < getArrayLength(); i++)
        {
            // If the car's name is found, then render the car page for the user
            if (name.compare(carList[i].getName()) == 0)
            {
                carList[i].displayCarPage();
                return;
            }
        }

        cout << "Car not found!" << endl;
        cout << "Do you want to try again? (y/n) ";
        string choice = getUserInputAsString();

        // Check if the first character in the answer is a y or Y. If false, stop the loop.
        if (!(choice.at(0) == 'y' || choice.at(0) == 'Y'))
        {
            isGood = true;
        }
    }
}

/**
 * Search for Car by Car Make Menu
 * Author(s): Chris
 *
 * This is a part of the search feature
 */
void searchForCarsByMakeMenu()
{
    bool isGood = false;
    while (!isGood)
    {
        clearScreen();
        cout << "*************** Search for Car by Car Manufacturer ***************" << endl << endl;
        cout << "Please input a car name (i.e. Tesla) ";
        string name = getUserInputAsString();

        // This is a linear search
        // TODO: Convert this to a binary search
        for (int i = 0; i < carMakeVector.size(); i++)
        {
            // If the car's make exists, then call the list cars menu
            if (name.compare(carMakeVector[i]) == 0)
            {
                filterCarsMenu(name);
                return;
            }
        }

        cout << "Manufacturer not found!" << endl;
        cout << "Do you want to try again? (y/n) ";
        string choice = getUserInputAsString();

        // Check if the first character in the answer is a y or Y. If false, stop the loop.
        if (!(choice.at(0) == 'y' || choice.at(0) == 'Y'))
        {
            isGood = true;
        }
    }
}

/**
 * Search for Car by Price Menu
 * Author(s): Chris
 *
 * This is a part of the search feature
 */
void searchForCarsByPriceMenu()
{
    bool isGood = false;
    while (!isGood)
    {
        clearScreen();
        cout << "**************** Search for Car by Price Range ****************" << endl << endl;
        cout << "Please input the min price (i.e. $25000) $";
        int min = getUserInputAsInt(0, INT_MAX);

        cout << "Please input the max price (i.e. $50000) $";
        // Max can't be less than min
        int max = getUserInputAsInt(min, INT_MAX);

        vector<Car> cars;

        // This is a linear search
        // TODO: Convert this to a binary search
        for (int i = 0; i < getArrayLength(); i++)
        {
            // If car price is in range
            if (carList[i].getPrice() >= min && carList[i].getPrice() <= max)
            {
                cars.push_back(carList[i]);
            }
        }

        if (cars.size() == 0)
        {
            cout << "No cars found." << endl;

            cout << "Do you want to try again? (y/n) ";

            string choice = getUserInputAsString();

            // Check if the first character in the answer is a y or Y. If false, stop the loop.
            if (!(choice.at(0) == 'y' || choice.at(0) == 'Y'))
            {
                isGood = true;
            }
        }
        else
        {
            for (int i = 0; i < cars.size(); i++)
            {
                cout << i + 1 << ". " << cars[i].getName() << " - $" << cars[i].getPrice() << endl;
            }

            cout << "0 - Quit" << endl;

            cout << "What is your choice? ";
            int choice = getUserInputAsInt(0, cars.size());

            if (choice != 0) cars[choice - 1].displayCarPage();

            isGood = true;
        }
    }
}

void testHashEfficiency()
{
    int min = INT_MAX;
    int max = INT_MIN;
    int sum = 0;
    double size = getArrayLength();
    for (int i = 0; i < size; i++)
    {
        Car car = carList[i];
        int accesses = reviewTable.getNumAccesses(car.getMake(), car.getModel());
        if (accesses < min) min = accesses;
        if (accesses > max) max = accesses;
        sum = sum + accesses;
    }

    clearScreen();

    cout << "The load factor is: " << size/reviewTable.getTableSize() << endl;
    cout << "The minimum amount of accesses before finding a key's value is: " << min << endl;
    cout << "The maximum amount of accesses before finding a key's value is: " << max << endl;
    cout << "The average amount of accesses before finding a key's value is: " << sum/size << endl << endl;

    system("PAUSE");

}

void miscMenu()
{
    bool isGood = false;
    while (!isGood)
    {
        clearScreen();
        cout << "******************** Misc *******************" << endl << endl;
        cout << "1. Special print cars" << endl;
        cout << "2. View statistics" << endl;
        cout << "3. Test hash table efficiency" << endl;
        cout << "0. Back" << endl << endl;
        cout << "What is your option? ";

        int choice = getUserInputAsInt(0, 3);

        switch (choice)
        {
            case 0:
                isGood = true;
                break;
            case 1:
                specialPrintMenu();
                break;
            case 2:
                statsMenu();
                break;
            case 3:
                testHashEfficiency();
                break;
        }
    }
}

void specialPrintMenu()
{
    bool isGood = false;
    while (!isGood)
    {
        clearScreen();
        cout << "Special print cars with which parameter?" << endl;
        cout << "1. Print by MPG" << endl;
        cout << "2. Print by price" << endl;
        cout << "0. Return to misc" << endl;
        cout << ": ";

        int choice = getUserInputAsInt(0, 2);

        switch (choice)
        {
            case 0:
                isGood = true;
                break;
            case 1:
                mpgBST.levelOrderPrint();
                system("PAUSE");
                break;
            case 2:
                priceBST.levelOrderPrint();
                system("PAUSE");
                break;
        }
    }
}

void statsMenu()
{
    clearScreen();

    cout << "Total number of reviews in Welp: " << reviewTable.getTotalNumObjects() << endl;
    cout << "Total number of cars in Welp: " << getArrayLength() << endl << endl;

    cout << "Most viewed car: " << viewHeap.getMaxObject() << endl;

    cout << "Most reviewed car: " << reviewTable.getObjMostElements() << endl;
    cout << "Least reviewed car: " << reviewTable.getObjLeastElements() << endl << endl;

    cout << "Highest rated car: " << avgRatingBST.maximum().getName() <<endl;
	cout << "Least rated car: " << avgRatingBST.minimum().getName() << endl << endl;

    system("PAUSE");
}


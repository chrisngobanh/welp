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
#include "Search.h"

using namespace std;

// Menu Prototypes
void splashMenu(); // This is the splash menu for our app
void mainMenu();
void testHashEfficiency();
void specialPrintMenu();
void miscMenu();
void statsMenu();
void enterReviewMenu(string make, string model);

string userName;
Car* carList;
int numOfCars;
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

    numOfCars = getNumberOfCars();
    
    reviewTable = HashTable<Review>();
	viewTable = HashTable<int>();
    mpgBST = BST<int, Car>();
    priceBST = BST<int, Car>();
    avgRatingBST = BST<double, Car>();
    mpgFreewayBST = BST<int, Car>();
    viewHeap = MaxHeap<int, Car>(numOfCars);

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

    pauseProgram();
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

void testHashEfficiency()
{
    int min = INT_MAX;
    int max = INT_MIN;
    int sum = 0;
    double size = numOfCars;
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

    pauseProgram();

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
                pauseProgram();
                break;
            case 2:
                priceBST.levelOrderPrint();
                pauseProgram();
                break;
        }
    }
}

void statsMenu()
{
    clearScreen();

    cout << "Total number of reviews in Welp: " << reviewTable.getTotalNumObjects() << endl;
    cout << "Total number of cars in Welp: " << numOfCars << endl << endl;

    cout << "Most viewed car: " << viewHeap.getMaxObject() << endl;
    cout << "Most reviewed car: " << reviewTable.getMax() << endl;
    cout << "Highest rated car: " << avgRatingBST.maximum().getName() << endl << endl;

    pauseProgram();
}


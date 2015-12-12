// This is the main file for Welp, Yelp for Cars!
// Author(s): Han, Kevin, Carlos, Johnny, Chris

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
#include "Misc.h"

using namespace std;

// Menu Prototypes
void mainMenu();
void splashMenu();

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

/**
* Main
* Author(s): Han, Kevin, Carlos, Johnny, Chris
*
* This is the main function of the program.
*/
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

/**
* Main Menu
* Author(s): Han, Kevin, Carlos, Johnny, Chris
*
* This is the main menu of the program
*/
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

/**
* Splash Menu
* Author(s): Kevin, Johnny, Chris
*
* This is the splash menu
*/
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

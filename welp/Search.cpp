#include "Search.h"


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
        for (int i = 0; i < numOfCars; i++)
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
        for (int i = 0; i < numOfCars; i++)
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
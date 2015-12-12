#include "Browse.h"
#include "Util.h"

// Author(s): Jonathan
// Menu for the list of all the car makes
void browseForCarsMenu()
{
    bool isGood = false;
    while (!isGood)
    {
        clearScreen();
        cout << "********************* BROWSE MENU *********************" << endl << endl;
        cout << "Here is our selection of car makes"  << endl << endl;
        for (int i = 0; i < carMakeVector.size(); i++)
        {
            cout << i + 1 << ". " << carMakeVector[i] << endl;
        }
        cout << carMakeVector.size() + 1 << ". All" << endl;
        cout << "0. Back" << endl << endl;
        
        
        cout << "Pick a number to start browsing models: ";
        
        int choice = getUserInputAsInt(0, carMakeVector.size() + 1);
        
        switch (choice)
        {
            case 0:
                isGood = true;
                break;
            default:
                listCars(choice);
        }
    }
}

// Menu for when input is taken for the all the car makes. It takes input to filter to a specific car make or list all the cars
void listCars(int carType)
{
    if (carType > 0 && carType < carMakeVector.size() + 1)
        filterCarsMenu(carMakeVector[carType - 1]);
    else if (carType == carMakeVector.size() + 1)
        listAllCarsMenu();
}

// Menu for the list of all the cars of a specified car make (e.g. Honda or Tesla)
void filterCarsMenu(string carMake)
{
    clearScreen();
    cout << "******************** CAR LIST ********************" << endl << endl;
    int count = 0;
    Car filteredCars[30];
    for (int i = 0; i < getArrayLength(); i++)
    {
        if (carList[i].getMake() == carMake)
        {
            count++;
            filteredCars[count - 1] = carList[i];
            cout << count << ". ";
            cout << carList[i].getMake() << " ";
            cout << carList[i].getModel() << endl;
        }
    }
    
    cout << "0. Back" << endl << endl;
    cout << "Make a selection: ";
    
    int choice = getUserInputAsInt(0, count);
    
    if (choice != 0) filteredCars[choice - 1].displayCarPage();
}

// Menu for the list of all the cars of a specified car make (e.g. Honda or Tesla)
void listAllCarsMenu()
{
    clearScreen();
    cout << "******************* ALL CARS MENU ********************" << endl << endl;
    // Print out list of all cars
    for (int i = 1; i < getArrayLength() + 1; i++)
    {
        cout << i << ". ";
        cout << carList[i - 1].getMake() << " ";
        cout << carList[i - 1].getModel() << endl;
    }
    cout << "0. Quit" << endl;
    
    // Input validation by checking for integer and range
    int choice = getUserInputAsInt(0, getArrayLength());
    
    if (choice != 0) carList[choice - 1].displayCarPage();
}
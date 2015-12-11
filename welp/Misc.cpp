#include "Misc.h"
//Author: Kevin
//
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

//Autor: Kevin
// Shows a menu where the user has an option to view the special print menu, view statistics, view hash table efficiency, or return
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

//Author: Kevin
// Level order prints the cars by price or MPG
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

//Author: Han
// Displays the following statistics: # of reviews/cars, most/least reviewed car, and highest rated car
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

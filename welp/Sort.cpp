#include "Sort.h"

void sortByCategoryMenu()
{
    bool isGood = false;
    while (!isGood)
    {
        clearScreen();
        cout << "********************* CATEGORY MENU *********************" << endl << endl;
        cout << "1. MPG City" << endl;
        cout << "2. MPG Freeway" << endl;
        cout << "3. Price" << endl;
        cout << "4. Rating" << endl;
        cout << "0. Back" << endl << endl;
        cout << "What would you like to sort cars by? ";
        
        int choice = getUserInputAsInt(0, 4);
        
        switch (choice)
        {
            case 0:
                isGood = true;
                break;
            case 1:
                sortByMpgMenu();
                break;
            case 2:
                sortByMpgFreewayMenu();
                break;
            case 3:
                sortByPriceMenu();
                break;
            case 4:
                sortByRatingMenu();
                break;
        }
    }
}

void sortByMpgMenu()
{
    vector<Car> carVector;
    int min = INT_MIN;
    int max = INT_MAX;
    mpgBST.getVectorInOrder(min, max, carVector);
    
    clearScreen();
    cout << "******************* SORTED MPG LIST *******************" << endl << endl;
    
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
    
    int choice = getUserInputAsInt(0, count);
    
    if (choice != 0) carVector[choice - 1].displayCarPage();
}

void sortByMpgFreewayMenu()
{
    vector<Car> carVector;
    int min = INT_MIN;
    int max = INT_MAX;
    mpgFreewayBST.getVectorInOrder(min, max, carVector);
    
    clearScreen();
    cout << "****************** SORTED MPG FREEWAY LIST ******************" << endl << endl;
    
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
    
    int choice = getUserInputAsInt(0, count);
    
    if (choice != 0) carVector[choice - 1].displayCarPage();
}

void sortByPriceMenu()
{
    vector<Car> carVector;
    int min = INT_MIN;
    int max = INT_MAX;
    priceBST.getVectorInOrder(min, max, carVector);
    
    clearScreen();
    cout << "******************* SORTED PRICE LIST *******************" << endl << endl;
    int count = 0;
    for (int i = 0; i < carVector.size(); i++)
    {
        count++;
        cout << count << ". ";
        cout << carVector[i].getMake() << " ";
        cout << carVector[i].getModel() << "/ Price: $";
        cout << carVector[i].getPrice() << endl;
    }
    
    cout << "0. Back" << endl;
    
    int choice = getUserInputAsInt(0, count);
    
    if (choice != 0) carVector[choice - 1].displayCarPage();
}

void sortByRatingMenu()
{
    vector<Car> carVector;
    int min = INT_MIN;
    int max = INT_MAX;
    avgRatingBST.getVectorInOrder(min, max, carVector);
    
    clearScreen();
    cout << "****************** SORTED RATING FREEWAY LIST ******************" << endl << endl;
    
    int count = 0;
    for (int i = 0; i < carVector.size(); i++)
    {
        count++;
        cout << count << ". ";
        cout << carVector[i].getMake() << " ";
        cout << carVector[i].getModel() << "/ ";
        cout << reviewTable.getAverageRatingBucket(carVector[i].getMake(), carVector[i].getModel()) << " stars" << endl;
    }
    
    cout << "0. Back" << endl;
    
    int choice = getUserInputAsInt(0, count);
    
    if (choice != 0) carVector[choice - 1].displayCarPage();
}

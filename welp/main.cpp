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

using namespace std;

// Menu Prototypes
void splashMenu(); // This is the splash menu for our app
void mainMenu();
void searchForCarsMenu(); // This is the menu for the search function
void searchForCarByNameMenu();
void searchForCarsByMakeMenu();
void searchForCarsByPriceMenu();
void browseForCarsMenu();
void displayCarPage(Car &car);
void listAllCarsMenu();
void enterReview(string make, string model);
void sortByCategoryMenu();
void sortByMpgMenu();
void sortByMpgFreewayMenu();
void sortByPriceMenu();
void sortByRatingMenu();
void filterCarsMenu(string);
void testHashEfficiency();
void specialPrintMenu();
void miscMenu();
void statsMenu();
void quickSort(int low, int high);
void saveCars(Car* cList);

Car* load();
int getArrayLength();
void loadMpgBST(Car* list, BST<int, Car> &bst);
void loadMpgFreewayBST(Car* list, BST<int, Car> &bst);
void loadPriceBST(Car* list, BST<int, Car> &bst);
void loadReviewTable(HashTable<Review> &table);
void loadAvgRatingBST(Car* list, HashTable<Review> &table, BST<double, Car> &bst);
void loadCarMake(vector<string>& makeList, Car* cList);
void saveReviews(HashTable<Review> &Table, Car* list);
void listCars(int);

Car* carList;
string userName;
HashTable<Review> reviewTable;
HashTable<int> viewTable;
BST<int, Car> mpgBST;
BST<int, Car> mpgFreewayBST;
BST<int, Car> priceBST;
BST<double, Car> avgRatingBST;
vector<string> carMakeVector;

// Handler Functions (Reusable Code)

/**
 * Is Integer Handler
 * Author(s): Johnny
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
 * Author(s): Chris
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
 * Get User Input Handler (String)
 * Author(s): Chris
 *
 * This function gets user input when called.
 * It returns the user input as string.
 * Ignores empty lines
 */
string getUserInputAsString()
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
 * Get User Input Handler (Int)
 * Author(s): Chris
 *
 * This function gets user input when called.
 * It returns the user input as int.
 * Ignores empty lines and bad input
 */
int getUserInputAsInt()
{
    while (true) {
        string input = getUserInputAsString();
        int intInput = convertStringToInt(input);
        
        if (intInput == -1)
        {
            cout << "Invalid Input. Try again: ";
        }
        else
        {
            return intInput;
        }
    }
}

/**
 * Get User Input Handler (Int)
 * Author(s): Chris
 *
 * This function gets user input when called.
 * First parameter (int) is the min value that the input can be
 * Second parameter (int) is the max value that the input can be
 * It returns the user input as int.
 * Ignores empty lines and bad input
 */
int getUserInputAsInt(int min, int max)
{
    while (true) {
        int intInput = getUserInputAsInt();
        
        if (intInput < min || intInput > max)
        {
            cout << "Invalid Input. Try again: ";
        }
        else
        {
            return intInput;
        }
    }
}

/**
 * Get User Input Handler (Int)
 * Author(s): Chris
 *
 * This function gets user input when called.
 * First parameter (int) is the min value that the input can be
 * Second parameter (size_t) is the max value that the input can be
 * It returns the user input as int.
 * Ignores empty lines and bad input
 */
int getUserInputAsInt(int min, size_t max)
{
    return getUserInputAsInt(min, (int)max);
}

/**
 * Clear Screen Handler
 * Author(s): Chris
 *
 * This function clears the screen by making a lot of empty new lines
 * This method is cross platform
 */
#ifdef _WIN32
void clearScreen()
{
    system("CLS");
}

#else

void clearScreen()
{
    cout << string( 100, '\n' );
}

#endif
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

    carList = load();
    loadMpgBST(carList, mpgBST);
    loadPriceBST(carList, priceBST);
    loadMpgFreewayBST(carList, mpgFreewayBST);
    loadReviewTable(reviewTable);
    loadAvgRatingBST(carList, reviewTable, avgRatingBST);
    loadCarMake(carMakeVector, carList);

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
    
    if (choice != 0) displayCarPage(carVector[choice - 1]);
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
    
    if (choice != 0) displayCarPage(carVector[choice - 1]);
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
    
    if (choice != 0) displayCarPage(carVector[choice - 1]);
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
		cout << carVector[i].getModel() << "/ RATING: ";
		cout << reviewTable.getAverageRatingBucket(carVector[i].getMake(), carVector[i].getModel()) << endl;
	}

	cout << "0. Back" << endl;

    int choice = getUserInputAsInt(0, count);
    
    if (choice != 0) displayCarPage(carVector[choice - 1]);
}


void listCars(int carType)
{
	if (carType > 0 && carType < carMakeVector.size() + 1)
		filterCarsMenu(carMakeVector[carType - 1]);
    else if (carType == carMakeVector.size() + 1)
        listAllCarsMenu();
}

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
    
    if (choice != 0) displayCarPage(filteredCars[choice - 1]);
}

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

    if (choice != 0) displayCarPage(carList[choice - 1]);
}

void displayCarPage(Car &car)
{
    //Increment the car's view count. Outside the while loop so that it only counts "unique" views.

	int views = viewTable.getFront(car.getMake(), car.getModel());
	viewTable.clearIndex(car.getMake(), car.getModel());
	viewTable.addItem(car.getMake(), car.getModel(), views + 1);
    
    bool isGood = false;
    while (!isGood)
    {
        clearScreen();
        cout << "************************ " << car.getMake() << " " << car.getModel() << " ************************" << endl << endl;
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
        cout << endl;
        cout << "Engine Type: " << car.getEngine() << endl;
        cout << "MPG City: " << car.getMPGCity() << endl;
        cout << "MPG Freeway: " << car.getMPGFreeway() << endl;
        cout << "Price: $" << car.getPrice() << endl;
        cout << "Rating: " << reviewTable.getAverageRatingBucket(car.getMake(), car.getModel()) << endl;

        ///////////////Reviews Menu////////////////

        cout << endl << endl << endl;
        cout << "************* Review Menu *************" << endl << endl;
        cout << "1. View list of reviews" << endl;
        cout << "2. Add a review" << endl;
        cout << "3. Delete your previous review" << endl;
        cout << "0. Back" << endl << endl;
        cout << "What is your choice?  ";


        int choice = getUserInputAsInt(0, 3);
        
        switch (choice)
        {
            case 0:
                isGood = true;
                break;
            case 1:
                clearScreen();
                cout << "Printing out all reviews for the " << car.getMake() << " " << car.getModel() << ":" << endl << endl;
                reviewTable.printBucket(car.getMake(), car.getModel());
                system("PAUSE");
                break;
            case 2:
                enterReview(car.getMake(), car.getModel());
                break;
            case 3:
                Review review = Review(userName);
                if ( reviewTable.removeItem(car.getMake(), car.getModel(), review) )
                {
                    cout << "Your review has successfully been deleted." << endl;
                } else cout << "Could not find a review under the username \"" << userName << "\"." << endl;
                
                system("PAUSE");
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

//Make/Model/MPG City/MPG Freeway/Car Type/Engine Type/Price
//Honda,Civic (Sedan),25,40,Sedan,Gasoline,25000

Car* load()
{
    Car* list = new Car[getArrayLength()];
    string line;
    int index = 0;

    int substr_start, offset;

    string make, model, type, engine;
    int mpgcity, mpgfree, msrp, views;

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
            while (line[substr_start + offset] != divider)
            {
                offset++;
            }
            msrp = atoi(line.substr(substr_start, offset).c_str());
            substr_start = substr_start + offset + 1;
            offset = 0;

            //Get the views
            while (line[substr_start + offset] != NULL)
            {
                offset++;
            }
            views = atoi(line.substr(substr_start, offset).c_str());
            substr_start = substr_start + offset + 1;
            offset = 0;

            //make << model << engine << mpgcity <<  mpgfree << msrp
            list[index] = Car(make, model, engine, mpgcity, mpgfree, msrp);
           
			viewTable.addItem(make, model, views);
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

/* Function to get user's review on a vehicle */
void enterReview(string make, string model)
{
    clearScreen();
    cout << "Give us your thoughts on the " << make << " " << model << "." << endl;
    cout << ": ";
    string description = getUserInputAsString();
    cout << endl;
    cout << "How many stars does the vehicle deserve? " << endl;
    cout << ": ";
    int stars = getUserInputAsInt(0, 5);

    Review newReview(userName, description, stars, make, model);
    reviewTable.addItem(make, model, newReview);

    cout << "Your review has successfully been added." << endl;
    system("PAUSE");
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
                displayCarPage(carList[i]);
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

            if (choice != 0) displayCarPage(cars[choice - 1]);
            
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
    clearScreen();

    cout << "******************** Misc *******************" << endl << endl;
    cout << "1. Special print cars" << endl;
    cout << "2. View statistics" << endl;
    cout << "3. Test hash table efficiency" << endl;
    cout << "0. Back" << endl << endl;
    cout << "What is your option? ";
    string choice = getUserInputAsString();

	if (choice == "0") return;

    if (choice == "1")
    {
        specialPrintMenu();
    }
    else if (choice == "2")
    {
        statsMenu();
    }
    else if (choice == "3")
    {
        testHashEfficiency();
    }

    miscMenu();
}

void specialPrintMenu()
{
    clearScreen();

    cout << "Special print cars with which parameter?" << endl;
    cout << "1. Print by MPG" << endl;
    cout << "2. Print by price" << endl;
    cout << "0. Return to misc" << endl;
    cout << ": ";

    int choice = convertStringToInt(getUserInputAsString());

    if (choice == 0) return;
    if (choice == 1) mpgBST.levelOrderPrint();
    else if (choice == 2) priceBST.levelOrderPrint();

    cout << endl;

    system("PAUSE");

    specialPrintMenu();
}

void statsMenu()
{
    clearScreen();

    cout << "Total number of reviews in Welp: " << reviewTable.getTotalNumObjects() << endl;
    cout << "Total number of cars in Welp: " << getArrayLength() << endl << endl;

    cout << "Most viewed car: " << viewTable.getMax() << endl;
    cout << "Least viewed car: " << viewTable.getMin() << endl << endl;

    cout << "Most reviewed car: " << reviewTable.getObjMostElements() << endl;
    cout << "Least reviewed car: " << reviewTable.getObjLeastElements() << endl << endl;

    cout << "Highest rated car: " << avgRatingBST.maximum().getName() <<endl;
	cout << "Least rated car: " << avgRatingBST.minimum().getName() << endl << endl;

//  cout << "The number of cars inside the database is: " << getArrayLength() << endl;
//	cout << "The number of reviews inside the database is: " << reviewTable.getNumObjects() << endl;
//	cout << "The most viewed car is: " << endl;
//	cout << "The least viewed car is: " << endl;
//	cout << "The most reviewed car is: " << endl;
//	cout << "The least reviewed car is: " << endl;
//	cout << "The highest rated car is: " << endl;
//	cout << "The lowest rated car is: " << endl;

    system("PAUSE");
}

void quickSort(int low, int high)
{
    int pivot = low + (high-low)/2;
    int value_of_pivot = carList[pivot].getViews();
    int left = low;
    int right = high;
    while (left <= right)
    {
        while (carList[left].getViews() < value_of_pivot)
        {
            left++;
        }
        while (carList[right].getViews() > value_of_pivot)
        {
            right--;
        }
        if (left <= right)
        {
            Car temp = carList[left];
            carList[left] = carList[right];
            carList[right] = temp;
            left++;
            right--;
        }
    }
    if (low < right) quickSort(low, right);
    if (left < high) quickSort(left, high);
}


void saveCars(Car* cList)
{
	// Make/Model/MPGe City/MPGe Highway/Type/Price/Views

	int size = getArrayLength();
	ofstream save("Kars Data.txt");

	if (save.is_open())
	{
		// Checks every car for reviews
		for (int i = 0; i < size; i++)
		{
			save << cList[i].getMake() << "/" << cList[i].getModel() << "/" << cList[i].getMPGCity() << "/" << cList[i].getMPGFreeway() << "/" << cList[i].getEngine() << "/" << cList[i].getPrice() << "/" << viewTable.getFront(cList[i].getMake(), cList[i].getModel()) << endl;
		}
		save.close();
	}
	else
	{
		cout << "Error : Unable to open file 'Kars Data.txt' ";
		exit(-1);
	}

}

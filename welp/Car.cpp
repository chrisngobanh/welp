#include "Car.h"

/**
 * Car Constructor
 * Author(s): Chris, Johnny
 *
 * Creates a car object
 * Initializes every field
 */
Car::Car()
{
	make = "";
	model = "";
	engine = "";
	MPGCity = 0;
	MPGFreeway = 0;
	price = 0;
}

/**
 * Car Constructor
 * Author(s): Chris, Johnny
 *
 * Creates a car object
 * Overloaded function that initializes every field with inputs
 */
Car::Car(string _make, string _model, string _engine, int _MPGCity, int _MPGFreeway, int _price)
{
	make = _make;
	model = _model;
	engine = _engine;
	MPGCity = _MPGCity;
	MPGFreeway = _MPGFreeway;
	price = _price;
}

/**
 * Get Make
 * Author(s): Chris, Johnny
 *
 * Returns the make field
 */
string Car::getMake() {
	return make;
}

/**
 * Get Model
 * Author(s): Chris, Johnny
 *
 * Returns the model field
 */
string Car::getModel()
{
	return model;
}

/**
 * Get Name
 * Author(s): Chris, Johnny
 *
 * Returns the name field
 */
string Car::getName()
{
	return make + " " + model;
}

/**
 * Get Engine
 * Author(s): Chris, Johnny
 *
 * Returns the engine field
 */
string Car::getEngine()
{
	return engine;
}

/**
 * Get MPG City
 * Author(s): Chris, Johnny
 *
 * Returns the mpg city field
 */
int Car::getMPGCity()
{
	return MPGCity;
}

/**
 * Get MPG Freeway
 * Author(s): Chris, Johnny
 *
 * Returns the mpg freeway field
 */
int Car::getMPGFreeway()
{
	return MPGFreeway;
}

/**
 * Get Price
 * Author(s): Chris, Johnny
 *
 * Returns the price field
 */
int Car::getPrice()
{
	return price;
}

/**
 * << Operator
 * Author(s): Kevin
 *
 * Overloads the << operator. Outputs the car make and model
 * Ex. Honda Accord
 */
ostream& operator<<(ostream &os, const Car &car)
{
	os << car.make << ' ' << car.model;
	return os;
}

/**
 * == Operator
 * Author(s): Kevin
 *
 * Overloads the == operator.
 * Returns true if the models match
 */
bool Car::operator==(const Car &car)
{
    return (car.model == this->model);
}

/**
 * != Operator
 * Author(s): Kevin
 *
 * Overloads the != operator
 * Returns true if the models don't match
 */
bool Car::operator!=(const Car &car)
{
    return !(*this == car);
}

/**
 * Display Car Page
 * Author(s): Carlos, Kevin
 *
 * Print the car page.
 * Displays the car specs to the console.
 */
void Car::displayCarPage()
{
    //Increment the car's view count. Outside the while loop so that it only counts "unique" views.

    int views = viewTable.getFront(make, model);
    viewTable.clearIndex(make, model);
    viewTable.addItem(make, model, views + 1);
    viewHeap.iterateValue(*this, 1);

    bool isGood = false;
    while (!isGood)
    {
        clearScreen();
        cout << "************************ " << make << " " << model << " ************************" << endl;
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
        cout << "Engine Type: " << engine << endl;
        cout << "MPG City: " << MPGCity << endl;
        cout << "MPG Freeway: " << MPGFreeway << endl;
        cout << "Price: $" << price << endl;
        cout << "Rating: " << reviewTable.getAverageRatingBucket(make, model) << " stars" << endl;
        cout << "Views: " << viewTable.getFront(make, model) << endl;

        /****** Reviews Menu -----
         *
         * Coder: Carlos Quirarte
         *
         *****/
        cout << "************* Review Menu *************" << endl;
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
                cout << "Printing out all reviews for the " << make << " " << model << ":" << endl << endl;
                reviewTable.printBucket(make, model);
                pauseProgram();
                break;
            case 2:
                enterReviewMenu(make, model);
                break;
            case 3:
                Review review = Review(userName);
                if ( reviewTable.removeItem(make, model, review) )
                {
                    cout << "Your review has successfully been deleted." << endl;
                } else cout << "Could not find a review under the username \"" << userName << "\"." << endl;

                pauseProgram();
                break;
        }
    }
}


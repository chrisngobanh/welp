#include <string>
#include <vector>

#include "Util.h"
#include "Car.h"
#include "Browse.h"

using namespace std;

extern Car* carList;
extern vector<string> carMakeVector;

void searchForCarsMenu(); // This is the menu for the search function
void searchForCarByNameMenu();
void searchForCarsByMakeMenu();
void searchForCarsByPriceMenu();

extern int getArrayLength();
// Author(s): Johnny

#include "FileIO.h"
#include "Util.h"
#include "Car.h"

using namespace std;

extern vector<string> carMakeVector;
extern Car* carList;

void browseForCarsMenu();
void listAllCarsMenu();
void listCars(int carType);
void filterCarsMenu(string carMake);
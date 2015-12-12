// Author(s): Kevin, Han
#include "Util.h"
#include "BST.h"
#include "Car.h"

void testHashEfficiency();
void specialPrintMenu();
void miscMenu();
void statsMenu();
void enterReviewMenu(string make, string model);

extern int numOfCars;
extern Car* carList;
extern HashTable<Review> reviewTable;
extern BST<int, Car> mpgBST;
extern BST<int, Car> priceBST;
extern BST<double, Car> avgRatingBST;
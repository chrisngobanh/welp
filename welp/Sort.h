#include <iostream>
#include <vector>

#include "Util.h"
#include "BST.h"
#include "Car.h"

using namespace std;

extern BST<int, Car> mpgBST;
extern BST<int, Car> mpgFreewayBST;
extern BST<int, Car> priceBST;
extern BST<double, Car> avgRatingBST;

void sortByCategoryMenu();
void sortByMpgMenu();
void sortByMpgFreewayMenu();
void sortByPriceMenu();
void sortByRatingMenu();
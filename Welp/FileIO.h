#include <string>
#include <fstream>

#include "Car.h"
#include "Review.h"
#include "HashTable.h"
#include "BST.h"

using namespace std;

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

extern vector<string> carMakeVector;
extern HashTable<Review> reviewTable;
extern HashTable<int> viewTable;
extern BST<int, Car> mpgBST;
extern BST<int, Car> mpgFreewayBST;
extern BST<int, Car> priceBST;
extern BST<double, Car> avgRatingBST;

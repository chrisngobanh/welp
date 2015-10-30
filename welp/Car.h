#ifndef CAR_H
#define CAR_H
#include <string>
#include "Rating.h"
#include "List.h"

using namespace std;

// Car Objects will never be manipulated after its creation.
class Car
{

private:
	string make; // i.e. Ford
	string model; // i.e. Mustang (Coupe)
	string type; // i.e. Coupe
	string engine; // i.e. ICE

	int MPGCity; // i.e. 22
	int MPGFreeway; // i.e. 31
	int price; // i.e. 23895

public:
	// Constructor
	Car();
	Car(string _make, string _model, string _type, string _engine, int _MPGCity, int _MPGFreeway, int _price);
	
	// Getters
	string getMake();
	string getModel();
	string getType();
	string getEngine();
	
	int getMPGCity();
	int getMPGFreeway();
	int getPrice();

	List<Rating> ratings[5];
};

#endif
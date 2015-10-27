#ifndef RATING_H
#define RATING_H
#include <string>

#include "User.h"
#include "Car.h"

using namespace std;

// TODO: Add a feature to allow editing Ratings
class Rating
{
private:
	string description;
	int stars;
	User owner;
	Car car;

public:
	// Constructor
	Rating();
	Rating(string _description, int _stars, User _owner, Car _car);

	// Getters
	string getDescription();
	int getStars();
	User getOwner();
	Car getCar();
};

#endif
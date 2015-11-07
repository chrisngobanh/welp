#ifndef RATING_H
#define RATING_H
#include <string>

using namespace std;

// TODO: Add a feature to allow editing Ratings
class Rating
{
private:
	string description;
	int stars;
	string owner;

public:
	// Constructor
	Rating();
	Rating(string _description, int _stars, string _owner);

	// Getters
	string getDescription();
	int getStars();
	string getOwner();
    
    // Setters
    void changeDescription(string _description);
    void changeStars(int _stars);
    void changeOwner(string _owner);
};

#endif
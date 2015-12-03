// Authors(s): Chris, Kevin, Han, Carlos

#ifndef REVIEW_H
#define REVIEW_H
#include <string>
#include <iostream>
#include <iomanip>

#include "Util.h"
#include "HashTable.h"

using namespace std;

extern string userName;

void enterReview(string make, string model);

//A review from a user for a specific car. Can be edited by the user (stars and description)
class Review
{

private:

    //Information displayed to the user
    string owner;
    string description;
    int stars;

    //Identifiers for what car the review is for
    string make;
    string model;

public:

    //Constructors
    Review();
    Review(string _owner);
    Review(string _owner, string _description, int _stars, string _make, string _model);

    //Getters
    string getOwner();
    string getDescription();
    int getStars();

    string getMake();
    string getModel();

    //Setters (only the description and stars should be changed)
    void setDescription(string _description);
    void setStars(int _stars);

    //Operator overload
    bool operator==(const Review &review);
    bool operator!=(const Review &review);
    //compares if the owners are the same

    friend ostream& operator<<(ostream &os, const Review &review);
    //so that Review can be printed

    operator const int()
    {
        return stars;
    };
    //int cast for getting the average stars

};

extern HashTable<Review> reviewTable;
#endif // REVIEW_H
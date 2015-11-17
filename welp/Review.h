#ifndef REVIEW_H
#define REVIEW_H
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

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

#endif // REVIEW_H

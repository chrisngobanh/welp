#include "Review.h"

/**
 * Review Constructor
 * Author(s): Carlos
 *
 * Creates a review object.
 * Initializes all the fields
 */
Review::Review()
{
    owner = "";
    description = "";
    stars = 0;
    make = "";
    model = "";
}

/**
 * Review Constructor
 * Author(s): Carlos
 *
 * Creates a review object.
 * Initializes all the fields. Gets owner as an argument
 */
Review::Review(string _owner)
{
    owner = _owner;
    description = "";
    stars = 0;
    make = "";
    model = "";
}

/**
 * Review Constructor
 * Author(s): Carlos
 *
 * Initializes all the fields. Gets all the fields as arguments
 */
Review::Review(string _owner, string _description, int _stars, string _make, string _model)
{
    owner = _owner;
    description = _description;
    stars = _stars;
    make = _make;
    model = _model;
}

/**
 * Get Owner
 * Author(s): Carlos
 *
 * Returns the owner of the review
 */
string Review::getOwner()
{
    return owner;
}

/**
 * Get Description
 * Author(s): Carlos
 *
 * Returns the description the user gave
 */
string Review::getDescription()
{
    return description;
}

/**
 * Get Stars
 * Author(s): Carlos
 *
 * Returns the rating the user gave
 */
int Review::getStars()
{
    return stars;
}

/**
 * Get Make
 * Author(s): Carlos
 *
 * Returns the make of the car that this review belongs to
 */
string Review::getMake()
{
    return make;
}

/**
 * Get Model
 * Author(s): Carlos
 *
 * Returns the model of the car that this review belongs to
 */
string Review::getModel()
{
    return model;
}

/**
 * Set Description
 * Author(s): Carlos
 *
 * Changes the description in the review to a new one
 */
void Review::setDescription(string _description)
{
    description = _description;
}

/**
 * Set Stars
 * Author(s): Carlos
 *
 * Changes the stars in the review to a new amount
 */
void Review::setStars(int _stars)
{
    stars = _stars;
}

/**
 * == Operator
 * Author(s): Carlos
 *
 * Checks if the reviews are the same.
 * Returns true if the owners are the same
 */
bool Review::operator==(const Review &review)
{
    return ( this->owner == review.owner );
}

/**
 * != Operator
 * Author(s): Carlos
 *
 * Checks if the reviews are the same.
 * Returns true if the owners are not the same
 */
bool Review::operator!=(const Review &review)
{
    return !(*this == review);
}

/**
 * << Operator
 * Author(s): Carlos
 *
 * Overloads the << operator.
 * Outputs the review in pretty formatting
 */
ostream& operator<<(ostream &os, const Review &review)
{
    int width = 18 - static_cast<int>(review.make.size());
    os << review.make << " " << setw(width) << left << review.model << "  Rating: " << review.stars << " stars" << endl;
    os << review.owner << " comments:" << endl;
    os << review.description;
	return os;
}

/**
 * Enter Review
 * Author(s): Carlos
 *
 * A submenu for the user to add a review for a car
 */
/* Function to get user's review on a vehicle */
void enterReview(string make, string model)
{
    clearScreen();
    cout << "Give us your thoughts on the " << make << " " << model << "." << endl;
    cout << ": ";
    string description = getUserInputAsString();
    cout << endl;
    cout << "How many stars does the vehicle deserve? " << endl;
    cout << ": ";
    int stars = getUserInputAsInt(0, 5);

    Review newReview(userName, description, stars, make, model);
    reviewTable.addItem(make, model, newReview);

    cout << "Your review has successfully been added." << endl;
    pauseProgram();
}

/**
 * Enter Review Menu
 * Author(s): Kevin
 *
 * A menu that asks if the user would like to overwrite their review if it exists
 * or simply to add a review if it doesn't already exist
 */
void enterReviewMenu(string make, string model)
{
    clearScreen();
    Review review = Review(userName);
    if (reviewTable.isInTable(make, model, review))
    {
        cout << "Would you like to overwrite your exisiting review?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        int input = getUserInputAsInt(1, 2);

        switch (input)
        {
            case 1:
                break;
            case 2:
                return;
        }

    }
    enterReview(make, model);
    pauseProgram();
}

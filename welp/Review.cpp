#include "Review.h"

Review::Review()
{
    owner = "";
    description = "";
    stars = 0;
    make = "";
    model = "";
}

Review::Review(string _owner)
{
    owner = _owner;
    description = "";
    stars = 0;
    make = "";
    model = "";
}

Review::Review(string _owner, string _description, int _stars, string _make, string _model)
{
    owner = _owner;
    description = _description;
    stars = _stars;
    make = _make;
    model = _model;
}

string Review::getOwner()
{
    return owner;
}

string Review::getDescription()
{
    return description;
}

int Review::getStars()
{
    return stars;
}

string Review::getMake()
{
    return make;
}

string Review::getModel()
{
    return model;
}

void Review::setDescription(string _description)
{
    description = _description;
}

void Review::setStars(int _stars)
{
    stars = _stars;
}

bool Review::operator==(const Review &review)
{
    return ( this->owner == review.owner );
}

bool Review::operator!=(const Review &review)
{
    return !(*this == review);
}

ostream& operator<<(ostream &os, const Review &review)
{
    int width = 18 - static_cast<int>(review.make.size());
    os << review.make << " " << setw(width) << left << review.model << "  Rating: " << review.stars << " stars" << endl;
    os << review.owner << " comments:" << endl;
    os << review.description;
	return os;
}

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

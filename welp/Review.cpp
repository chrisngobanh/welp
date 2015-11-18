#include "Review.h"

Review::Review()
{
    owner = "";
    description = "";
    stars = 0;
    make = "";
    model = "";
};

Review::Review(string _owner, string _description, int _stars, string _make, string _model)
{
    owner = _owner;
    description = _description;
    stars = _stars;
    make = _make;
    model = _model;
};

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
    int width = 18 - review.make.size();
    os << review.make << " " << setw(width) << left << review.model << "  Rating: " << review.stars << endl;
    os << review.owner << " comments:" << endl;
    os << review.description;
	return os;
}

#include "Rating.h"

Rating::Rating()
{}

// Getter Function Definitions //
Rating::Rating(string _description, int _stars, string _owner)
{
	description = _description;
	stars = _stars;
	owner = _owner;
}

string Rating::getDescription()
{
	return description;
}

int Rating::getStars()
{
	return stars;
}

string Rating::getOwner()
{
	return owner;
}

// Setter Function Definitions //
void Rating::changeDescription(string _description)
{
    description = _description;
}
void Rating::changeStars(int _stars)
{
    stars = _stars;
}
void Rating::changeOwner(string _owner)
{
    owner = _owner;
}






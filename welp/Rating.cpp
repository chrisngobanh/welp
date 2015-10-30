#include "Rating.h"

Rating::Rating()
{}

Rating::Rating(string _description, int _stars, User _owner)
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

User Rating::getOwner()
{
	return owner;
}
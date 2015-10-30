#include "Rating.h"

Rating::Rating()
{}


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
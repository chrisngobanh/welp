#include "Rating.h"

Rating::Rating(string _description, int _stars, User _owner, Car _car)
{
	description = _description;
	stars = _stars;
	owner = _owner;
	car = _car;
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

Car Rating::getCar()
{
	return car;
}
#include "User.h"

User::User()
{}


User::User(string _name)
{
	name = _name;
}

string User::getName()
{
	return name;
}
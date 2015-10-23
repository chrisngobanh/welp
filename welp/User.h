#ifndef USER_H
#define USER_H
#include <string>

using namespace std;
class User
{
private:
	string name;
public:
	User();
	User(string _name);

	string getName();
};

#endif
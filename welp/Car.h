#ifndef CAR_H
#define CAR_H
#include "Rating.h"

using namespace std;
class Car
{
public:
	Car();
	Rating getRating();
private:
	Rating rating;
};

#endif
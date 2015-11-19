#include "Car.h"

Car::Car()
{
	make = "";
	model = "";
	engine = "";
	MPGCity = 0;
	MPGFreeway = 0;
	price = 0;
}

Car::Car(string _make, string _model, string _engine, int _MPGCity, int _MPGFreeway, int _price)
{
	make = _make;
	model = _model;
	engine = _engine;
	MPGCity = _MPGCity;
	MPGFreeway = _MPGFreeway;
	price = _price;
}

string Car::getMake() {
	return make;
}

string Car::getModel()
{
	return model;
}

string Car::getName()
{
	return make + " " + model;
}



string Car::getEngine()
{
	return engine;
}

int Car::getMPGCity()
{
	return MPGCity;
}

int Car::getMPGFreeway()
{
	return MPGFreeway;
}

int Car::getPrice()
{
	return price;
}

ostream& operator<<(ostream &os, const Car &car)
{
	os << car.make << '/' << car.model << '/' << car.MPGCity << '/' << car.MPGFreeway << '/' << car.engine << '/' << car.price;
	return os;
}

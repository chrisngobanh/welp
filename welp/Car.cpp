#include "Car.h"

Car::Car()
{

}

Car::Car(string _make, string _model, string _type, string _engine, int _MPGCity, int _MPGFreeway, int _price) 
{
	make = _make;
	model = _model;
	type = _type;
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

string Car::getType()
{
	return type;
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

#include "Person.h"


int Person::current_id = 0;

Person::Person(const string& name): id(++current_id)
{
	this->name = name;
}


const int Person::getId() const
{
	return this->id;
}

string Person::getName() const
{
	return this->name;
}

bool Person::setName(const string name)
{
	this->name = name;
	return &this->name != nullptr;
}

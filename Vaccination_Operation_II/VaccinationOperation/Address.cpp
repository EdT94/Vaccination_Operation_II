#include "Address.h"
#include <iostream>
using namespace std;

Address::Address(const string& district, const string& street, const int houseNum)
{
	this->district = district;
	this->street = street;
	this->houseNum = houseNum;
}



const string Address::getDistrict() const
{
	return this->district;
}



const string Address::getStreet() const
{
	return this->street;
}



const int Address::getHouseNum() const
{
	return this->houseNum;
}



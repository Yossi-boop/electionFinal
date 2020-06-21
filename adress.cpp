#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "adress.h"
#include <string>

//c'tor
Adress::Adress(const string street, int number, const string city)
{
	setStreet(street);
	setNumber(number);
	setCity(city);
}

const string& Adress::getStreet() const
{
	return street;
}

int Adress::getNumber() const
{
	return number;
}

const string& Adress::getCity() const
{
	return city;
}

bool nameCharForAdress(char c)
//This function check is a given charcter is a letter (big or small) or a space.
//if yes, the function return true, else return false.
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c < 'Z') || (c == ' '));
}

bool validNameCheckForAdress(string str)
//This function returns true if a given string is made of letters and spaces,
//else the function return false.
{
	int i, len = str.length();

	for (i = 0; i < len; i++)
	{
		if (!nameCharForAdress(str[i]))
		{
			return false;
		}
	}

	return true;
}

bool Adress::setStreet(string streetName)
{
	if (!validNameCheckForAdress(streetName)) //If validation check for adress name is false the setter returns false
	{
		cout << "Invalid adress.\n";
		return false;
	}
	else
	{
		street = streetName;
		return true;
	}
}

bool Adress::setNumber(int num)
{
	if (num > 0)
	{
		number = num;
		return true;
	}
	else //The number enterd is not a positive number. A street number must be positive.
	{
		cout << "Street number must be a positive number. Number unchanged\n";
		return false;
	}
}

bool Adress::setCity(string cityName)
{
	if (!validNameCheckForAdress(cityName))
		return false;
	else
	{
		city = cityName;
		return true;
	}
}

const Adress& Adress:: operator=(const Adress& other)
{
	if (this != &other)
	{
		street = other.getStreet();
		city = other.getCity();
		number = other.number;
	}
	return *this;
}

ostream& operator<<(ostream& os, const Adress& adress)
{
	os << adress.street << " " << adress.number << " " << adress.city;
	return os;
}


//No need in d'tor - we don't have dynamic allocation in address class itself

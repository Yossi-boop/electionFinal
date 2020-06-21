#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "citizen.h"

int const VALID_YEAR = 2002; //all citizens in our electios system must be over 18

//C'tor
Citizen::Citizen(const string name, const Date& birthday, int id, int ballotNum, bool isIsolated) throw (string, string) : birthday(std::move(birthday))
{
	if (!setId(id))
		throw "invalid id!";
	if (birthday.getYear() > VALID_YEAR)
		throw "invalid age!";
	setName(name); //We set name - beacuse the throw is before the name set, if have need to throw we will throw (exit the c'tor) and not allocate the name so no need to realse the name
	setBallotNum(ballotNum); //We set ballot number
	setIsIsolated(isIsolated); //We set his isolation status

}

Citizen::Citizen(ifstream& in)
{
	in >> *this;
}

const string& Citizen::getName() const
{
	return name;
}

const Date& Citizen::getBirth() const
{
	return birthday;
}

const int Citizen::getId() const
{
	return id;
}

int Citizen::getBallotNum() const
{
	return ballotNum;
}

bool Citizen::getIsIsolated() const
{
	return isIsolated;
}

bool nameChar(char c)
//This function check is a given charcter is a letter (big or small) or a space.
//if yes, the function return true, else return false.
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c < 'Z') || (c == ' '));
}

bool validNameCheck(string str)
//This function returns true if a given string is made of letters and spaces,
//else the function return false.
{
	int i, len = str.length();

	for (i = 0; i < len; i++)
	{
		if (!nameChar(str[i]))
		{
			return false;
		}
	}

	return true;
}

bool Citizen::setName(const string citizenName)
{
	if (!(validNameCheck(citizenName)))
	{
		cout << "Invalid citizen name\n";
		return false;
	}
	else
	{
		name = citizenName;
		return true;
	}
}

bool Citizen::setBirth(Date citizenBirth)
{
	birthday = citizenBirth;
	return true;
}

/*This function is a helper funtion for "set id".*/
bool checkID(int idNum)
{
	return (idNum >= 100000000 && idNum <= 999999999);
}

bool Citizen::setId(int citizenId) 
{
	if (checkID(citizenId))
	{
		id = citizenId;
		return true;
	}
	else
		return false;

}

bool Citizen::setBallotNum(int bn)
{
	if (bn <= 0)
	{
		cout << "Ballot num must be a positive number. Number unchanged.\n";
		return false;
	}
	else
	{
		ballotNum = bn;
		return true;
	}

}

bool Citizen::setIsIsolated(bool ans)
{
	if (ans != 1 || ans != 0)
	{
		this->isIsolated = ans;
		return true;
	}
	else
		return false;
}

void Citizen::show() const
{
	cout << "Name: " << name << ".\n" << "Date of birth: " << birthday <<
		"." << endl << "ID: " << id << ".\n";
	if (isIsolated)
		cout << "In isolation.\n";
	else
		cout << "Not in isolation.\n";
}

Citizen::~Citizen()
{

}

//No need in d'tor - no dynamic allocations in citizen class itself
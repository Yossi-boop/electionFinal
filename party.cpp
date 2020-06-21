#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "party.h"
using namespace std;


const char* streamStr[] = { "Left", "Right", "Center" };
																			//C'tor
Party::Party(string name, Party::eStream stream, const Date& date) : creationDate(std::move(date))
{
	setName(name);
	setStream(stream);
}

Party::Party(const Party& other) //Copy c'tor
{
	name = other.name;
	theStream = other.theStream;
	creationDate = other.creationDate;
	int size = other.contestants.size();
	for (int i = 0; i < size; ++i)
	{
		contestants += new Contestant(*(other.contestants[i]));
	}
}

const string& Party::getName() const
{
	return name;
}

Party::eStream Party::getStream() const
{
	return theStream;
}

const Date& Party::getCreationDate() const
{
	return creationDate;
}

Array <Contestant*> Party::getContestants() const
{
	return contestants;
}

bool nameCharForParty(char c)
//This function check is a given charcter is a letter (big or small) or a space.
//if yes, the function return true, else return false.
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c < 'Z') || (c == ' '));
}

bool validNameCheckForParty(string str)
//This function returns true if a given string is made of letters and spaces,
//else the function return false.
{
	int i, len = str.length();

	for (i = 0; i < len; i++)
	{
		if (!nameCharForParty(str[i]))
		{
			cout << "Invalid name.\n";
			return false;
		}
	}

	return true;
}

bool Party::setName(string str)
//This function insert the name of the party.
{
	if (!(validNameCheckForParty(str)))//is the name ok?
		return false;//if not return false.
	else//if the name good, insert him, and return true.
	{
		name = str;
		return true;
	}
}

bool Party::setStream(Party::eStream s)
{
	if ((int)s <0 || (int)s >2)
	{
		cout << "You entered invalid stream. Stream unchanged\n";
		return false;
	}
	else
	{
		theStream = s;
		return true;
	}
}

bool Party::setCreationDate(const Date& date)
{
	creationDate = date;
	return true;
}

const Party& Party::operator=(const Party& other)
{
	if (this != &other)
	{
		name = other.name;
		theStream = other.theStream;
		creationDate = other.creationDate;
		contestants = other.contestants;
	}
	return *this;
}

bool Party:: operator>(const Party& other) const
{
	return contestants.size() > other.contestants.size();
}


void Party::addContestant(const Contestant& citizen)
//This function gets a pointer to a citizen and add the citizen to the contestant list.
{
	contestants+= new Contestant(citizen);
}

void Party::show() const
//This function prints the party information.
{
	int i;
	cout << "Party name: " << name << "." << endl;
	cout << "Party stream: " << streamStr[(int)theStream] << "." << endl;
	cout << "Party creation date: " << creationDate << "." << endl;

	if (contestants.size() == 0)
	{
		cout << "The party doesnt have Contestants.\n";
	}
	else
	{

		cout << "Contestants: \n-------------\n";

		for (i = 0; i < contestants.size(); i++)//print each contestant.
		{
			cout << i + 1 << ")";
			contestants[i]->show();
			cout << endl;
		}
	}
}

Party::~Party()
//This function deallocate the used memory.
{
	int cSize = contestants.size();
	for(int i=0; i<cSize; i++)
		delete contestants[i];//delete pointers.	
}
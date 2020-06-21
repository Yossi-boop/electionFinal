#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;
#include "contestant.h"

//C'tor
Contestant::Contestant(const string partyName, const string name, const Date& birthday, int id, int ballotNum, bool isIsolated) : Citizen(name, birthday, id, ballotNum, isIsolated)
{
	this->partyName = partyName;
};

Contestant::Contestant(ifstream& in) : Citizen(in)
{
	in.ignore();
	getline(in, partyName);
}

const string& Contestant::getPartyName() const
{
	return partyName;
}

bool Contestant::setPartyName(string partyName)
{
	this->partyName = partyName;
	return true;
}

void Contestant::show() const
{
	Citizen::show();
	cout << "Party: " << partyName << "." << endl;
}

//No need it d'tor - no actuall dynamic cast inside the class itself
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include "soldier.h"

//C'tor
Soldier::Soldier(const string unitName, const string name, const Date& birthday, int id, int ballotNum, bool isIsolated) : Citizen(name, birthday, id, ballotNum, isIsolated)
{
	this->unitName = unitName;
};

Soldier::Soldier(ifstream& in) : Citizen(in)
{
	in.ignore();
	getline(in, unitName);
}

const string& Soldier::getUnitName() const
{
	return unitName;
}

bool Soldier::setUnitName(const string unitName)
{

	this->unitName = unitName;
	return true;
}

void Soldier::show() const
{
	Citizen::show();
	cout << "Unit name: " << this->unitName << "." << endl;
}

//No need in d'tor - no dynamic allocation are specified in this class
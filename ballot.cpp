#include <iostream>
using namespace std;

#include "ballot.h"

const char* typeStr[] = { "Regular", "Corona", "Military", "MilitaryCoron" };

int Ballot::counter = 0;

Ballot::Ballot(const Adress& location, Ballot::eType type) : location(std::move(location)) //C'tor
{
	votingPercentage = 0;
	serialNum = ++counter;
	setType(type);
}

int Ballot::getSerialNum() const
{
	return serialNum;
}

int Ballot::getNumOfVotes() const
{
	return numOfVotes;
}

int Ballot::getNumOfVoters() const
{
	return voters.size();
}

Adress Ballot::getLocation() const
{
	return location;
}

vector <Citizen*> Ballot::getValidVoters() const
{
	return voters;
}

double Ballot::getVotingPercentage() const
{
	return votingPercentage;
}

vector <PartyVotes*> Ballot::getPartyList() const
{
	return partyList;
}

int Ballot::getCounter() const
{
	return counter;
}

Ballot::eType Ballot::getType() const
{
	return this->ballotType;
}

bool Ballot::setSerialNum(int s)
{
	if (s <= 0)
	{
		cout << "The serial number must be a positive number. Number unchanged.\n";
		return false;
	}
	else
	{
		serialNum = s;
		return true;
	}
}

bool Ballot::setType(Ballot::eType t)
{
	if ((int)t < 0 || (int)t > 3)
	{
		cout << "You entered invalid type. Ballot type unchanged\n";
		return false;
	}
	else
	{
		ballotType = t;
		return true;
	}
}

bool Ballot::setLocation(Adress l)
{
	location = l;
	return true;
}

bool Ballot::setNumOfVotes(int nv)
{
	numOfVotes = nv;
	return true;
}

bool Ballot::setVotingPercentage(int votersWhoVoted, int totalVoters)
{
	if (totalVoters == 0)
	{
		votingPercentage = 0;
		return false;
	}
	else
	{
		votingPercentage = ((double)votersWhoVoted / (double)totalVoters) * 100;
		return true;
	}
}

void Ballot::addVoter(Citizen& c)
{
	if (voters.size() == voters.capacity()) //If the size of the vector equals to the vector capacity - we increase capcity by 2
		voters.reserve(voters.capacity() * 2);

	Contestant* tempCont = dynamic_cast<Contestant*>(&c);
	if (!tempCont)
	{
		Soldier* tempSold = dynamic_cast<Soldier*>(&c);
		if (!tempSold)
		{
			voters.push_back(new Citizen(c));
		}
		else
		{
			voters.push_back(new Soldier(*tempSold));
		}
	}
	else
		voters.push_back(new Contestant(*tempCont));
}

void Ballot::addParty(const Party& p)//from party to partyVotes
{
	if (partyList.size() == partyList.capacity()) //If the size of the vector equals to the vector capacity - we increase capcity by 2
		partyList.reserve(partyList.capacity() * 2);
	partyList.push_back(new PartyVotes(p));
}

void Ballot::addVoteToParty(int index)
{
	int currVotes;
	currVotes = partyList[index]->getNumOfVoters();
	partyList[index]->setNumVotes(currVotes + 1);

}

void Ballot::show() const
{
	cout << "-------------\n";
	cout << "Ballot # " << serialNum << endl;
	cout << "-------------\n";

	cout << "Ballot type: " << typeStr[(int)ballotType] << '.' << endl
		<< location << '.' << endl;

	if (voters.size() == 0)
	{
		cout << "No citizens are allowed to vote in this ballot at the moment.\n";
	}
	else
	{
		int vListSize = voters.size();
		cout << "The citizens who are allowed to vote in this ballot are:" << endl;
		for (int i = 0; i < vListSize; i++)
		{
			cout << i + 1 << ')';
			voters[i]->show();
		}
	}

	cout << "Ballot voting percentage is: " << votingPercentage << '%' << endl;

	int pListSize = partyList.size();
	cout << "The voting results are:" << endl;
	for (int i = 0; i < pListSize; i++)
	{
		cout << *(partyList[i]) << '.' << endl;
	}
}

Ballot::~Ballot()
{
	int i;
	int cSize = voters.size();
	int pSize = partyList.size();

	//We delete all the pointers in the arrays (pointer doesn't free automaticlly in STL)
	for (int i = 0; i < cSize; i++)
		delete voters[i]; 
	for (int i = 0; i < pSize; i++)
		delete partyList[i];
}
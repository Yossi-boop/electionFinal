#include <iostream>
#include "partyvotes.h"

using namespace std;

//C'tor
PartyVotes::PartyVotes(const Party& party) : party(party)
{
	numOfVotes = 0;
}

const Party& PartyVotes::getParty() const
{
	return party;
}

int PartyVotes::getNumOfVoters() const
{
	return numOfVotes;
}

bool PartyVotes::setParty(Party& party)
{
	this->party = party;
	return true;
}


bool  PartyVotes::setNumVotes(int num)
{
	this->numOfVotes = num;
	return true;
}


ostream& operator<<(ostream& os, const PartyVotes& partyVotes)
{
	os << "Party Name: " << partyVotes.party.getName() << " ";
	os << "Number of votes: " << partyVotes.numOfVotes;
	return os;
}
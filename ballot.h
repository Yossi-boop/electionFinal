#ifndef __BALLOT
#define __BALLOT

#include <vector>
#include "contestant.h"
#include "soldier.h"
#include "adress.h"
#include "partyvotes.h"

class Ballot
{
public:
	enum class eType { Regular, Corona, Military, MilitaryCorona };

protected:
	static int counter; //Static counter, gives serial number to each ballot
	int numOfVotes = 0;
	double votingPercentage = 0;
	int serialNum;
	eType ballotType;
	Adress location;
	vector <Citizen*> voters;
	vector <PartyVotes*> partyList;

public:
	Ballot(const Adress& location, Ballot::eType type); //C'tor

	//Get methods
	int getSerialNum() const;
	int getNumOfVotes() const;
	int getNumOfVoters() const;
	Adress getLocation() const;
	double getVotingPercentage() const;
	vector <Citizen*> getValidVoters() const;
	vector <PartyVotes*> getPartyList() const;
	int getCounter() const;
	eType getType() const;

	//Add methods
	void addVoter(Citizen& c);
	void addParty(const Party& p);
	void addVoteToParty(int index);

	//Set Methods
	bool setSerialNum(int s);
	bool setLocation(Adress l);
	bool setNumOfVotes(int nv);
	bool setVotingPercentage(int votersWhoVoted, int totalVoters);
	bool setType(Ballot::eType t);

	void show() const;

	~Ballot(); //D'tor
};

#endif // !__BALLOT
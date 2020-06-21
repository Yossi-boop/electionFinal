
#ifndef __ELECTIONROUND
#define __ELECTIONROUND

#include "ballot.h"

class ElectionRound
{
private:
	Date electionDate;
	vector <Citizen*> citizenNote;
	vector <Party*> partyList;
	vector <Ballot*> ballotList;

public:
	ElectionRound(const Date& date); //C'tor (No need in a default c'tor at this point - we only define one election round the whole program an we initialize it when defining it)

	//get methods
	Date getElecationDate() const;
	vector <Citizen*> getCitizenNote() const;
	int getPLogSize() const;
	vector <Party*> getPartyList() const;
	vector <Ballot*> getBallotList() const;

	//Set methods
	bool setElectionDate(const Date& date);
	bool setCitizenNote(vector <Citizen*> vv);
	bool setPartyList(vector <Party*> p);
	bool setBallotList(vector <Ballot*> b);

	void electionDay();

	//Add methods
	void addNewBallot(const Ballot& ballot);
	bool addNewParty(const Party& party);

	//Show methods
	void showRelevantBallots(int age, bool isIsolated);
	void showBallots() const;
	void showCitizens() const;
	void showParties() const;
	void showElectionResults() const;

	int findParty(vector <Party*> allParties, int size, string partyName);
	bool isValidBallot(int age, bool isIsolted, int ballotNum);

	const ElectionRound& operator+=(Citizen& citizen);

	~ElectionRound(); //D'tor
};

#endif // !__ELECTIONROUND
#include <iostream>
using namespace std;

#include <string>
#include <string.h>
#include "electionround.h"

int const MAX_LEN = 100;
int const PARTY_NOT_FOUND = -1;

//C'tor
ElectionRound::ElectionRound(const Date& date) : electionDate(date)
{
}

Date ElectionRound::getElecationDate() const
{
	return electionDate;
}

vector <Citizen*> ElectionRound::getCitizenNote() const
{
	return citizenNote;
}

int ElectionRound::getPLogSize() const
{
	return partyList.size();
}

vector <Party*> ElectionRound::getPartyList() const
{
	return partyList;
}

vector <Ballot*> ElectionRound::getBallotList() const
{
	return ballotList;
}

bool ElectionRound::setElectionDate(const Date& date)
{
	electionDate = date;
	return true;
}

bool ElectionRound::setCitizenNote(vector <Citizen*> vv)
{
	if (vv.empty())
	{
		cout << "The array doesnt exist. The cuurent array unchanged.\n";
		return false;
	}
	else
	{
		int cListSize = citizenNote.size();
		for (int i = 0; i < cListSize; i++) //We free the old citizen note
			delete citizenNote[i];
		citizenNote = vv;
		return true;
	}
}

bool ElectionRound::setPartyList(vector <Party*> p)
{
	if (p.empty())
	{
		cout << "The array doesnt exist. The cuurent array unchanged.\n";
		return false;
	}
	else
	{
		partyList = p;
		return true;
	}
}

bool ElectionRound::setBallotList(vector <Ballot*> b)
{
	if (b.empty())
	{
		cout << "The array doesnt exist. The cuurent array unchanged.\n";
		return false;
	}
	else
	{
		ballotList = b;
		return true;
	}
}

void ElectionRound::addNewBallot(const Ballot& ballot)
//This function gets a ballot from user, and insert the ballot into the ballot list(array at the moment).
{

	if (ballotList.size() == ballotList.capacity()) //If the size of the vector equals to the vector capacity - we increase capcity by 2
		ballotList.reserve(ballotList.capacity() * 2);
	
	ballotList.push_back(new Ballot(ballot));
	int pListSize = partyList.size(), bListSize = ballotList.size();

	for (int i = 0; i < pListSize; i++)//making the party list for the new ballot.
		ballotList[bListSize-1]->addParty(*(partyList[i]));
}

bool checkIfIdExists(int id, vector <Citizen*> allCitizens, int size)
//This function checks if a given id is already exist in the system.
{
	for (int i = 0; i < size; i++)
	{
		if (allCitizens[i]->getId() == id)
		{
			return true;
		}
	}
	return false;
}

int ElectionRound::findParty(vector <Party*> allParties, int size, string partyName)
//This function seach for a party according to a given party name,
//if the party doesnt exist, the function return -1.
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (partyName == allParties[i]->getName())
		{
			return i;
		}
	}
	return PARTY_NOT_FOUND; //didn't find the party that matches the name user enterd
}

bool ElectionRound::addNewParty(const Party& party)
//This function gets a new party, and add her to the party list(now array).
{
	if (findParty(partyList, partyList.size(), party.getName()) != PARTY_NOT_FOUND) //if the party is alreadt on the list exist
	{
		cout << "\nThe party you entered alreay exist.\nThe party wasn't added to the parties list\n";
		return false;
	}
	else //if the party isnt in the system: 
	{
		if (partyList.size() == partyList.capacity()) //If the size of the vector equals to the vector capacity - we increase capcity by 2
			partyList.reserve(partyList.capacity() * 2);

		int i;
		int bListSize = ballotList.size();
		for (i = 0; i < bListSize; i++) //We add the new party to all of the ballots
			ballotList[i]->addParty(party);

		partyList.push_back(new Party(party));//placement
		return true;
	}

}

void ElectionRound::electionDay()
//This function recieve all the votes from the citizens.
{
	char answer;
	char partyName[MAX_LEN];
	bool canVote = true;
	int cListSize = citizenNote.size(), pListSize = partyList.size();
	for (int i = 0; i < cListSize; i++)//for each citizen:
	{
		canVote = true;
		cout << "Hello " << citizenNote[i]->getName() << "." << " Do you want to vote? Please enter y/n:" << endl;
		cin >> answer;
		if (answer == 'y')//want to vote
		{
			if (citizenNote[i]->getIsIsolated() == true) //We check if the person is qualified to vote (if he is isolated than if he wear valid cloths)
			{
				answer = '0'; //We restart answer in order to re-use the vraiable
				do {
					cout << "You are in isolation. Do you have proper wear?\n";
					cin >> answer;
				} while (answer != 'y' && answer != 'n');

				if (answer == 'n')
				{
					cout << "You must wear proper cloth inorder to vote\n";
					canVote = false; //We flag that this person can vote and we move to the next person
				}
			}

			if (canVote) {
				//If you got to this point it means the person is valid to vote - we take his vote
				int j = 0, k = 0, cBallotNum = citizenNote[i]->getBallotNum();

				do {//enter the party name, if worng or doesnt exist, enter again.
					cout << "Please enter the party name: <Party name must be a name of a party who exists>\n"; //to what party
					if (j != PARTY_NOT_FOUND)
					{
						cin.ignore();
					}
					cin.getline(partyName, MAX_LEN);
					j = findParty(partyList, pListSize, partyName);//party exist?
				} while (j == PARTY_NOT_FOUND);

				while (ballotList[k]->getSerialNum() != cBallotNum) //We keep the index of the right ballot 
				{
					k++;
				}

				ballotList[k]->addVoteToParty(j);//add the vote to the party in the correct ballot.
				ballotList[k]->setNumOfVotes(ballotList[k]->getNumOfVotes() + 1);
				ballotList[k]->setVotingPercentage(ballotList[k]->getNumOfVotes(), ballotList[k]->getNumOfVoters());
			}
		}

	}
}

//This function checks if citizen choose a valid ballot number
bool ElectionRound::isValidBallot(int age, bool isIsolted, int ballotNum)
{
	int ballotType;
	int bListSize = ballotList.size();
	if (isIsolted == true && 18 <= age && age <= 21) //Citizens who should be assigned to a corona-military ballot
		ballotType = 3;
	else if (18 <= age && age <= 21) //Citizens who should be assigned to military ballot
		ballotType = 2;
	else if (isIsolted == true) //Citizens who should be assigned to a corona ballot
		ballotType = 1;
	else //The citizen have no special attributes - he should be assigned to a regular ballot
		ballotType = 0;

	for (int i = 0; i < bListSize; i++) //We loop over all the ballots and search for ballots who match the type of ballot the citizen can be assigned to
	{
		if (ballotList[i]->getType() == (Ballot::eType)ballotType
			&& ballotList[i]->getSerialNum() == ballotNum)
			return true;
	}
	return false; //We got to the end of the loop and the ballot type of the new citizen didn't match a ballot of the relevant type
}

int calcAgeForBallot(Date electionDate, Date birthdate)
{
	// days of every month 
	int month[] = { 31, 28, 31, 30, 31, 30, 31,	31, 30, 31, 30, 31 };
	int currDay = electionDate.getDay();
	int currMonth = electionDate.getMonth();
	int currYear = electionDate.getYear();

	// if birth date is greater then current birth 
	// month then do not count this month and add 30  
	// to the date so as to subtract the date and 
	// get the remaining days 
	if (birthdate.getDay() > currDay) {
		currDay = currDay + month[birthdate.getDay() - 1];
		currMonth -= 1;
	}

	// if birth month exceeds current month, then do 
	// not count this year and add 12 to the month so 
	// that we can subtract and find out the difference 
	if (birthdate.getMonth() > currMonth) {
		currYear -= 1;
	}

	return currYear - birthdate.getYear(); //We return the age (in years) of the citizen
}

int calcBallot(Citizen citizen, Date date)
{
	int age = calcAgeForBallot(date, citizen.getBirth());
	if (age > 18 && age < 21)
	{
		if (citizen.getIsIsolated())
		{
			return 3;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		if (citizen.getIsIsolated())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

const ElectionRound& ElectionRound:: operator+=(Citizen& citizen)
{
	if (checkIfIdExists(citizen.getId(), citizenNote, citizenNote.size())) //If the id of the new citizen already exists in the system return false
	{
		cout << "\nThe Id num you entered for the citizen alreay exist.\nThe citizen wasn't added to the voters note.\n";
		return *this;
	}

	//Add citizen to the citizen list

	if (citizenNote.size() == citizenNote.capacity())
	{//If the size of the vector equals to the vector capacity - we increase capcity by 2
		citizenNote.reserve(citizenNote.capacity() * 2);
	}

	Contestant* tempCont = dynamic_cast<Contestant*>(&citizen);
	if (!tempCont) //If he is not a contestant we check if he is a citizen of a soldier
	{
		Soldier* tempSold = dynamic_cast<Soldier*>(&citizen);
		if (!tempSold) //if he is not a soldier, we add him as regular citizen
			citizenNote.push_back(new Citizen(citizen));//placement
		else //he is a soldier - we add him as soldier
			citizenNote.push_back(new Soldier(*tempSold));
	}
	else // he is a contestant - we add him as a contestant
	{
		//citizenNote.push_back(new Contestant(*tempCont));//placement
		int index;
		int pListSize = partyList.size();
		for (index = 0; index < pListSize; index++)
		{
			if (partyList[index]->getName() == tempCont->getPartyName())
			{//if the party name exist
				partyList[index]->addContestant(*tempCont);//add the contestant to the right party.
				break;//break the loop.
			}
		}
		if (index == pListSize)//if the name isnt in the party list.
		{
			tempCont->setPartyName("Halikud");//enter the contestant to the deafualt party Halikud.
			partyList[0]->addContestant(*tempCont);
		}
		citizenNote.push_back(new Contestant(*tempCont));//placement
	}

	int serialNum = citizen.getBallotNum();//get the ballot of the citizen.
	int bListSize = ballotList.size(), i, goodBallot,
		ballotType = calcBallot(citizen, electionDate);
	for (i = 0; i < bListSize; i++)
	{
		if (serialNum == ballotList[i]->getSerialNum())
		{
			ballotList[i]->addVoter(citizen);//add the citizen to the correct ballot.
			break; //We found the right ballot. No need to keep search
		}
		if ((int)ballotList[i]->getType() == ballotType)
		{
			goodBallot = i;
		}
	}
	if (i == bListSize)//if the ballot isnt found.
	{
		citizenNote[citizenNote.size() - 1]->setBallotNum(goodBallot);//change to a ballot with the same type.
		ballotList[goodBallot]->addVoter(*(citizenNote[citizenNote.size() - 1]));//add the voter.
	}
	return *this;
}

//This function prints all relevant ballots for a person
void ElectionRound::showRelevantBallots(int age, bool isIsolated)
{
	int ballotType, bListSize = ballotList.size();

	if (isIsolated == true && (18 <= age && age <= 21)) //Citizens who should be assigned to a corona-military ballot
		ballotType = 3;
	else if (18 <= age && age <= 21) //Citizens who should be assigned to military ballot
		ballotType = 2;
	else if (isIsolated == true) //Citizens who should be assigned to a corona ballot
		ballotType = 1;
	else //The citizen have no special attributes - he should be assigned to a regular ballot
		ballotType = 0;

	for (int i = 0; i < bListSize; i++) //We loop over all the ballots and search for ballots who match the type of ballot the citizen can be assigned to
	{
		if (ballotList[i]->getType() == (Ballot::eType)ballotType)
			cout << ballotList[i]->getSerialNum() << " ";
	}
	cout << endl;
}

void ElectionRound::showElectionResults() const
//This function shows the election day results.
{
	int pListSize = partyList.size(), bListSize = ballotList.size();
	vector <int>  results(partyList.size(), 0);//array of the results.

	cout << "\n\nElections results that took place at " << electionDate.getMonth() << "/" << electionDate.getYear() << ":\n";
	cout << "--------------------------------------------\n";
	for (int i = 0; i < pListSize; i++)//make the results array all zeros.
	{
		results[i] = 0;
	}
	for (int i = 0; i < bListSize; i++)//for each ballot:
	{
		cout << "In ballot #" << ballotList[i]->getSerialNum() << ":" << endl;
		cout << "-------------\n";
		cout << "Voting percentage is: " << ballotList[i]->getVotingPercentage() << endl;//print voting percentage
		for (int j = 0; j < pListSize; j++)//print the number of votes for each party:
		{
			string name = ballotList[i]->getPartyList()[j]->getParty().getName();
			int votes = (ballotList[i]->getPartyList())[j]->getNumOfVoters();
			cout << "Party: " << name << " recieved " << votes << " votes. \n";
			results[j] += votes;//add the number of votes in this ballot, to the total sum of votes.
		}
		cout << endl;
	}
	cout << "\nThe final results are:" << endl;
	cout << "----------------------\n";
	for (int i = 0; i < pListSize; i++)//for each party, prints the final results:
	{
		cout << "Party: " << partyList[i]->getName() << " recieved "
			<< results[i] << " votes." << endl;
	}
}

void ElectionRound::showBallots() const
//This function prints all the ballots.
{
	int bListSize = ballotList.size();
	cout << "The ballots are:" << endl;
	for (int i = 0; i < bListSize; i++)
		ballotList[i]->show();
}

void ElectionRound::showCitizens() const
//This function prints all the citizens.
{
	int cListSize = citizenNote.size();
	cout << "The voters note is:" << endl;
	cout << "-------------------\n";
	for (int i = 0; i < cListSize; i++)
	{
		cout << "Voter #" << i + 1 << " is: " << endl;
		cout << "-----------" << endl;
		citizenNote[i]->show();
		cout << endl;
	}
}

void ElectionRound::showParties() const
//This function prints all the parties.
{
	int pListSize = partyList.size();
	cout << "The parties are:" << endl;
	for (int i = 0; i < pListSize; i++)
	{
		cout << "-----------------\n";
		partyList[i]->show();
	}
}

ElectionRound::~ElectionRound()
//D'tor - This function deallocate all of the used memory
{
	int i;
	//We keep the sizes of all the vectors we have in order to free the pointers 
	//It is more efficient to keep the size than calling the size() function on each iteration
	int cListSize = citizenNote.size(), pListSize = partyList.size(), bListSize = ballotList.size(); 

	for (i = 0 ;i < cListSize; i++)
		delete citizenNote[i]; 
	for (i = 0; i < pListSize; i++)
		delete partyList[i];
	for (i = 0; i < bListSize; i++)
		delete ballotList[i];
}
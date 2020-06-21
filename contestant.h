#ifndef __CONTESTANT
#define __CONTESTANT

#include <fstream>
#include "citizen.h"

class Contestant : virtual public Citizen
{
private:
	string partyName;

public:
	Contestant(const string partyName, const string name, const Date& birthday, int id, int ballotNum, bool isIsolated); //C'tor
	Contestant(ifstream& in); //File c'tor

	const string& getPartyName() const;
	bool setPartyName(string partyName);

	void show() const;

	friend ostream& operator<<(ostream& out, const Contestant& contestant)
	{
		out << contestant.name << '\n' << contestant.birthday << "\n" << contestant.id << "\n"
			<< contestant.ballotNum << '\n' << contestant.isIsolated
			<< '\n' << contestant.partyName << '\n';
		return out;
	}

	friend istream& operator >> (istream& in, Contestant& contestant)
	{
		char delimiter;
		getline(in, contestant.name);
		in >> contestant.birthday >> delimiter >> contestant.id >>
			delimiter >> contestant.ballotNum >> delimiter >>
			contestant.isIsolated;
		getline(in, contestant.partyName);
		return in;
	}

};
#endif // !__CONTESTANT
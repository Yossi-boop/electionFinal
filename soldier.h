#ifndef __SOLDIER
#define __SOLDIER

#include <fstream>
#include "citizen.h"

class Soldier : virtual public Citizen
{
private:
	string unitName;

public:
	Soldier(const string unit, const string name, const Date& birthday, int id, int ballotNum, bool isIsolated); //C'tor
	Soldier(ifstream& in); //File c'tor

	const string& getUnitName() const;
	bool setUnitName(const string unitName);

	void show() const;

	friend ostream& operator<<(ostream& out, const Soldier& soldier)
	{
		out << soldier.name << '\n' << soldier.birthday << "\n" << soldier.id << "\n"
			<< soldier.ballotNum << '\n' << soldier.isIsolated << '\n' <<
			soldier.unitName << '\n';
		return out;
	}

	friend istream& operator >> (istream& in, Soldier& soldier)
	{
		char delimiter;
		in >> delimiter >> soldier.unitName >> soldier.name >> delimiter >> soldier.birthday >> delimiter
			>> soldier.id >> delimiter >> soldier.ballotNum >> delimiter >> soldier.isIsolated >> delimiter;
		return in;
	}
};
#endif // !__CONTESTANT
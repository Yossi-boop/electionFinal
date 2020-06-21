#ifndef __PARTY
#define __PARTY

#include "contestant.h"
#include "array.h"

class Party
{
public:
	enum class eStream { Left, Right, Center };

private:
	string name; //Party name
	eStream theStream;
	Date creationDate;
	Array <Contestant*> contestants;

public:

	Party(string name, Party::eStream stream, const Date& date); //C'tor
	Party(const Party& other); //copy C'tor

						 //Get methods
	const string& getName() const;
	eStream getStream() const;
	const Date& getCreationDate() const;
	Array <Contestant*> getContestants() const;

	//Set methods
	bool setName(string str);
	bool setStream(Party::eStream s);
	bool setCreationDate(const Date& date);

	void addContestant(const Contestant& citizen);

	const Party& operator=(const Party& other);
	bool operator>(const Party& other) const;

	void show() const;

	~Party(); //D'tor

};
#endif // !__PARTY
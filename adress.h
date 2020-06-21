#ifndef __ADRESS
#define __ADRESS

#include <iostream>
using namespace std;

class Adress
{
private:
	string street;
	int number;
	string city;

public:

	Adress(const string name = "Hertzel", int number = 1, const string city = "Tel Aviv"); //C'tor

	//Get methods
	const string& getStreet() const;
	int getNumber() const;
	const string& getCity() const;

	//Set methods
	bool setStreet(string streetName);
	bool setNumber(int num);
	bool setCity(string cityName);

	const Adress& operator=(const Adress& other);
	friend ostream& operator<<(ostream& os, const Adress& adress);

};

#endif // !__ADRESS
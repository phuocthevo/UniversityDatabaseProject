// Data file
// Written by Dan Nguyen
#ifndef UNIVERSITY
#define UNIVERSITY
#include <string>
using namespace std;

class University
{
	friend bool operator ==(const University& a, const University& b) 
	{
		bool rVal = false;
		if (!(a.code.compare(b.code)))
			rVal = true;
		return rVal;
	}
	friend bool operator>(const University& a, const University& b)
	{
		bool rVal = false;
		if ((a.code.compare(b.code)) >0)
			rVal = true;
		return rVal;
	}
	friend bool operator<(const University& a, const University& b)
	{
		bool rVal = false;
		if ((a.code.compare(b.code)) <0)
			rVal = true;
		return rVal;
	}

	friend bool operator !=(const University& a, const University& b)
	{
		bool rVal = false;
		if (!(a.name.compare(b.name)))
			rVal = true;
		return rVal;
	}
	friend bool operator >=(const University& a, const University& b)
	{
		bool rVal = false;
		if ((a.name.compare(b.name)) >0)
			rVal = true;
		return rVal;
	}
	friend bool operator <=(const University& a, const University& b)
	{
		bool rVal = false;
		if ((a.name.compare(b.name)) < 0)
			rVal = true;
		return rVal;
	}


private:
	string code;
	string name;
	string location;
	int tuition;
	string ranking;
	string admission;
public:
	University(){
		code = name = location = admission =ranking= "";
		tuition = 0;

	}
	University(string c){
		code = c;
		name = location = admission = ranking= "";
		tuition = 0;
	}

	University(string c, string n, string l, int t, string r, string a)
	{
		code = c;
		name = n;
		location = l;
		tuition = t;
		ranking = r;
		admission = a;
	}
	string getCode() const { return code; }
	string getName() const { return name; }
	string getLocation() const { return location; }
	string getAdmission() const { return admission; }
	int getTuition() const { return tuition; }
	string getRanking() const { return ranking; }

	void setCode(string c){
		for (int i = 0; i < c.length(); i++)
			c[i] = (char)toupper(c[i]);
		code = c;
	}
	void setName(string n){ name = n; }
	void setLocation(string l){ location = l; }
	void setTuition(int t){ tuition = t; }
	void setRanking(string r){ ranking = r; }
	void setAdmission(string a){ admission = a; }

	University& operator=(const University& r)
	{
		code = r.code;
		name = r.name;
		location = r.location;
		tuition = r.tuition;
		ranking = r.ranking;
		admission = r.admission;
		return *this;
	}

	bool operator % (University& r)
	{
		if (r.getName().find(this->getName()) != std::string::npos)
			return true;
		else
			return false;
	}
	
};

#endif
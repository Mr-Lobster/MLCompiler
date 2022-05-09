#pragma once
#include<iostream>
#include<iomanip>
using namespace std;

class twoTuple {
public:
	string type;
	string value;
	twoTuple(string type = "null", string value = "null") {
		this->type = type;
		this->value = value;
	}

};

ostream& operator<<(ostream& out, const twoTuple& tuple)
{
	out << "(" << setw(10) << tuple.type << "  £¬" << setw(8) << tuple.value << "     )" ;
	return out;
}
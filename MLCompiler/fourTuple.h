#pragma once
#include<iostream>
#include<iomanip>
using namespace std;

class fourTuple {
	
public:
	string symbol;
	string operand1;
	string operand2;
	string result;
	fourTuple(string symbol, string operand1, string operand2, string result) {
		this->symbol = symbol;
		this->operand1 = operand1;
		this->operand2 = operand2;
		this->result = result;
	}

};

/*
static ostream& operator<<(ostream& out, const fourTuple& tuple)
{
	out << "(" << tuple.symbol << "," << tuple.operand1 << "," << tuple.operand2 << "," << tuple.result << "";
	return out;
}*/
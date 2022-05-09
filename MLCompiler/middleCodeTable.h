#pragma once
#include <iostream>
#include <vector>
#include "fourTuple.h"
using namespace std;

//�м���� ��Ԫʽ��
class middleCodeTable
{
public:
	middleCodeTable();
	~middleCodeTable();
	int NXQ();
	vector<fourTuple> table;
	bool add(string, string, string, string);
	bool Backpath(int index, string result);
	void clear();
	void dump();
private:

};

middleCodeTable::middleCodeTable()
{
}

middleCodeTable::~middleCodeTable()
{
}

bool middleCodeTable::add(string symbol, string operand1, string operand2, string result)
{

	this->table.push_back(fourTuple(symbol, operand1, operand2, result));
	return true;

}

int middleCodeTable::NXQ() {
	return this->table.size();
}

bool middleCodeTable::Backpath(int index, string result) {
	if (index < 0 || index > this->table.size() - 1) {
		return false;
	}
	else {
		this->table[index].result = result;
	}
}

void middleCodeTable::clear() {
	this->table.clear();
}

void middleCodeTable::dump() {
	cout << endl << endl;
	cout << "�м������Ԫʽ��:" << endl;

	//ͨ������������
	vector<fourTuple>::iterator iter;
	int index = 0;
	for (iter = table.begin(); iter != table.end(); iter++)
	{
		cout <<"(" << index++ << ")" << " ( " << (*iter).symbol << " , " << (*iter).operand1 << " , " << (*iter).operand2 << " , " << (*iter).result << " )" << endl;
	}
}

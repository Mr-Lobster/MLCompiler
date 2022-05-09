#pragma once
#include <iostream>
#include <string> 
#include<vector>
#include "identifier.h"
using namespace std;

class tempVarTavble {
public:
	vector<string> table;
	identifier getNewTempVar();
	void clear();
	void dump();

};

void tempVarTavble::clear() {
	this->table.clear();
}

void tempVarTavble::dump() {
	cout << endl << endl;
	cout << "临时变量表:" << endl;

	//通过迭代器访问
	vector<string>::iterator iter;
	for (int i = 0; i < table.size(); i++)
	{
		cout << " " << i << ": " << table[i] << endl;
	}
}

identifier tempVarTavble::getNewTempVar() {
	int index = table.size();
	string name = "T" + to_string(index);
	//我认为临时变量的名称要+1
	table.push_back(name);
	return identifier(name);
}
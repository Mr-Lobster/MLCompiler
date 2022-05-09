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
	cout << "��ʱ������:" << endl;

	//ͨ������������
	vector<string>::iterator iter;
	for (int i = 0; i < table.size(); i++)
	{
		cout << " " << i << ": " << table[i] << endl;
	}
}

identifier tempVarTavble::getNewTempVar() {
	int index = table.size();
	string name = "T" + to_string(index);
	//����Ϊ��ʱ����������Ҫ+1
	table.push_back(name);
	return identifier(name);
}
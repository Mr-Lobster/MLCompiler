#pragma once
#include "identifier.h"
#include <string>
#include <vector>

class identifierTable
{
private:
	/* data */
	//bool mycomp(const identifier i, const string j)
	//{
	//    return i.name == j;
	//}

public:
	vector<identifier> table;
	bool existIdentifier(string name);
	bool add(string name);
	bool updateIdentifierTypeByName(string, string);
	bool updateIdentifierValueByName(string, string);
	int getIdentifierIndexByName(string);
	string getIdentifierValueByName(string);
	int getIdentifierValueByNameAsInt(string);
	double getIdentifierValueByNameAsDouble(string);
	void clear();
	string dump();
};

bool identifierTable::existIdentifier(string name)
{
	//bool flag = binary_search(table.begin(), table.end(), name, mycomp);
	//if (flag != 0)
	//{
	//    return true;
	//}
	//else
	//{
	//    return false;
	//}
	//通过迭代器访问
	vector<identifier>::iterator iter;
	for (iter = table.begin(); iter != table.end(); iter++)
	{
		if ((*iter).name == name)
		{
			return true;
		}

	}
	return false;
}

bool identifierTable::add(string name)
{
	if (existIdentifier(name))
		return false;
	else
	{
		this->table.push_back(identifier(name));
		return true;
	}
}

void identifierTable::clear() {
	table.clear();
}

string identifierTable::dump() {
	cout << endl << endl;
	cout << "标识符表:" << endl;
	string output = "";
	//通过迭代器访问
	vector<identifier>::iterator iter;
	for (iter = table.begin(); iter != table.end(); iter++)
	{
		output += "( " + (*iter).name + " , " + (*iter).type + " , " + (*iter).value + " )";
		output += "\n";
	}
	return output;
}

//更新标识符类型
bool identifierTable::updateIdentifierTypeByName(string name, string type) {
	if (this->existIdentifier(name) == false) {
		return false;
	}

	//开始更新
	//通过迭代器访问
	vector<identifier>::iterator iter;
	for (iter = table.begin(); iter != table.end(); iter++)
	{
		if ((*iter).name == name)
		{
			(*iter).type = type;
			return true;
		}
	}
}

//更新标识符的值
bool identifierTable::updateIdentifierValueByName(string name, string value) {
	if (this->existIdentifier(name) == false) {
		return false;
	}

	//开始更新
	//通过迭代器访问
	vector<identifier>::iterator iter;
	for (iter = table.begin(); iter != table.end(); iter++)
	{
		if ((*iter).name == name)
		{
			(*iter).value = value;
			return true;
		}
	}
}

//返回标识符的下标 没找到的化返回-1
int identifierTable::getIdentifierIndexByName(string name) {
	if (this->existIdentifier(name) == false) {
		return -1;
	}
	//开始查询
	for (int i = 0; i < table.size(); i++) {
		if (table[i].name == name) {
			return i;
		}
	}
}

//根据名称返回标识符的值 string
string identifierTable::getIdentifierValueByName(string name) {
	if (this->existIdentifier(name) == false) {
		return "Error : indentifier does not exist .";
	}
	//开始查询
	for (int i = 0; i < table.size(); i++) {
		if (table[i].name == name) {
			return table[i].value;
		}
	}
}


//根据名称返回标识符的值 int
int identifierTable::getIdentifierValueByNameAsInt(string name) {
	if (this->existIdentifier(name) == false) {
		return -1;
	}
	if (this->getIdentifierValueByName(name) == "") {
		return -1;
	}
	return atoi(this->getIdentifierValueByName(name).c_str());
}

//根据名称返回标识符的值 double
double identifierTable::getIdentifierValueByNameAsDouble(string name) {
	if (this->existIdentifier(name) == false) {
		return -1;
	}
	if (this->getIdentifierValueByName(name) == "") {
		return -1;
	}
	return stod(this->getIdentifierValueByName(name));
}
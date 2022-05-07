#pragma once
#include "identifier.h"
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
	string output = "";
	//通过迭代器访问
	vector<identifier>::iterator iter;
	for (iter = table.begin(); iter != table.end(); iter++)
	{
		output += (*iter).name + (*iter).type + (*iter).value;
		output += " ";
	}
	return output;
}
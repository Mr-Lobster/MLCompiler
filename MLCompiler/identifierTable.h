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
	//ͨ������������
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
	cout << "��ʶ����:" << endl;
	string output = "";
	//ͨ������������
	vector<identifier>::iterator iter;
	for (iter = table.begin(); iter != table.end(); iter++)
	{
		output += "( " + (*iter).name + " , " + (*iter).type + " , " + (*iter).value + " )";
		output += "\n";
	}
	return output;
}

//���±�ʶ������
bool identifierTable::updateIdentifierTypeByName(string name, string type) {
	if (this->existIdentifier(name) == false) {
		return false;
	}

	//��ʼ����
	//ͨ������������
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

//���±�ʶ����ֵ
bool identifierTable::updateIdentifierValueByName(string name, string value) {
	if (this->existIdentifier(name) == false) {
		return false;
	}

	//��ʼ����
	//ͨ������������
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

//���ر�ʶ�����±� û�ҵ��Ļ�����-1
int identifierTable::getIdentifierIndexByName(string name) {
	if (this->existIdentifier(name) == false) {
		return -1;
	}
	//��ʼ��ѯ
	for (int i = 0; i < table.size(); i++) {
		if (table[i].name == name) {
			return i;
		}
	}
}

//�������Ʒ��ر�ʶ����ֵ string
string identifierTable::getIdentifierValueByName(string name) {
	if (this->existIdentifier(name) == false) {
		return "Error : indentifier does not exist .";
	}
	//��ʼ��ѯ
	for (int i = 0; i < table.size(); i++) {
		if (table[i].name == name) {
			return table[i].value;
		}
	}
}


//�������Ʒ��ر�ʶ����ֵ int
int identifierTable::getIdentifierValueByNameAsInt(string name) {
	if (this->existIdentifier(name) == false) {
		return -1;
	}
	if (this->getIdentifierValueByName(name) == "") {
		return -1;
	}
	return atoi(this->getIdentifierValueByName(name).c_str());
}

//�������Ʒ��ر�ʶ����ֵ double
double identifierTable::getIdentifierValueByNameAsDouble(string name) {
	if (this->existIdentifier(name) == false) {
		return -1;
	}
	if (this->getIdentifierValueByName(name) == "") {
		return -1;
	}
	return stod(this->getIdentifierValueByName(name));
}
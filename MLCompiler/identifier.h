#pragma once
#include <iostream>
using namespace std;

class identifier
{
private:
	/* data */
public:
	identifier(string name, string type, string value);
	~identifier();
	string name;//用于存放变量（标识符）的名字
	string type;//用于存放变量的类型（int double等）
	string value; //用于存放变量的值
};

identifier::identifier(string name, string type = "int", string value = "")
{
	this->name = name;
	this->type = type;
	this->value = value;
}

identifier::~identifier()
{
}

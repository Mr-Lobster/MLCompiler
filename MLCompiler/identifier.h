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
	string name;//���ڴ�ű�������ʶ����������
	string type;//���ڴ�ű��������ͣ�int double�ȣ�
	string value; //���ڴ�ű�����ֵ
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

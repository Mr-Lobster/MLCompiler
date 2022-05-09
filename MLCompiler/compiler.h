#pragma once
#include  <iostream>
#include  "dfa.h"
#include "middleCodeTable.h"
#include "tempVarTable.h"
using namespace std;

class Compiler {
private:
	DFA dfa;//�ʷ�����DFA
	twoTuple word;//���ڱ���ÿ�δʷ���������Ķ�Ԫʽ
	twoTuple nextInput();//��ȡ��һ���ʷ���������Ķ�Ԫʽ
	middleCodeTable codetable;//�м����� ��Ԫʽ
	tempVarTavble tempvartable;//��ʱ������ ���ڱ��� + * ����Ľ��
	bool match(string);
	bool parseProgram();
	bool parseExplainVars();
	bool parseIdentifierList(string);
	bool parseIdentifierListPrime(string);
	bool parseStatementSection();
	bool parseStatementSectionPrime();
	bool parseStatement();
	bool parseAssignStatement();
	bool parseIfStatement();
	bool parseLoopStatement();
	identifier parseCondition();
	identifier parseExpression();
	identifier parseExpressionPrime(identifier);
	identifier parseItem();
	identifier parseItemPrime(identifier);
	identifier parseElement();
	bool parseCompoundStatement();
	bool parseNestStatement();
	string myPlus(string, string);
	string myMult(string, string);
public:
	Compiler(string);
	void run();
};



Compiler::Compiler(string inputFile) :dfa(inputFile) {

}

twoTuple Compiler::nextInput() {
	return dfa.runOnce();
}

bool Compiler::match(string type) {
	if (type != word.type) {
		cout << endl << endl;
		cout << "Error!" << endl;
		cout << "ƥ��ʧ��! " << word.type << " != " << type << endl;
		cout << "Error!" << endl;
		cout << endl << endl;
		return false;
	}
	else {
		//ƥ��ɹ�
		cout << "-> ƥ��ɹ�: " << word << endl;
		word = this->nextInput();
		cout << "-> ʶ�𵥴�: " << word << endl;
		return true;
	}
}

void Compiler::run() {
	cout << "�ʷ�������ʼ" << endl;
	word = this->nextInput();
	cout << "-> ʶ�𵥴�: " << word << endl;
	this->parseProgram();
	cout << this->dfa.iTable.dump();
	this->codetable.dump();
	this->tempvartable.dump();
}

bool Compiler::parseProgram() {
	cout << "�Ƶ�: <����> ��<����˵������>;<��䲿��>" << endl;
	this->parseExplainVars();
	this->match("�ֺ�");
	this->parseStatementSection();
	cout << "�﷨��������" << endl;
	return true;
}

bool Compiler::parseExplainVars() {
	cout << "�Ƶ�: <����˵������> �� <����˵��><��ʶ���б�>" << endl;
	match("int");
	this->parseIdentifierList("int");//�ѱ������ʹ��ݸ� ��ʶ���б�
	return true;
}

bool Compiler::parseIdentifierList(string type) {
	cout << "�Ƶ�: <��ʶ���б�> �� <��ʶ��><��ʶ���б�Prime>" << endl;
	if (word.type == "��ʶ��") {
		dfa.iTable.updateIdentifierTypeByName(word.value, "int");//���±��������� word Ϊ�ʷ���������Ķ�Ԫʽ word.value Ϊ��������
		cout << "Update ���±�ʶ��: " << word.value << " ������Ϊ int" << endl;
		this->match("��ʶ��");
	}
	this->parseIdentifierListPrime(type);
	return true;
}

bool Compiler::parseIdentifierListPrime(string type) {
	cout << "�Ƶ�: <��ʶ���б�Prime> ��,<��ʶ��><��ʶ���б�Prime>|e" << endl;
	if (word.type == "����") {
		this->match("����");
		if (word.type == "��ʶ��") {
			dfa.iTable.updateIdentifierTypeByName(word.value, "int");
			cout << "Update ���±�ʶ��: " << word.value << " ������Ϊ int" << endl;
			this->match("��ʶ��");
		}
		parseIdentifierListPrime(type);
	}
	else {
	}

	return true;
}

bool Compiler::parseStatementSection() {
	cout << "�Ƶ�: <��䲿��> ��<���>;<��䲿��Prime>" << endl;
	parseStatement();
	match("�ֺ�");
	parseStatementSectionPrime();
	return true;
}

bool Compiler::parseStatementSectionPrime() {
	cout << "�Ƶ�: <��䲿��Prime> ��<���>;<��䲿��Prime>|e" << endl;
	if (word.type == "��ʶ��" || word.type == "if" || word.type == "while")
	{
		parseStatement();
		match("�ֺ�");
		parseStatementSectionPrime();
	}
	else {

	}
	return true;
}

bool Compiler::parseStatement() {
	cout << "�Ƶ�: <���> ��<��ֵ���>|<�������>|<ѭ�����>" << endl;
	if (word.type == "��ʶ��") {
		parseAssignStatement();
	}
	if (word.type == "if") {
		parseIfStatement();
	}
	if (word.type == "while") {
		parseLoopStatement();
	}
	return true;
}

bool Compiler::parseAssignStatement() {
	cout << "�Ƶ�: <��ֵ���> ��<��ʶ��>=<���ʽ>" << endl;
	string identifiername;
	if (word.type == "��ʶ��") {
		identifiername = word.value;//�����ʶ��������
		match("��ʶ��");
	}

	match("��ֵ��");
	identifier E = parseExpression();//����һ�����������ձ��ʽ��ֵ
	codetable.add("=", E.name, "null", identifiername);
	cout << "������ֵ��Ԫʽ" << endl;
	//���±�ʶ����ֵ
	dfa.iTable.updateIdentifierValueByName(identifiername, E.value);
	//cout << endl << endl << E.name<<"  "<< E.value << endl << endl;
	return true;
}

bool Compiler::parseIfStatement() {
	cout << "�Ƶ�: <�������> �� if ��<����>�� then <Ƕ�����>; else <Ƕ�����>" << endl;
	match("if");
	match("������");
	identifier E = parseCondition();
	match("������");
	match("then");
	codetable.add("jnz", E.name, "null", to_string(codetable.NXQ() + 2));
	int falseExitIndex = codetable.NXQ();
	codetable.add("j", "null", "null", "0");//��Ҫ����

	parseNestStatement();
	int exitIndex = codetable.NXQ();
	codetable.add("j", "null", "null", "0");//��Ҫ����
	codetable.Backpath(falseExitIndex, to_string(codetable.NXQ()));
	match("�ֺ�");
	match("else");
	parseNestStatement();
	codetable.Backpath(exitIndex, to_string(codetable.NXQ()));
	return true;
}

bool Compiler::parseLoopStatement() {
	cout << "�Ƶ�: <ѭ�����> �� while ��<����>�� do <Ƕ�����>" << endl;
	match("while");
	match("������");
	int initIndex = codetable.NXQ();//����������������Ԫʽindex
	identifier E = parseCondition();//��ȡ�������ص���ʱ����
	match("������");
	match("do");
	codetable.add("jnz", E.name, "null", to_string(codetable.NXQ() + 2));
	int falseExitIndex = codetable.NXQ();
	codetable.add("j", "null", "null", "null");//�ȴ�����ٳ���
	parseNestStatement();
	codetable.add("j", "null", "null", to_string(initIndex));
	//��ʼ����
	codetable.Backpath(falseExitIndex, to_string(codetable.NXQ()));
	return true;
}

identifier Compiler::parseCondition() {
	cout << "�Ƶ�: <����> �� <���ʽ><��ϵ�����><���ʽ>" << endl;
	identifier E1 = parseExpression();

	string logicOperator = "";
	if (word.type == "��ϵ�����") {
		logicOperator = word.value;
		match("��ϵ�����");
	}

	identifier E2 = parseExpression();

	//�����м����
	identifier T = tempvartable.getNewTempVar();
	codetable.add(logicOperator, E1.name, E2.name, T.name);
	cout << "�����߼�������Ԫʽ" << endl;
	//��ʼ����T��ֵ
	T.type = "bool";
	bool flag = false;//������������true
	double value1 = dfa.iTable.getIdentifierValueByNameAsDouble(E1.name);
	double value2 = dfa.iTable.getIdentifierValueByNameAsDouble(E2.name);
	if (logicOperator == "<") {
		if (value1 < value2)
		{
			flag = true;
		}
	}
	if (logicOperator == ">") {
		if (value1 > value2)
		{
			flag = true;
		}
	}
	if (logicOperator == "!=") {
		if (value1 != value2)
		{
			flag = true;
		}
	}
	if (logicOperator == ">=") {
		if (value1 >= value2)
		{
			flag = true;
		}
	}
	if (logicOperator == "<=") {
		if (value1 <= value2)
		{
			flag = true;
		}
	}
	if (logicOperator == "==") {
		if (value1 == value2)
		{
			flag = true;
		}
	}
	T.value = flag == true ? true : false;
	return T;
}

identifier Compiler::parseExpression() {
	cout << "�Ƶ�: <���ʽ> �� <��><���ʽPrime>" << endl;
	identifier E1 = parseItem();
	identifier E2 = parseExpressionPrime(E1);
	return E2;
}

identifier Compiler::parseExpressionPrime(identifier E1) {
	cout << "�Ƶ�: <���ʽPrime> �� <�ӷ������><��><���ʽPrime>|e" << endl;
	if (word.type == "�Ӻ�") {
		match("�Ӻ�");
		identifier E2 = parseItem();//��ǰ���ֵ
		identifier T = tempvartable.getNewTempVar();//������ʱ����������T1+T2��ֵ
		codetable.add("+", E1.name, E2.name, T.name);
		cout << "�����ӷ���Ԫʽ" << endl;
		//���мӷ�����
		T.value = this->myPlus(E1.value, E2.value);
		//�ӷ��������
		identifier E = parseExpressionPrime(T);//�� �ӷ��õ��Ľ�� ���ݸ����ʽprime �õ���һ�μ���Ľ��
		return E;
	}
	else {
		return E1;
	}
	return identifier("Error!");
}

identifier Compiler::parseItem() {
	cout << "�Ƶ�: <��> �� <����><��Prime>" << endl;
	identifier E1 = parseElement();//�������ӵ�ֵ
	identifier E2 = parseItemPrime(E1);
	return E2;
}

identifier Compiler::parseItemPrime(identifier E1) {
	cout << "�Ƶ�: <��Prime> ��<�˷������><����><��Prime>|e" << endl;
	if (word.type == "�˺�") {
		match("�˺�");
		identifier E2 = parseElement();//�������ӵ�ֵ
		identifier T = tempvartable.getNewTempVar();//������ʱ����T ���ڱ���˷������ֵ
		codetable.add("*", E1.name, E2.name, T.name);
		cout << "�����˷���Ԫʽ" << endl;
		//���г˷�����
		//cout <<endl<< "���г˷�����  " << E1.value <<"  " << E2.value << endl;
		T.value = this->myMult(E1.value, E2.value);
		//cout << T.value << endl;
		//�ӷ��˷�����
		identifier E = parseItemPrime(T);//�� �˷������� ���ݸ���prime���н�һ������
		return E;
	}
	else {
		return E1;
	}
	return identifier("Error!");
}

identifier Compiler::parseElement() {
	cout << "�Ƶ�: <����> �� <��ʶ��>|<����>|(<���ʽ>)" << endl;
	if (word.type == "��ʶ��") {
		identifier E(word.value);//��E ��ʶ��������
		E.value = dfa.iTable.getIdentifierValueByName(word.value);//��E ��ʶ����ֵ
		match("��ʶ��");
		E.type = "int";
		return E;
	}
	if (word.type == "��������") {
		identifier E(word.value);//��E ��ʶ��������
		E.value = word.value;//��E ��ʶ����ֵ
		match("��������");
		E.type = "int";
		return E;
	}
	if (word.type == "������") {
		match("������");
		identifier E = parseExpression();
		match("������");
		return E;
	}
	return identifier("Error!");
}

bool Compiler::parseCompoundStatement() {
	cout << "�Ƶ�: <�������> �� begin <��䲿��> end" << endl;
	match("begin");
	parseStatementSection();
	match("end");
	return true;
}

bool Compiler::parseNestStatement() {
	cout << "�Ƶ�: <Ƕ�����> �� <���>|<�������>" << endl;
	if (word.type == "��ʶ��" || word.type == "if" || word.type == "while") {
		parseStatement();
	}
	else if (word.type == "begin") {
		parseCompoundStatement();
	}
	return true;
}

string Compiler::myPlus(string str1, string str2) {
	double x = stod(str1);
	double y = stod(str2);
	return to_string(x + y);
}

string Compiler::myMult(string str1, string str2) {

	double x = stod(str1);
	double y = stod(str2);
	return to_string(x * y);
}
#pragma once
#include  <iostream>
#include  "dfa.h"
#include  "twoTuple.h"
using namespace std;


class Compiler {
private:
	DFA dfa;//�ʷ�����DFA
	twoTuple word;//���ڱ���ÿ�δʷ����������ԭʼ
	twoTuple nextInput();//��ȡ��һ���ʷ���������Ķ�Ԫʽ
	bool match(string);
	bool parseProgram();
	bool parseExplainVars();
	bool parseIdentifierList();
	bool parseIdentifierListPrime();
	bool parseStatementSection();
	bool parseStatementSectionPrime();
	bool parseStatement();
	bool parseAssignStatement();
	bool parseIfStatement();
	bool parseLoopStatement();
	bool parseCondition();
	bool parseExpression();
	bool parseExpressionPrime();
	bool parseItem();
	bool parseItemPrime();
	bool parseElement();
	bool parseNums();
	bool parseNumsPrime();
	bool parseCompoundStatement();
	bool parseNestStatement();

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
		cout << "ƥ��ʧ��! "<<word.type<<" != "<<type << endl;
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
	word = this->nextInput();
	cout << "-> ʶ�𵥴�: " << word << endl;
	this->parseProgram();
	this->dfa.iTable.dump();
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
	this->parseIdentifierList();
	return true;
}

bool Compiler::parseIdentifierList() {
	cout << "�Ƶ�: <��ʶ���б�> �� <��ʶ��><��ʶ���б�Prime>" << endl;
	this->match("��ʶ��");
	this->parseIdentifierListPrime();
	return true;
}

bool Compiler::parseIdentifierListPrime() {
	cout << "�Ƶ�: <��ʶ���б�Prime> ��,<��ʶ��><��ʶ���б�Prime>|e" << endl;
	if (word.type == "����") {
		this->match("����");
		this->match("��ʶ��");
		parseIdentifierListPrime();
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
	match("��ʶ��");
	match("��ֵ��");
	parseExpression();
	return true;
}

bool Compiler::parseIfStatement() {
	cout << "�Ƶ�: <�������> �� if ��<����>�� then <Ƕ�����>; else <Ƕ�����>" << endl;
	match("if");
	match("������");
	parseCondition();
	match("������");
	match("then");
	parseNestStatement();
	match("�ֺ�");
	match("else");
	parseNestStatement();
	return true;
}

bool Compiler::parseLoopStatement() {
	cout << "�Ƶ�: <ѭ�����> �� while ��<����>�� do <Ƕ�����>" << endl;
	match("while");
	match("������");
	parseCondition();
	match("������");
	match("do");
	parseNestStatement();
	return true;
}

bool Compiler::parseCondition() {
	cout << "�Ƶ�: <����> �� <���ʽ><��ϵ�����><���ʽ>" << endl;
	parseExpression();
	match("��ϵ�����");
	parseExpression();
	return true;
}

bool Compiler::parseExpression() {
	cout << "�Ƶ�: <���ʽ> �� <��><���ʽPrime>" << endl;
	parseItem();
	parseExpressionPrime();
	return true;
}

bool Compiler::parseExpressionPrime() {
	cout << "�Ƶ�: <���ʽPrime> ��<�ӷ������><��><���ʽPrime>|e" << endl;
	if (word.type == "�Ӻ�") {
		match("�Ӻ�");
		parseItem();
		parseExpressionPrime();
	}
	else {

	}
	return true;
}

bool Compiler::parseItem() {
	cout << "�Ƶ�: <��> ��<����><��Prime>" << endl;
	parseElement();
	parseItemPrime();
	return true;
}

bool Compiler::parseItemPrime() {
	cout << "�Ƶ�: <��Prime> ��<�˷������><����><��Prime>|e" << endl;
	if (word.type == "�˺�") {
		match("�˺�");
		parseElement();
		parseItemPrime();
	}
	else {

	}
	return true;
}

bool Compiler::parseElement() {
	cout << "�Ƶ�: <����> �� <��ʶ��>|<����>|(<���ʽ>)" << endl;
	if (word.type == "��ʶ��") {
		match("��ʶ��");
	}
	if (word.type == "��������") {
		match("��������");
	}
	if (word.type == "������") {
		match("������");
		parseExpression();
		match("������");
	}
	return true;
}

//������Ҫ
bool Compiler::parseNums() {
	cout << "�Ƶ�: <��������> �� <����><��������Prime>" << endl;
	return true;
}

//������Ҫ
bool Compiler::parseNumsPrime() {
	cout << "�Ƶ�: <��������Prime> �� <����><��������Prime>|e" << endl;
	return true;
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
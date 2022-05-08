#pragma once
#include  <iostream>
#include  "dfa.h"
#include  "twoTuple.h"
using namespace std;


class Compiler {
private:
	DFA dfa;//词法分析DFA
	twoTuple word;//用于保存每次词法分析输出而原始
	twoTuple nextInput();//获取下一个词法分析结果的二元式
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
		cout << "匹配失败! "<<word.type<<" != "<<type << endl;
		cout << "Error!" << endl;
		cout << endl << endl;
		return false;
	}
	else {
		//匹配成功
		cout << "-> 匹配成功: " << word << endl;
		word = this->nextInput();
		cout << "-> 识别单词: " << word << endl;
		return true;
	}
}

void Compiler::run() {
	word = this->nextInput();
	cout << "-> 识别单词: " << word << endl;
	this->parseProgram();
	this->dfa.iTable.dump();
}

bool Compiler::parseProgram() {
	cout << "推导: <程序> →<变量说明部分>;<语句部分>" << endl;
	this->parseExplainVars();
	this->match("分号");
	this->parseStatementSection();
	cout << "语法分析结束" << endl;
	return true;
}

bool Compiler::parseExplainVars() {
	cout << "推导: <变量说明部分> → <变量说明><标识符列表>" << endl;
	match("int");
	this->parseIdentifierList();
	return true;
}

bool Compiler::parseIdentifierList() {
	cout << "推导: <标识符列表> → <标识符><标识符列表Prime>" << endl;
	this->match("标识符");
	this->parseIdentifierListPrime();
	return true;
}

bool Compiler::parseIdentifierListPrime() {
	cout << "推导: <标识符列表Prime> →,<标识符><标识符列表Prime>|e" << endl;
	if (word.type == "逗号") {
		this->match("逗号");
		this->match("标识符");
		parseIdentifierListPrime();
	}
	else {
	}

	return true;
}

bool Compiler::parseStatementSection() {
	cout << "推导: <语句部分> →<语句>;<语句部分Prime>" << endl;
	parseStatement();
	match("分号");
	parseStatementSectionPrime();
	return true;
}

bool Compiler::parseStatementSectionPrime() {
	cout << "推导: <语句部分Prime> →<语句>;<语句部分Prime>|e" << endl;
	if (word.type == "标识符" || word.type == "if" || word.type == "while")
	{
		parseStatement();
		match("分号");
		parseStatementSectionPrime();
	}
	else {

	}
	return true;
}

bool Compiler::parseStatement() {
	cout << "推导: <语句> →<赋值语句>|<条件语句>|<循环语句>" << endl;
	if (word.type == "标识符") {
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
	cout << "推导: <赋值语句> →<标识符>=<表达式>" << endl;
	match("标识符");
	match("赋值号");
	parseExpression();
	return true;
}

bool Compiler::parseIfStatement() {
	cout << "推导: <条件语句> → if （<条件>） then <嵌套语句>; else <嵌套语句>" << endl;
	match("if");
	match("左括号");
	parseCondition();
	match("右括号");
	match("then");
	parseNestStatement();
	match("分号");
	match("else");
	parseNestStatement();
	return true;
}

bool Compiler::parseLoopStatement() {
	cout << "推导: <循环语句> → while （<条件>） do <嵌套语句>" << endl;
	match("while");
	match("左括号");
	parseCondition();
	match("右括号");
	match("do");
	parseNestStatement();
	return true;
}

bool Compiler::parseCondition() {
	cout << "推导: <条件> → <表达式><关系运算符><表达式>" << endl;
	parseExpression();
	match("关系运算符");
	parseExpression();
	return true;
}

bool Compiler::parseExpression() {
	cout << "推导: <表达式> → <项><表达式Prime>" << endl;
	parseItem();
	parseExpressionPrime();
	return true;
}

bool Compiler::parseExpressionPrime() {
	cout << "推导: <表达式Prime> →<加法运算符><项><表达式Prime>|e" << endl;
	if (word.type == "加号") {
		match("加号");
		parseItem();
		parseExpressionPrime();
	}
	else {

	}
	return true;
}

bool Compiler::parseItem() {
	cout << "推导: <项> →<因子><项Prime>" << endl;
	parseElement();
	parseItemPrime();
	return true;
}

bool Compiler::parseItemPrime() {
	cout << "推导: <项Prime> →<乘法运算符><因子><项Prime>|e" << endl;
	if (word.type == "乘号") {
		match("乘号");
		parseElement();
		parseItemPrime();
	}
	else {

	}
	return true;
}

bool Compiler::parseElement() {
	cout << "推导: <因子> → <标识符>|<常量>|(<表达式>)" << endl;
	if (word.type == "标识符") {
		match("标识符");
	}
	if (word.type == "数字序列") {
		match("数字序列");
	}
	if (word.type == "左括号") {
		match("左括号");
		parseExpression();
		match("右括号");
	}
	return true;
}

//好像不需要
bool Compiler::parseNums() {
	cout << "推导: <数字序列> → <数字><数字序列Prime>" << endl;
	return true;
}

//好像不需要
bool Compiler::parseNumsPrime() {
	cout << "推导: <数字序列Prime> → <数字><数字序列Prime>|e" << endl;
	return true;
}
bool Compiler::parseCompoundStatement() {
	cout << "推导: <复合语句> → begin <语句部分> end" << endl;
	match("begin");
	parseStatementSection();
	match("end");
	return true;
}

bool Compiler::parseNestStatement() {
	cout << "推导: <嵌套语句> → <语句>|<复合语句>" << endl;
	if (word.type == "标识符" || word.type == "if" || word.type == "while") {
		parseStatement();
	}
	else if (word.type == "begin") {
		parseCompoundStatement();
	}
	return true;
}
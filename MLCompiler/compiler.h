#pragma once
#include  <iostream>
#include  "dfa.h"
#include "middleCodeTable.h"
#include "tempVarTable.h"
using namespace std;

class Compiler {
private:
	DFA dfa;//词法分析DFA
	twoTuple word;//用于保存每次词法分析输出的二元式
	twoTuple nextInput();//获取下一个词法分析结果的二元式
	middleCodeTable codetable;//中间代码表 四元式
	tempVarTavble tempvartable;//临时变量表 用于保存 + * 运算的结果
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
		cout << "匹配失败! " << word.type << " != " << type << endl;
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
	cout << "词法分析开始" << endl;
	word = this->nextInput();
	cout << "-> 识别单词: " << word << endl;
	this->parseProgram();
	cout << this->dfa.iTable.dump();
	this->codetable.dump();
	this->tempvartable.dump();
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
	this->parseIdentifierList("int");//把变量类型传递给 标识符列表
	return true;
}

bool Compiler::parseIdentifierList(string type) {
	cout << "推导: <标识符列表> → <标识符><标识符列表Prime>" << endl;
	if (word.type == "标识符") {
		dfa.iTable.updateIdentifierTypeByName(word.value, "int");//更新变量的类型 word 为词法分析输出的二元式 word.value 为变量名字
		cout << "Update 更新标识符: " << word.value << " 的类型为 int" << endl;
		this->match("标识符");
	}
	this->parseIdentifierListPrime(type);
	return true;
}

bool Compiler::parseIdentifierListPrime(string type) {
	cout << "推导: <标识符列表Prime> →,<标识符><标识符列表Prime>|e" << endl;
	if (word.type == "逗号") {
		this->match("逗号");
		if (word.type == "标识符") {
			dfa.iTable.updateIdentifierTypeByName(word.value, "int");
			cout << "Update 更新标识符: " << word.value << " 的类型为 int" << endl;
			this->match("标识符");
		}
		parseIdentifierListPrime(type);
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
	string identifiername;
	if (word.type == "标识符") {
		identifiername = word.value;//保存标识符的名字
		match("标识符");
	}

	match("赋值号");
	identifier E = parseExpression();//创建一个变量来接收表达式的值
	codetable.add("=", E.name, "null", identifiername);
	cout << "产生赋值四元式" << endl;
	//更新标识符的值
	dfa.iTable.updateIdentifierValueByName(identifiername, E.value);
	//cout << endl << endl << E.name<<"  "<< E.value << endl << endl;
	return true;
}

bool Compiler::parseIfStatement() {
	cout << "推导: <条件语句> → if （<条件>） then <嵌套语句>; else <嵌套语句>" << endl;
	match("if");
	match("左括号");
	identifier E = parseCondition();
	match("右括号");
	match("then");
	codetable.add("jnz", E.name, "null", to_string(codetable.NXQ() + 2));
	int falseExitIndex = codetable.NXQ();
	codetable.add("j", "null", "null", "0");//需要回填

	parseNestStatement();
	int exitIndex = codetable.NXQ();
	codetable.add("j", "null", "null", "0");//需要回填
	codetable.Backpath(falseExitIndex, to_string(codetable.NXQ()));
	match("分号");
	match("else");
	parseNestStatement();
	codetable.Backpath(exitIndex, to_string(codetable.NXQ()));
	return true;
}

bool Compiler::parseLoopStatement() {
	cout << "推导: <循环语句> → while （<条件>） do <嵌套语句>" << endl;
	match("while");
	match("左括号");
	int initIndex = codetable.NXQ();//保存条件产生的四元式index
	identifier E = parseCondition();//获取条件返回的临时变量
	match("右括号");
	match("do");
	codetable.add("jnz", E.name, "null", to_string(codetable.NXQ() + 2));
	int falseExitIndex = codetable.NXQ();
	codetable.add("j", "null", "null", "null");//等待回填假出口
	parseNestStatement();
	codetable.add("j", "null", "null", to_string(initIndex));
	//开始回填
	codetable.Backpath(falseExitIndex, to_string(codetable.NXQ()));
	return true;
}

identifier Compiler::parseCondition() {
	cout << "推导: <条件> → <表达式><关系运算符><表达式>" << endl;
	identifier E1 = parseExpression();

	string logicOperator = "";
	if (word.type == "关系运算符") {
		logicOperator = word.value;
		match("关系运算符");
	}

	identifier E2 = parseExpression();

	//产生中间代码
	identifier T = tempvartable.getNewTempVar();
	codetable.add(logicOperator, E1.name, E2.name, T.name);
	cout << "产生逻辑计算四元式" << endl;
	//开始计算T的值
	T.type = "bool";
	bool flag = false;//满足条件就是true
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
	cout << "推导: <表达式> → <项><表达式Prime>" << endl;
	identifier E1 = parseItem();
	identifier E2 = parseExpressionPrime(E1);
	return E2;
}

identifier Compiler::parseExpressionPrime(identifier E1) {
	cout << "推导: <表达式Prime> → <加法运算符><项><表达式Prime>|e" << endl;
	if (word.type == "加号") {
		match("加号");
		identifier E2 = parseItem();//当前项的值
		identifier T = tempvartable.getNewTempVar();//创建临时变量来保存T1+T2的值
		codetable.add("+", E1.name, E2.name, T.name);
		cout << "产生加法四元式" << endl;
		//进行加法运算
		T.value = this->myPlus(E1.value, E2.value);
		//加法运算结束
		identifier E = parseExpressionPrime(T);//将 加法得到的结果 传递给表达式prime 得到下一次计算的结果
		return E;
	}
	else {
		return E1;
	}
	return identifier("Error!");
}

identifier Compiler::parseItem() {
	cout << "推导: <项> → <因子><项Prime>" << endl;
	identifier E1 = parseElement();//保存因子的值
	identifier E2 = parseItemPrime(E1);
	return E2;
}

identifier Compiler::parseItemPrime(identifier E1) {
	cout << "推导: <项Prime> →<乘法运算符><因子><项Prime>|e" << endl;
	if (word.type == "乘号") {
		match("乘号");
		identifier E2 = parseElement();//保存因子的值
		identifier T = tempvartable.getNewTempVar();//生成临时变量T 用于保存乘法运算的值
		codetable.add("*", E1.name, E2.name, T.name);
		cout << "产生乘法四元式" << endl;
		//进行乘法运算
		//cout <<endl<< "进行乘法运算  " << E1.value <<"  " << E2.value << endl;
		T.value = this->myMult(E1.value, E2.value);
		//cout << T.value << endl;
		//加法乘法结束
		identifier E = parseItemPrime(T);//将 乘法运算结果 传递给项prime进行进一步运算
		return E;
	}
	else {
		return E1;
	}
	return identifier("Error!");
}

identifier Compiler::parseElement() {
	cout << "推导: <因子> → <标识符>|<常量>|(<表达式>)" << endl;
	if (word.type == "标识符") {
		identifier E(word.value);//给E 标识符的名字
		E.value = dfa.iTable.getIdentifierValueByName(word.value);//给E 标识符的值
		match("标识符");
		E.type = "int";
		return E;
	}
	if (word.type == "数字序列") {
		identifier E(word.value);//给E 标识符的名字
		E.value = word.value;//给E 标识符的值
		match("数字序列");
		E.type = "int";
		return E;
	}
	if (word.type == "左括号") {
		match("左括号");
		identifier E = parseExpression();
		match("右括号");
		return E;
	}
	return identifier("Error!");
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
#pragma once
#include "identifierTable.h"
#include  <iostream>
#include <iomanip>
#include <string>
#include "twoTuple.h"
using namespace std;

class DFA {
public:
	DFA(string);

	twoTuple runOnce();

	void forwardState(int newState);

	void resetState();

	void printTuple(string type, string sign);

	identifierTable iTable;//保存标识符(变量)
private:

	string inputProgram;//保存程序源代码的字符串

	string temp;//保存正在读取单词的字符串

	int inputPointer;//保存读头的指针或整数

	int state;//保存自动机状态编号的 整数

};

DFA::DFA(string inputFile) {
	//自动机初始化
	this->inputProgram = inputFile;
	iTable.clear();
	temp = "";
	inputPointer = 0;
}

void DFA::forwardState(int newState) {
	temp += inputProgram[inputPointer];//添加正在读取的符号
	state = newState;//状态转移
	inputPointer++;//读头后移
}

void DFA::resetState() {
	state = 1;//转换为初始状态
	temp = "";//将当前读取清空
}

void DFA::printTuple(string type, string sign) {
	cout << "(" << setw(10) << type << "  ，" << setw(8) << sign << "     )" << endl;
}

twoTuple DFA::runOnce() {

	this->resetState();
	char symbol;

	while (inputProgram[inputPointer] != '\0')
	{
		//读取一个符号
		symbol = inputProgram[inputPointer];

		//处理 空格
		if (symbol == ' ')
		{
			//读头后移一位
			inputPointer++;
			continue;
		}

		//处理 int
		if (state == 1 && symbol == 'i')
		{
			forwardState(12);
			continue;
		}
		if (state == 12 && symbol == 'n')
		{
			forwardState(13);
			continue;
		}
		if (state == 13 && symbol == 't')
		{
			forwardState(14);
			return twoTuple("int", temp);
		}

		//处理 标识符（变量名）
		if (state == 1 && symbol == '$') {
			forwardState(2);
			continue;
		}
		if (state == 2 && symbol >= 'a' && symbol <= 'z') {
			forwardState(3);
			continue;
		}
		if (state == 3) {
			//变量名还没结束
			if ((symbol >= 'a' && symbol <= 'z') || (symbol >= '0' && symbol <= '9')) {
				forwardState(3);
				continue;
			}
			else
			{
				//变量名已经结束
				iTable.add(temp);
				return twoTuple("标识符", temp);
			}
		}

		//处理 ;
		if (state == 1 && symbol == ';') {
			forwardState(4);
			return twoTuple("分号", temp);
		}

		//处理 ,
		if (state == 1 && symbol == ',') {
			forwardState(5);
			return twoTuple("逗号", temp);
		}

		//处理 = 和 ==
		if (state == 1 && symbol == '=') {
			forwardState(6);
			continue;
		}
		if (state == 6) {
			if (symbol == '=')
			{
				forwardState(7);
				return twoTuple("关系运算符", temp);
			}
			else
			{
				return twoTuple("赋值号", temp);
			}
		}

		//处理 < 和 <=
		if (state == 1 && symbol == '<') {
			forwardState(8);
			continue;
		}
		if (state == 8) {
			if (symbol == '=')
			{
				forwardState(32);
				return twoTuple("关系运算符", temp);
			}
			else
			{
				return twoTuple("关系运算符",temp);
			}
		}

		//处理 > 和 >=
		if (state == 1 && symbol == '>') {
			forwardState(9);
			continue;
		}
		if (state == 9) {
			if (symbol == '=')
			{
				forwardState(33);
				return twoTuple("关系运算符", temp);
			}
			else
			{
				return twoTuple("关系运算符", temp);
			}
		}

		//处理 (
		if (state == 1 && symbol == '(') {
			forwardState(10);
			return twoTuple("左括号", temp);
		}

		//处理 ）
		if (state == 1 && symbol == ')') {
			forwardState(11);
			return twoTuple("右括号", temp);
		}

		//处理 +
		if (state == 1 && symbol == '+') {
			forwardState(37);
			return twoTuple("加号", temp);
		}

		//处理 *
		if (state == 1 && symbol == '*') {
			forwardState(34);
			return twoTuple("乘号", temp);
		}

		//处理 数字序列
		if (state == 1 && symbol >= '0' && symbol <= '9') {
			forwardState(35);
			continue;
		}
		if (state == 35)
		{
			if (symbol >= '0' && symbol <= '9') {
				forwardState(35);
				continue;
			}
			else {
				return twoTuple("数字序列", temp);
			}
		}

		//处理 if
		if (state == 12 && symbol == 'f') {
			forwardState(15);
			return twoTuple("if", temp);
		}

		//处理 then
		if (state == 1 && symbol == 't') {
			forwardState(16);
			continue;
		}
		if (state == 16 && symbol == 'h') {
			forwardState(17);
			continue;
		}
		if (state == 17 && symbol == 'e') {
			forwardState(18);
			continue;
		}
		if (state == 18 && symbol == 'n') {
			forwardState(19);
			return twoTuple("then", temp);
		}

		//处理 begin
		if (state == 1 && symbol == 'b') {
			forwardState(26);
			continue;
		}
		if (state == 26 && symbol == 'e') {
			forwardState(27);
			continue;
		}
		if (state == 27 && symbol == 'g') {
			forwardState(28);
			continue;
		}
		if (state == 28 && symbol == 'i') {
			forwardState(29);
			continue;
		}
		if (state == 29 && symbol == 'n') {
			forwardState(30);
			return twoTuple("begin", temp);
		}

		//处理 while
		if (state == 1 && symbol == 'w') {
			forwardState(40);
			continue;
		}
		if (state == 40 && symbol == 'h') {
			forwardState(41);
			continue;
		}
		if (state == 41 && symbol == 'i') {
			forwardState(42);
			continue;
		}
		if (state == 42 && symbol == 'l') {
			forwardState(43);
			continue;
		}
		if (state == 43 && symbol == 'e') {
			forwardState(44);
			return twoTuple("while", temp);
		}

		//处理 do
		if (state == 1 && symbol == 'd') {
			forwardState(38);
			continue;
		}
		if (state == 38 && symbol == 'o') {
			forwardState(39);
			return twoTuple("do", temp);
		}

		//处理 !=
		if (state == 1 && symbol == '!') {
			forwardState(45);
			continue;
		}
		if (state == 45 && symbol == '=') {
			forwardState(46);
			return twoTuple("关系运算符", temp);
		}

		//处理 else
		if (state == 1 && symbol == 'e') {
			forwardState(20);
			continue;
		}
		if (state == 20 && symbol == 'l') {
			forwardState(21);
			continue;
		}
		if (state == 21 && symbol == 's') {
			forwardState(22);
			continue;
		}
		if (state == 22 && symbol == 'e') {
			forwardState(23);
			return twoTuple("else", temp);
		}

		//处理 end
		if (state == 20 && symbol == 'n') {
			forwardState(24);
			continue;
		}
		if (state == 24 && symbol == 'd') {
			forwardState(25);
			return twoTuple("end", temp);
		}

		//错误处理
		cout << "无法识别的符号: " << symbol << endl;
		resetState();
		//读头后移一位
		inputPointer++;
	}
	//读取结束 返回一个特殊二元组来表示
	return twoTuple("#", "#");
}


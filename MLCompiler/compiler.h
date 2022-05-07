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
public:
	Compiler(string);

};

Compiler::Compiler(string inputFile) :dfa(inputFile) {

}
twoTuple Compiler::nextInput() {
	return dfa.runOnce();
}
bool Compiler::match(string type) {
	if (type != word.type) {
		cout<<"匹配失败!"<<endl;
		return false;
	}
	else {
		//匹配成功
		cout << "识别到单词:" << word << endl;
		word = this->nextInput();
		return true;
	}
}
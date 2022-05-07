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
		cout<<"ƥ��ʧ��!"<<endl;
		return false;
	}
	else {
		//ƥ��ɹ�
		cout << "ʶ�𵽵���:" << word << endl;
		word = this->nextInput();
		return true;
	}
}
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

	identifierTable iTable;//�����ʶ��(����)
private:

	string inputProgram;//�������Դ������ַ���

	string temp;//�������ڶ�ȡ���ʵ��ַ���

	int inputPointer;//�����ͷ��ָ�������

	int state;//�����Զ���״̬��ŵ� ����

};

DFA::DFA(string inputFile) {
	//�Զ�����ʼ��
	this->inputProgram = inputFile;
	iTable.clear();
	temp = "";
	inputPointer = 0;
}

void DFA::forwardState(int newState) {
	temp += inputProgram[inputPointer];//������ڶ�ȡ�ķ���
	state = newState;//״̬ת��
	inputPointer++;//��ͷ����
}

void DFA::resetState() {
	state = 1;//ת��Ϊ��ʼ״̬
	temp = "";//����ǰ��ȡ���
}

void DFA::printTuple(string type, string sign) {
	cout << "(" << setw(10) << type << "  ��" << setw(8) << sign << "     )" << endl;
}

twoTuple DFA::runOnce() {

	this->resetState();
	char symbol;

	while (inputProgram[inputPointer] != '\0')
	{
		//��ȡһ������
		symbol = inputProgram[inputPointer];

		//���� �ո�
		if (symbol == ' ')
		{
			//��ͷ����һλ
			inputPointer++;
			continue;
		}

		//���� int
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

		//���� ��ʶ������������
		if (state == 1 && symbol == '$') {
			forwardState(2);
			continue;
		}
		if (state == 2 && symbol >= 'a' && symbol <= 'z') {
			forwardState(3);
			continue;
		}
		if (state == 3) {
			//��������û����
			if ((symbol >= 'a' && symbol <= 'z') || (symbol >= '0' && symbol <= '9')) {
				forwardState(3);
				continue;
			}
			else
			{
				//�������Ѿ�����
				iTable.add(temp);
				return twoTuple("��ʶ��", temp);
			}
		}

		//���� ;
		if (state == 1 && symbol == ';') {
			forwardState(4);
			return twoTuple("�ֺ�", temp);
		}

		//���� ,
		if (state == 1 && symbol == ',') {
			forwardState(5);
			return twoTuple("����", temp);
		}

		//���� = �� ==
		if (state == 1 && symbol == '=') {
			forwardState(6);
			continue;
		}
		if (state == 6) {
			if (symbol == '=')
			{
				forwardState(7);
				return twoTuple("��ϵ�����", temp);
			}
			else
			{
				return twoTuple("��ֵ��", temp);
			}
		}

		//���� < �� <=
		if (state == 1 && symbol == '<') {
			forwardState(8);
			continue;
		}
		if (state == 8) {
			if (symbol == '=')
			{
				forwardState(32);
				return twoTuple("��ϵ�����", temp);
			}
			else
			{
				return twoTuple("��ϵ�����",temp);
			}
		}

		//���� > �� >=
		if (state == 1 && symbol == '>') {
			forwardState(9);
			continue;
		}
		if (state == 9) {
			if (symbol == '=')
			{
				forwardState(33);
				return twoTuple("��ϵ�����", temp);
			}
			else
			{
				return twoTuple("��ϵ�����", temp);
			}
		}

		//���� (
		if (state == 1 && symbol == '(') {
			forwardState(10);
			return twoTuple("������", temp);
		}

		//���� ��
		if (state == 1 && symbol == ')') {
			forwardState(11);
			return twoTuple("������", temp);
		}

		//���� +
		if (state == 1 && symbol == '+') {
			forwardState(37);
			return twoTuple("�Ӻ�", temp);
		}

		//���� *
		if (state == 1 && symbol == '*') {
			forwardState(34);
			return twoTuple("�˺�", temp);
		}

		//���� ��������
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
				return twoTuple("��������", temp);
			}
		}

		//���� if
		if (state == 12 && symbol == 'f') {
			forwardState(15);
			return twoTuple("if", temp);
		}

		//���� then
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

		//���� begin
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

		//���� while
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

		//���� do
		if (state == 1 && symbol == 'd') {
			forwardState(38);
			continue;
		}
		if (state == 38 && symbol == 'o') {
			forwardState(39);
			return twoTuple("do", temp);
		}

		//���� !=
		if (state == 1 && symbol == '!') {
			forwardState(45);
			continue;
		}
		if (state == 45 && symbol == '=') {
			forwardState(46);
			return twoTuple("��ϵ�����", temp);
		}

		//���� else
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

		//���� end
		if (state == 20 && symbol == 'n') {
			forwardState(24);
			continue;
		}
		if (state == 24 && symbol == 'd') {
			forwardState(25);
			return twoTuple("end", temp);
		}

		//������
		cout << "�޷�ʶ��ķ���: " << symbol << endl;
		resetState();
		//��ͷ����һλ
		inputPointer++;
	}
	//��ȡ���� ����һ�������Ԫ������ʾ
	return twoTuple("#", "#");
}


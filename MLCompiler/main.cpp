#include<iostream>
#include <vector>
#include <fstream>
#include "dfa.h"
#include "compiler.h"
using namespace std;


int main() {

	ifstream fin;
	fin.open("201921147181in.txt", ios::in);
	if (!fin.is_open())
	{
		cout << "无法找到这个文件！" << endl;
		return 0;
	}
	string buff;
	string inputFile = "";
	while (getline(fin, buff))
	{
		inputFile += buff;
	}
	fin.close();

	Compiler myCompiler(inputFile);
	myCompiler.nextInput();
	return 0;
}
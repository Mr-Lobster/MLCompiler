#include<iostream>
#include <fstream>
#include<windows.h>
using namespace std;

//定义文件句柄
ifstream fin;
ofstream fout;

//添加本地文件
#include "compiler.h"
int main() {

	
	fin.open("in.txt", ios::in);//读入文件
	fout.open("out.txt", ios::out);//写入文件

	SYSTEMTIME st;//定义本地时间变量，该变量为结构体
	GetLocalTime(&st);//获取本地时间函数，参数为时间变量指针
	//写入当前时间
	fout << st.wYear << "年" << " ";//显示某年
	fout << st.wMonth << "月" << "";//显示某月
	fout << st.wDay << "日" << " ";//显示某日
	fout << st.wHour << "时" << "";//显示某时
	fout << st.wMinute << "分" << "";//显示某分
	fout << st.wSecond << "秒" << " ";//显示某秒
	fout << "星期" << st.wDayOfWeek << endl;//显示星期

	//读取输入的文件
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

	//传入程序代码
	Compiler myCompiler(inputFile);
	//启动编译器
	myCompiler.run();

	//关闭文件句柄
	fin.close();
	fout.close();
	return 0;
}
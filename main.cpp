#include <iostream>

#include "myString.h"
#include "windows.h"	//设置颜色

using namespace std;

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);//设置绿色
	cout << "	   *********************************" << endl;
	cout << "	   *" << "				   " << "*" << endl;
	cout << "	   *" << "	   实验二（文本编辑器）    " << "*" << endl;
	cout << "	   *" << "	     实现基本操作          " << "*" << endl;
	cout << "	   *" << "	       实现替换            " << "*" << endl;
	cout << "	   *" << "				   " << "*" << endl;
	cout << "	   *********************************" << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);//设置原色

	myString myString1;
	string file = "new1.txt";	//自动生成一个空白文档
	string s;
	list<A> li = myString1.openFile(file);
	list<A> *plist = &li;

	int func;
	while (1)
	{
		while (1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);//设置绿色
			cout << "[1]打开文件  [2]保存文件  [3]另存为  [4]插入  [5]查找  [6]删除  [7]展示  [8]替换  [9]退出" << endl;
			cout << "请输入你需要的功能：";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);//设置原色
			cin >> func;
			char sbuf[1024];
			if (func == 1 || func == 2 || func == 3 || func == 4 || func == 5 || func == 6 || func == 7 || func == 8 || func == 9)
				break;
			else
			{
				fgets(sbuf, 1024, stdin); // 将缓冲中的所有字符读到sbuf，即达到清空缓冲的目的
				cout << "请退出重进" << endl;
			}
		}
		if (func == 1)
		{
			cout << "请输入文件名：";
			getline(cin, s);
			getline(cin, file);
			li = myString1.openFile(file);
			plist = &li;
		}
		else if (func == 2)
		{
			myString1.save(file, li);
		}
		else if (func == 3)
		{
			myString1.saveAs(li);
		}
		else if (func == 4)
		{
			int insert = myString1.insert(plist);
			if (insert == 0)
				cout << "插入失败" << endl;
		}
		else if (func == 5)
		{
			getline(cin, s);
			int search = myString1.search(li);
			if (search == 0)
				cout << "未找到" << endl;
		}
		else if (func == 6)
		{
			getline(cin, s);
			myString1.del(plist);
		}
		else if (func == 7)
		{
			myString1.show(li);
		}
		else if (func == 8)
		{
			getline(cin, s);
			myString1.replace(plist);
		}
		else if (func == 9)
		{
			exit(0);
		}
	}
	return 0;
}
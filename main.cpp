#include <iostream>

#include "myString.h"
#include "windows.h"	//������ɫ

using namespace std;

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);//������ɫ
	cout << "	   *********************************" << endl;
	cout << "	   *" << "				   " << "*" << endl;
	cout << "	   *" << "	   ʵ������ı��༭����    " << "*" << endl;
	cout << "	   *" << "	     ʵ�ֻ�������          " << "*" << endl;
	cout << "	   *" << "	       ʵ���滻            " << "*" << endl;
	cout << "	   *" << "				   " << "*" << endl;
	cout << "	   *********************************" << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);//����ԭɫ

	myString myString1;
	string file = "new1.txt";	//�Զ�����һ���հ��ĵ�
	string s;
	list<A> li = myString1.openFile(file);
	list<A> *plist = &li;

	int func;
	while (1)
	{
		while (1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);//������ɫ
			cout << "[1]���ļ�  [2]�����ļ�  [3]���Ϊ  [4]����  [5]����  [6]ɾ��  [7]չʾ  [8]�滻  [9]�˳�" << endl;
			cout << "����������Ҫ�Ĺ��ܣ�";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);//����ԭɫ
			cin >> func;
			char sbuf[1024];
			if (func == 1 || func == 2 || func == 3 || func == 4 || func == 5 || func == 6 || func == 7 || func == 8 || func == 9)
				break;
			else
			{
				fgets(sbuf, 1024, stdin); // �������е������ַ�����sbuf�����ﵽ��ջ����Ŀ��
				cout << "���˳��ؽ�" << endl;
			}
		}
		if (func == 1)
		{
			cout << "�������ļ�����";
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
				cout << "����ʧ��" << endl;
		}
		else if (func == 5)
		{
			getline(cin, s);
			int search = myString1.search(li);
			if (search == 0)
				cout << "δ�ҵ�" << endl;
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
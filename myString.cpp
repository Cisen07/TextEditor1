#include <iostream>
#include <fstream>
#include <list>

#include "myString.h"
#include "windows.h"

using namespace std;

myString::myString()
{
}

list<A> myString::openFile(string file)
{
	string str, str1;
	ifstream in;
	in.open(file);	//如果open函数只有文件名一个参数，则是以读/写普通文件打开
	list<A> list;
	if (in.is_open())
	{
		while (!in.eof())
		{
			getline(in, str);
			if (str.length() <= 80)	//str.length()的长度不包括结尾的'\n'，长度小于八十直接进，注意结尾有换行
			{
				A a = { str, 1 };
				list.push_back(a);
			}
			else
			{
				while (str.length() > 80)
				{
					str1 = str.substr(0, 80);
					A a = { str1, 0 };
					list.push_back(a);
					str = str.substr(80, str.length() - 1);
				}
				if (!str.empty())	//str.length()的长度不包括结尾的'\n'，长度小于八十直接进，注意结尾有换行
				{
					A a = { str, 1 };
					list.push_back(a);
				}
			}
		}
		list.back().newLine = 2;
		in.close();
	}
	return list;
}

void myString::show(list<A> li)
{
	cout << "文本如下：" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);//设置青色
	while (!li.empty())
	{
		cout << li.front().str << endl;
		li.pop_front();
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);//设置原色
}

int myString::insert(list<A> *li)
{
	int row, line, num = 0;	//num用来存xlist遍历的结点数量
	list<A> xlist = *li;	//将li数据给xlist
	int n = xlist.size();
	list<A>::iterator endIter = xlist.end();
	cout << "**注意**：输入\"" << xlist.size() << "\"意味着结尾另起一行插入" << endl;
	cout << "请输入想插入的行数（0-" << xlist.size() << "）：";
	cin >> row;
	char sbuf[1024];
	fgets(sbuf, 1024, stdin); // 将缓冲中的所有字符读到sbuf，即达到清空缓冲的目的
	if (row == xlist.size())	//特例处理，这是在结尾加结点
	{
		cout << "请输入想插入的字符串：";
		string s1;
		getline(cin, s1);
		if (s1.length() <= 80)	//s.length()不大于八十直接进，注意结尾有换行
		{
			A a = { s1, 1 };
			li->push_back(a);
		}
		else
		{
			string str1;
			while (s1.length() > 80)
			{
				str1 = s1.substr(0, 80);
				A a = { str1, 0 };
				li->push_back(a);
				s1 = s1.substr(80, s1.length() - 1);
			}
			if (!s1.empty())	//str.length()的长度不包括结尾的'\n'，长度小于八十直接进，注意结尾有换行
			{
				A a = { s1, 1 };
				li->push_back(a);
			}
		}
		li->back().newLine = 2;
		return 1;
	}
	for (int a = 0; a < n; a++)	//将li清空
		li->pop_back();
	if (row < 0 || row > xlist.size())
		return 0;
	list<A>::iterator iter = xlist.begin();
	for (int a = 0; a < row; a++, num++)	//循环结束后num中算进去了row结点
		iter++;
	cout << "请输入想插入的列数（0-" << (*iter).str.length() << "）：";
	cin >> line;
	fgets(sbuf, 1024, stdin); // 将缓冲中的所有字符读到sbuf，即达到清空缓冲的目的
	if (line < 0 || line > (*iter).str.length())
		return 0;
	cout << "请输入想插入的字符串：";
	string s1;
	getline(cin, s1);
	for (int a = 0; a < row; a++)	//序号为row的node之前的，都从xlist传给li
	{
		li->push_back(xlist.front());
		xlist.pop_front();
	}
	string s;
	s = (*iter).str;
	while ((*iter).newLine == 0)
	{
		iter++;
		s += (*iter).str;
		num++;
	}
	s = s.substr(0, line) + s1 + s.substr(line, s.length() - line);
	if (s.length() <= 80)	//s.length()不大于八十直接进，注意结尾有换行
	{
		A a = { s, 1 };
		li->push_back(a);
	}
	else
	{
		string str1;
		while (s.length() > 80)
		{
			str1 = s.substr(0, 80);
			A a = { str1, 0 };
			li->push_back(a);
			s = s.substr(80, s.length() - 1);
		}
		if (!s.empty())	//str.length()的长度不包括结尾的'\n'，长度小于八十直接进，注意结尾有换行
		{
			A a = { s, 1 };
			li->push_back(a);
		}
	}
	while (num < n - 1)
	{
		iter++;
		li->push_back((*iter));
		num++;
	}
	return 1;
}

void myString::del(list<A>* li)	
{
	string s;	//临时主串
	string s1;	//要找的字符串
	list<A> xlist = *li;
	int n = xlist.size();	//n为链表中元素数量
	int i, j = 0, temp = -1, offset[80];	//offset[]中保存一段中可能发现的目标偏移量
	int lines = 0;	//操作的行数
	int	k = 0;	//标识整篇有无目标串
	int k1 = 0;	//标识本段有无目标串
	int m = 0;
	cout << "输入你想删除的字符串：";
	getline(cin, s1);
	for (i = 0; i < n; i++)
	{
		if (xlist.front().newLine == 0)
		{
			s += xlist.front().str;
			xlist.pop_front();
			lines++;
		}
		else
		{
			s += xlist.front().str;
			xlist.pop_front();
			lines++;
			if (s.find(s1) != string::npos)	//在该段中找到了目标串
			{
				k = 1;
				k1 = 1;
			}
			else
			{	//在该段中没找到目标串
				k1 = 0;
			}
			while (s.find(s1) != string::npos)
			{
				temp += s.find(s1) + 1;
				offset[j++] = temp;
				s = s.substr(s.find(s1) + 1, s.length() - s.find(s1) - 1);
			}	
			offset[j] = -1;
			if (k1 == 1)
			{
				int a = 0;
				for (; a < j; a++)
				{
					cout << "第" << offset[a] / 80 + 1 + m << "行\t";
					cout << "第" << offset[a] % 80 + 1 << "个字符开始" << endl;
				}

			}
			m += lines;	//保存下来这段做完到了几行
			lines = 0;
			j = 0;
			s = "";
			temp = -1;
			offset[0] = -1;
		}
	}
	if (k == 1)	//找到了目标串，接下来进行删除操作
	{
		int oneOrAll = 0;	//判别删除第一个字符串还是全部找到的字符串(键入1或0)
		while (1)
		{
			cout << "删除第一个字符串还是全部找到的字符串(键入1或0): ";
			cin >> oneOrAll;
			if (oneOrAll == 1 || oneOrAll == 0)
				break;
		}
		list<A> ylist = *li;
		m = 0;
		if (oneOrAll == 1)	//删除第一个字符串
		{
			int eraseOrNot = 0;	//为1的时候表示删除了第一个字符串
			for (i = 0; i < n; i++)	//开始每行的遍历
			{
				if (ylist.front().newLine == 0)
				{
					s += ylist.front().str;
					ylist.pop_front();
					lines++;
				}
				else
				{
					s += ylist.front().str;
					ylist.pop_front();
					lines++;
					if (eraseOrNot == 0)
					{

						if (s.find(s1) != string::npos)	//在该段中找到了目标串
						{
							k1 = 1;
						}
						else
						{
							k1 = 0;
						}
						if (s.find(s1) != string::npos)
						{
							temp += s.find(s1) + 1;
							offset[j++] = temp;
						}
						offset[j] = -1;
						if (k1 == 1)
						{
							int a = 0;
							for (; a < j; a++)
							{
								s.erase(offset[0], s1.length());
								for (int lit = 0; lit < n; lit++)	//清空li串
								{
									li->pop_back();
								}
								if (s.length() <= 80)	//s.length()不大于八十直接进，注意结尾有换行
								{
									A a = { s, 1 };
									li->push_back(a);
								}
								else
								{
									string str1;
									while (s.length() > 80)
									{
										str1 = s.substr(0, 80);
										A a = { str1, 0 };
										li->push_back(a);
										s = s.substr(80, s.length() - 1);
									}
									if (!s.empty())	//str.length()的长度不包括结尾的'\n'，长度小于八十直接进，注意结尾有换行
									{
										A a = { s, 1 };
										li->push_back(a);
									}
								}
								eraseOrNot = 1;
							}
						}
						else
						{	//因为该段中没有目标穿，所以直接把s放入li中
							if (s.length() <= 80)	//s.length()不大于八十直接进，注意结尾有换行
							{
								A a = { s, 1 };
								li->push_back(a);
							}
							else
							{
								string str1;
								while (s.length() > 80)
								{
									str1 = s.substr(0, 80);
									A a = { str1, 0 };
									li->push_back(a);
									s = s.substr(80, s.length() - 1);
								}
								if (!s.empty())	//str.length()的长度不包括结尾的'\n'，长度小于八十直接进，注意结尾有换行
								{
									A a = { s, 1 };
									li->push_back(a);
								}
							}
						}
					}
					else
					{	//因为第一个已经被删除，不需要再查找，只是把s放入li中
						if (s.length() <= 80)	//s.length()不大于八十直接进，注意结尾有换行
						{
							A a = { s, 1 };
							li->push_back(a);
						}
						else
						{
							string str1;
							while (s.length() > 80)
							{
								str1 = s.substr(0, 80);
								A a = { str1, 0 };
								li->push_back(a);
								s = s.substr(80, s.length() - 1);
							}
							if (!s.empty())	//str.length()的长度不包括结尾的'\n'，长度小于八十直接进，注意结尾有换行
							{
								A a = { s, 1 };
								li->push_back(a);
							}
						}
					}
					m += lines;	//保存下来这段做完到了几行
					lines = 0;
					j = 0;
					s = "";
					temp = -1;
					offset[0] = -1;
				}
			}
		}
		else
		{	//删除全部找到的字符串
			for (int lit = 0; lit < n; lit++)	//清空li串
			{
				li->pop_back();
			}
			for (i = 0; i < n; i++)
			{
				if (ylist.front().newLine == 0)
				{
					s += ylist.front().str;
					ylist.pop_front();
					lines++;
				}
				else
				{
					s += ylist.front().str;
					ylist.pop_front();
					lines++;
					while (s.find(s1) != string::npos)
					{
						s = s.erase(s.find(s1), s1.length());
					}
					if (s.length() <= 80)	//s.length()不大于八十直接进，注意结尾有换行
					{
						A a = { s, 1 };
						li->push_back(a);
					}
					else
					{
						string str1;
						while (s.length() > 80)
						{
							str1 = s.substr(0, 80);
							A a = { str1, 0 };
							li->push_back(a);
							s = s.substr(80, s.length() - 1);
						}
						if (!s.empty())	//str.length()的长度不包括结尾的'\n'，长度小于八十直接进，注意结尾有换行
						{
							A a = { s, 1 };
							li->push_back(a);
						}
					}
					s = "";
				}
			}
		}
	}
	else
		cout << "该字符串不存在" << endl;
	li->back().newLine = 2;
}

int myString::search(list<A> li)
{
	string s;	//临时主串
	string s1;	//要找的字符串
	list<A> xlist = li;
	int n = xlist.size();	//n为链表中元素数量
	int i, j = 0, temp = -1, offset[80];	//offset[]中保存一段中可能发现的目标偏移量
	int lines = 0;	//操作的行数
	int	k = 0;	//标识整篇有无目标串
	int k1 = 0;	//标识本段有无目标串
	int m = 0;
	cout << "输入你想找的字符串：";
	getline(cin, s1);
	for (i = 0; i < n; i++)
	{
		if (xlist.front().newLine == 0)
		{
			s += xlist.front().str;
			xlist.pop_front();
			lines++;
		}
		else
		{	
			s += xlist.front().str;
			xlist.pop_front();
			lines++;
			if (s.find(s1) != string::npos)	//在该段中找到了目标串
			{
				k = 1;
				k1 = 1;
			}
			else
			{	//在该段中没找到目标串
				k1 = 0;
			}
			while (s.find(s1) != string::npos)
			{
				temp += s.find(s1) + 1;
				offset[j++] = temp;
				s = s.substr(s.find(s1) + 1, s.length() - s.find(s1) - 1);
			}	
			offset[j] = -1;
			if (k1 == 1)
			{	
				int a = 0;
				for (; a < j; a++)
				{
					cout << "第" << offset[a] / 80 + 1 + m<< "行\t";
					cout << "第" << offset[a] % 80 + 1 << "个字符开始" << endl;
				}
				
			}
			m += lines;	//保存下来这段做完到了几行
			lines = 0;
			j = 0;
			s = "";
			temp = -1;
			offset[0] = -1;
		}
	}
	if (k == 1)
		return 1;
	else
		return 0;
}

void myString::save(const string file, list<A> li)
{
	ofstream out(file);
	if (out.is_open())
	{
		int n = li.size();
		A a;
		for (int i = 0; i < n; i++)
		{
			a = li.front();
			li.pop_front();
			out << a.str;
			if (a.newLine == 1)
				out << endl;
		}
		out.close();
	}
}

void myString::saveAs(list<A> li)
{
	string file;
	cout << "请输入欲保存的文件名：";
	cin >> file;
	ofstream out(file);
	if (out.is_open())
	{
		int n = li.size();
		A a;
		for (int i = 0; i < n; i++)
		{
			a = li.front();
			li.pop_front();
			out << a.str;
			if (a.newLine == 1)
				out << endl;
		}
		out.close();
	}
}

void myString::replace(list<A> *li)
{
	string s;	//临时主串
	string s1;	//要找的字符串
	string sp;	//用来替换的字符串
	list<A> xlist = *li;
	int n = xlist.size();	//n为链表中元素数量
	int i, j = 0, temp = -1, offset[80];	//offset[]中保存一段中可能发现的目标偏移量
	int lines = 0;	//操作的行数
	int	k = 0;	//标识整篇有无目标串
	int k1 = 0;	//标识本段有无目标串
	int m = 0;
	cout << "输入你想被替换的文中字符串：";
	getline(cin, s1);
	for (i = 0; i < n; i++)
	{
		if (xlist.front().newLine == 0)
		{
			s += xlist.front().str;
			xlist.pop_front();
			lines++;
		}
		else
		{
			s += xlist.front().str;
			xlist.pop_front();
			lines++;
			if (s.find(s1) != string::npos)	//在该段中找到了目标串
			{
				k = 1;
				k1 = 1;
			}
			else
			{	//在该段中没找到目标串
				k1 = 0;
			}
			while (s.find(s1) != string::npos)
			{
				temp += s.find(s1) + 1;
				offset[j++] = temp;
				s = s.substr(s.find(s1) + 1, s.length() - s.find(s1) - 1);
			}
			offset[j] = -1;
			if (k1 == 1)
			{
				int a = 0;
				for (; a < j; a++)
				{
					cout << "第" << offset[a] / 80 + 1 + m << "行\t";
					cout << "第" << offset[a] % 80 + 1 << "个字符开始" << endl;
				}

			}
			m += lines;	//保存下来这段做完到了几行
			lines = 0;
			j = 0;
			s = "";
			temp = -1;
			offset[0] = -1;
		}
	}
	if (k == 1)	//找到了目标串，接下来进行删除操作
	{
		cout << "输入你想用来替换的字符串：";
		getline(cin, sp);
		int oneOrAll = 0;	//判别删除第一个字符串还是全部找到的字符串(键入1或0)
		while (1)
		{
			cout << "替换第一个字符串还是全部找到的字符串(键入1或0): ";
			cin >> oneOrAll;
			if (oneOrAll == 1 || oneOrAll == 0)
				break;
		}
		list<A> ylist = *li;
		m = 0;
		if (oneOrAll == 1)	//替换第一个字符串
		{
			int eraseOrNot = 0;	//为1的时候表示删除了第一个字符串
			for (i = 0; i < n; i++)	//开始每行的遍历
			{
				if (ylist.front().newLine == 0)
				{
					s += ylist.front().str;
					ylist.pop_front();
					lines++;
				}
				else
				{
					s += ylist.front().str;
					ylist.pop_front();
					lines++;
					if (eraseOrNot == 0)
					{

						if (s.find(s1) != string::npos)	//在该段中找到了目标串
						{
							k1 = 1;
						}
						else
						{
							k1 = 0;
						}
						if (s.find(s1) != string::npos)
						{
							temp += s.find(s1) + 1;
							offset[j++] = temp;
						}
						offset[j] = -1;
						if (k1 == 1)
						{
							int a = 0;
							for (; a < j; a++)
							{
								s.erase(offset[0], s1.length());
								s = s.substr(0, offset[0]) + sp + s.substr(offset[0], s.length() - offset[0]);
								for (int lit = 0; lit < n; lit++)	//清空li串
								{
									li->pop_back();
								}
								if (s.length() <= 80)	//s.length()不大于八十直接进，注意结尾有换行
								{
									A a = { s, 1 };
									li->push_back(a);
								}
								else
								{
									string str1;
									while (s.length() > 80)
									{
										str1 = s.substr(0, 80);
										A a = { str1, 0 };
										li->push_back(a);
										s = s.substr(80, s.length() - 1);
									}
									if (!s.empty())	//str.length()的长度不包括结尾的'\n'，长度小于八十直接进，注意结尾有换行
									{
										A a = { s, 1 };
										li->push_back(a);
									}
								}
								eraseOrNot = 1;
							}
						}
						else
						{	//因为该段中没有目标穿，所以直接把s放入li中
							if (s.length() <= 80)	//s.length()不大于八十直接进，注意结尾有换行
							{
								A a = { s, 1 };
								li->push_back(a);
							}
							else
							{
								string str1;
								while (s.length() > 80)
								{
									str1 = s.substr(0, 80);
									A a = { str1, 0 };
									li->push_back(a);
									s = s.substr(80, s.length() - 1);
								}
								if (!s.empty())	//str.length()的长度不包括结尾的'\n'，长度小于八十直接进，注意结尾有换行
								{
									A a = { s, 1 };
									li->push_back(a);
								}
							}
						}
					}
					else
					{	//因为第一个已经被删除，不需要再查找，只是把s放入li中
						if (s.length() <= 80)	//s.length()不大于八十直接进，注意结尾有换行
						{
							A a = { s, 1 };
							li->push_back(a);
						}
						else
						{
							string str1;
							while (s.length() > 80)
							{
								str1 = s.substr(0, 80);
								A a = { str1, 0 };
								li->push_back(a);
								s = s.substr(80, s.length() - 1);
							}
							if (!s.empty())	//str.length()的长度不包括结尾的'\n'，长度小于八十直接进，注意结尾有换行
							{
								A a = { s, 1 };
								li->push_back(a);
							}
						}
					}
					m += lines;	//保存下来这段做完到了几行
					lines = 0;
					j = 0;
					s = "";
					temp = -1;
					offset[0] = -1;
				}
			}
		}
		else
		{	//替换全部找到的字符串
			for (int lit = 0; lit < n; lit++)	//清空li串
			{
				li->pop_back();
			}
			for (i = 0; i < n; i++)
			{
				if (ylist.front().newLine == 0)
				{
					s += ylist.front().str;
					ylist.pop_front();
					lines++;
				}
				else
				{
					s += ylist.front().str;
					ylist.pop_front();
					lines++;
					while (s.find(s1) != string::npos)
					{
						int temp1 = s.find(s1);
						s = s.erase(s.find(s1), s1.length());
						s = s.substr(0, temp1) + sp + s.substr(temp1, s.length() - temp1);
					}
					if (s.length() <= 80)	//s.length()不大于八十直接进，注意结尾有换行
					{
						A a = { s, 1 };
						li->push_back(a);
					}
					else
					{
						string str1;
						while (s.length() > 80)
						{
							str1 = s.substr(0, 80);
							A a = { str1, 0 };
							li->push_back(a);
							s = s.substr(80, s.length() - 1);
						}
						if (!s.empty())	//str.length()的长度不包括结尾的'\n'，长度小于八十直接进，注意结尾有换行
						{
							A a = { s, 1 };
							li->push_back(a);
						}
					}
					s = "";
				}
			}
		}
	}
	else
		cout << "该字符串不存在" << endl;
	li->back().newLine = 2;
}
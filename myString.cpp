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
	in.open(file);	//���open����ֻ���ļ���һ�������������Զ�/д��ͨ�ļ���
	list<A> list;
	if (in.is_open())
	{
		while (!in.eof())
		{
			getline(in, str);
			if (str.length() <= 80)	//str.length()�ĳ��Ȳ�������β��'\n'������С�ڰ�ʮֱ�ӽ���ע���β�л���
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
				if (!str.empty())	//str.length()�ĳ��Ȳ�������β��'\n'������С�ڰ�ʮֱ�ӽ���ע���β�л���
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
	cout << "�ı����£�" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);//������ɫ
	while (!li.empty())
	{
		cout << li.front().str << endl;
		li.pop_front();
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);//����ԭɫ
}

int myString::insert(list<A> *li)
{
	int row, line, num = 0;	//num������xlist�����Ľ������
	list<A> xlist = *li;	//��li���ݸ�xlist
	int n = xlist.size();
	list<A>::iterator endIter = xlist.end();
	cout << "**ע��**������\"" << xlist.size() << "\"��ζ�Ž�β����һ�в���" << endl;
	cout << "������������������0-" << xlist.size() << "����";
	cin >> row;
	char sbuf[1024];
	fgets(sbuf, 1024, stdin); // �������е������ַ�����sbuf�����ﵽ��ջ����Ŀ��
	if (row == xlist.size())	//�������������ڽ�β�ӽ��
	{
		cout << "�������������ַ�����";
		string s1;
		getline(cin, s1);
		if (s1.length() <= 80)	//s.length()�����ڰ�ʮֱ�ӽ���ע���β�л���
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
			if (!s1.empty())	//str.length()�ĳ��Ȳ�������β��'\n'������С�ڰ�ʮֱ�ӽ���ע���β�л���
			{
				A a = { s1, 1 };
				li->push_back(a);
			}
		}
		li->back().newLine = 2;
		return 1;
	}
	for (int a = 0; a < n; a++)	//��li���
		li->pop_back();
	if (row < 0 || row > xlist.size())
		return 0;
	list<A>::iterator iter = xlist.begin();
	for (int a = 0; a < row; a++, num++)	//ѭ��������num�����ȥ��row���
		iter++;
	cout << "������������������0-" << (*iter).str.length() << "����";
	cin >> line;
	fgets(sbuf, 1024, stdin); // �������е������ַ�����sbuf�����ﵽ��ջ����Ŀ��
	if (line < 0 || line > (*iter).str.length())
		return 0;
	cout << "�������������ַ�����";
	string s1;
	getline(cin, s1);
	for (int a = 0; a < row; a++)	//���Ϊrow��node֮ǰ�ģ�����xlist����li
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
	if (s.length() <= 80)	//s.length()�����ڰ�ʮֱ�ӽ���ע���β�л���
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
		if (!s.empty())	//str.length()�ĳ��Ȳ�������β��'\n'������С�ڰ�ʮֱ�ӽ���ע���β�л���
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
	string s;	//��ʱ����
	string s1;	//Ҫ�ҵ��ַ���
	list<A> xlist = *li;
	int n = xlist.size();	//nΪ������Ԫ������
	int i, j = 0, temp = -1, offset[80];	//offset[]�б���һ���п��ܷ��ֵ�Ŀ��ƫ����
	int lines = 0;	//����������
	int	k = 0;	//��ʶ��ƪ����Ŀ�괮
	int k1 = 0;	//��ʶ��������Ŀ�괮
	int m = 0;
	cout << "��������ɾ�����ַ�����";
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
			if (s.find(s1) != string::npos)	//�ڸö����ҵ���Ŀ�괮
			{
				k = 1;
				k1 = 1;
			}
			else
			{	//�ڸö���û�ҵ�Ŀ�괮
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
					cout << "��" << offset[a] / 80 + 1 + m << "��\t";
					cout << "��" << offset[a] % 80 + 1 << "���ַ���ʼ" << endl;
				}

			}
			m += lines;	//��������������굽�˼���
			lines = 0;
			j = 0;
			s = "";
			temp = -1;
			offset[0] = -1;
		}
	}
	if (k == 1)	//�ҵ���Ŀ�괮������������ɾ������
	{
		int oneOrAll = 0;	//�б�ɾ����һ���ַ�������ȫ���ҵ����ַ���(����1��0)
		while (1)
		{
			cout << "ɾ����һ���ַ�������ȫ���ҵ����ַ���(����1��0): ";
			cin >> oneOrAll;
			if (oneOrAll == 1 || oneOrAll == 0)
				break;
		}
		list<A> ylist = *li;
		m = 0;
		if (oneOrAll == 1)	//ɾ����һ���ַ���
		{
			int eraseOrNot = 0;	//Ϊ1��ʱ���ʾɾ���˵�һ���ַ���
			for (i = 0; i < n; i++)	//��ʼÿ�еı���
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

						if (s.find(s1) != string::npos)	//�ڸö����ҵ���Ŀ�괮
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
								for (int lit = 0; lit < n; lit++)	//���li��
								{
									li->pop_back();
								}
								if (s.length() <= 80)	//s.length()�����ڰ�ʮֱ�ӽ���ע���β�л���
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
									if (!s.empty())	//str.length()�ĳ��Ȳ�������β��'\n'������С�ڰ�ʮֱ�ӽ���ע���β�л���
									{
										A a = { s, 1 };
										li->push_back(a);
									}
								}
								eraseOrNot = 1;
							}
						}
						else
						{	//��Ϊ�ö���û��Ŀ�괩������ֱ�Ӱ�s����li��
							if (s.length() <= 80)	//s.length()�����ڰ�ʮֱ�ӽ���ע���β�л���
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
								if (!s.empty())	//str.length()�ĳ��Ȳ�������β��'\n'������С�ڰ�ʮֱ�ӽ���ע���β�л���
								{
									A a = { s, 1 };
									li->push_back(a);
								}
							}
						}
					}
					else
					{	//��Ϊ��һ���Ѿ���ɾ��������Ҫ�ٲ��ң�ֻ�ǰ�s����li��
						if (s.length() <= 80)	//s.length()�����ڰ�ʮֱ�ӽ���ע���β�л���
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
							if (!s.empty())	//str.length()�ĳ��Ȳ�������β��'\n'������С�ڰ�ʮֱ�ӽ���ע���β�л���
							{
								A a = { s, 1 };
								li->push_back(a);
							}
						}
					}
					m += lines;	//��������������굽�˼���
					lines = 0;
					j = 0;
					s = "";
					temp = -1;
					offset[0] = -1;
				}
			}
		}
		else
		{	//ɾ��ȫ���ҵ����ַ���
			for (int lit = 0; lit < n; lit++)	//���li��
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
					if (s.length() <= 80)	//s.length()�����ڰ�ʮֱ�ӽ���ע���β�л���
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
						if (!s.empty())	//str.length()�ĳ��Ȳ�������β��'\n'������С�ڰ�ʮֱ�ӽ���ע���β�л���
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
		cout << "���ַ���������" << endl;
	li->back().newLine = 2;
}

int myString::search(list<A> li)
{
	string s;	//��ʱ����
	string s1;	//Ҫ�ҵ��ַ���
	list<A> xlist = li;
	int n = xlist.size();	//nΪ������Ԫ������
	int i, j = 0, temp = -1, offset[80];	//offset[]�б���һ���п��ܷ��ֵ�Ŀ��ƫ����
	int lines = 0;	//����������
	int	k = 0;	//��ʶ��ƪ����Ŀ�괮
	int k1 = 0;	//��ʶ��������Ŀ�괮
	int m = 0;
	cout << "���������ҵ��ַ�����";
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
			if (s.find(s1) != string::npos)	//�ڸö����ҵ���Ŀ�괮
			{
				k = 1;
				k1 = 1;
			}
			else
			{	//�ڸö���û�ҵ�Ŀ�괮
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
					cout << "��" << offset[a] / 80 + 1 + m<< "��\t";
					cout << "��" << offset[a] % 80 + 1 << "���ַ���ʼ" << endl;
				}
				
			}
			m += lines;	//��������������굽�˼���
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
	cout << "��������������ļ�����";
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
	string s;	//��ʱ����
	string s1;	//Ҫ�ҵ��ַ���
	string sp;	//�����滻���ַ���
	list<A> xlist = *li;
	int n = xlist.size();	//nΪ������Ԫ������
	int i, j = 0, temp = -1, offset[80];	//offset[]�б���һ���п��ܷ��ֵ�Ŀ��ƫ����
	int lines = 0;	//����������
	int	k = 0;	//��ʶ��ƪ����Ŀ�괮
	int k1 = 0;	//��ʶ��������Ŀ�괮
	int m = 0;
	cout << "�������뱻�滻�������ַ�����";
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
			if (s.find(s1) != string::npos)	//�ڸö����ҵ���Ŀ�괮
			{
				k = 1;
				k1 = 1;
			}
			else
			{	//�ڸö���û�ҵ�Ŀ�괮
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
					cout << "��" << offset[a] / 80 + 1 + m << "��\t";
					cout << "��" << offset[a] % 80 + 1 << "���ַ���ʼ" << endl;
				}

			}
			m += lines;	//��������������굽�˼���
			lines = 0;
			j = 0;
			s = "";
			temp = -1;
			offset[0] = -1;
		}
	}
	if (k == 1)	//�ҵ���Ŀ�괮������������ɾ������
	{
		cout << "�������������滻���ַ�����";
		getline(cin, sp);
		int oneOrAll = 0;	//�б�ɾ����һ���ַ�������ȫ���ҵ����ַ���(����1��0)
		while (1)
		{
			cout << "�滻��һ���ַ�������ȫ���ҵ����ַ���(����1��0): ";
			cin >> oneOrAll;
			if (oneOrAll == 1 || oneOrAll == 0)
				break;
		}
		list<A> ylist = *li;
		m = 0;
		if (oneOrAll == 1)	//�滻��һ���ַ���
		{
			int eraseOrNot = 0;	//Ϊ1��ʱ���ʾɾ���˵�һ���ַ���
			for (i = 0; i < n; i++)	//��ʼÿ�еı���
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

						if (s.find(s1) != string::npos)	//�ڸö����ҵ���Ŀ�괮
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
								for (int lit = 0; lit < n; lit++)	//���li��
								{
									li->pop_back();
								}
								if (s.length() <= 80)	//s.length()�����ڰ�ʮֱ�ӽ���ע���β�л���
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
									if (!s.empty())	//str.length()�ĳ��Ȳ�������β��'\n'������С�ڰ�ʮֱ�ӽ���ע���β�л���
									{
										A a = { s, 1 };
										li->push_back(a);
									}
								}
								eraseOrNot = 1;
							}
						}
						else
						{	//��Ϊ�ö���û��Ŀ�괩������ֱ�Ӱ�s����li��
							if (s.length() <= 80)	//s.length()�����ڰ�ʮֱ�ӽ���ע���β�л���
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
								if (!s.empty())	//str.length()�ĳ��Ȳ�������β��'\n'������С�ڰ�ʮֱ�ӽ���ע���β�л���
								{
									A a = { s, 1 };
									li->push_back(a);
								}
							}
						}
					}
					else
					{	//��Ϊ��һ���Ѿ���ɾ��������Ҫ�ٲ��ң�ֻ�ǰ�s����li��
						if (s.length() <= 80)	//s.length()�����ڰ�ʮֱ�ӽ���ע���β�л���
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
							if (!s.empty())	//str.length()�ĳ��Ȳ�������β��'\n'������С�ڰ�ʮֱ�ӽ���ע���β�л���
							{
								A a = { s, 1 };
								li->push_back(a);
							}
						}
					}
					m += lines;	//��������������굽�˼���
					lines = 0;
					j = 0;
					s = "";
					temp = -1;
					offset[0] = -1;
				}
			}
		}
		else
		{	//�滻ȫ���ҵ����ַ���
			for (int lit = 0; lit < n; lit++)	//���li��
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
					if (s.length() <= 80)	//s.length()�����ڰ�ʮֱ�ӽ���ע���β�л���
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
						if (!s.empty())	//str.length()�ĳ��Ȳ�������β��'\n'������С�ڰ�ʮֱ�ӽ���ע���β�л���
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
		cout << "���ַ���������" << endl;
	li->back().newLine = 2;
}
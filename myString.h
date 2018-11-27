#ifndef MYSTRING_H
#define MYSTRING_H

#include <string>
#include <list>

using namespace std;

struct A
{
	string str;
	int newLine = 0;	//newLineΪ1��ʾ�⴮ĩβ�л��У�2��ʾ����β��
};

class myString
{
public:
	myString();	//���캯��
	list<A> openFile(string);	//���ļ�������һ����ʱlist��li
	void show(list<A>);	//����Ļ����ʾ��ʱ�������е�����
	int insert(list<A>*);	//���룬����ֵΪ0�����ʧ�ܣ�1�ɹ�
	void del(list<A>*);
	int search(list<A>);
	void save(const string, list<A>);	//����
	void saveAs(list<A>);
	void replace(list<A>*);
protected:
	list<A> li;
};
#endif 
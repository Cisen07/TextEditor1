#ifndef MYSTRING_H
#define MYSTRING_H

#include <string>
#include <list>

using namespace std;

struct A
{
	string str;
	int newLine = 0;	//newLine为1表示这串末尾有换行，2表示到结尾了
};

class myString
{
public:
	myString();	//构造函数
	list<A> openFile(string);	//打开文件，返回一个临时list即li
	void show(list<A>);	//在屏幕上显示临时的链表中的内容
	int insert(list<A>*);	//插入，返回值为0则插入失败，1成功
	void del(list<A>*);
	int search(list<A>);
	void save(const string, list<A>);	//保存
	void saveAs(list<A>);
	void replace(list<A>*);
protected:
	list<A> li;
};
#endif 
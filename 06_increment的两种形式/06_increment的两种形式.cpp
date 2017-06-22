// 06_increment的两种形式.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;



class Widget {

public:
	Widget& operator++(); //++前缀
	const Widget operator++(int); //后缀,参数多一个int,但是没有意义，只是为了区分
	Widget& operator+=(int);
private:
	int m_int;

};

int main()
{

	system("pause");
	return 0;
}

Widget & Widget::operator++()
{
	*this += 1;
	return *this;
}

const Widget Widget::operator++(int)
{
	Widget old = *this; //旧的值先备份
	++(*this); //然后加
	return old; //返回旧的值，产生了临时对象，所以尽量少用后缀形式
}

Widget & Widget::operator+=(int i)
{
	m_int += i;
}

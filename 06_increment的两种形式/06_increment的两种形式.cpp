// 06_increment��������ʽ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;



class Widget {

public:
	Widget& operator++(); //++ǰ׺
	const Widget operator++(int); //��׺,������һ��int,����û�����壬ֻ��Ϊ������
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
	Widget old = *this; //�ɵ�ֵ�ȱ���
	++(*this); //Ȼ���
	return old; //���ؾɵ�ֵ����������ʱ�������Ծ������ú�׺��ʽ
}

Widget & Widget::operator+=(int i)
{
	m_int += i;
}

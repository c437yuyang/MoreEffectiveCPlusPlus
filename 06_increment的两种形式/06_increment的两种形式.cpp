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

Widget & Widget::operator+=(int i) //��ʵ��operator+=
{
	m_int += i;
}

Widget & Widget::operator++() //��ʵ��ǰ�ð汾
{
	*this += 1;
	return *this;
}

const Widget Widget::operator++(int)//�ٸ���ǰ�ð汾ʵ�ֺ��ð汾
{
	Widget old = *this; //�ɵ�ֵ�ȱ���
	++(*this); //Ȼ���(����ǰ�ð汾)
	return old; //���ؾɵ�ֵ����������ʱ�������Ծ������ú�׺��ʽ
}



int main()
{

	system("pause");
	return 0;
}



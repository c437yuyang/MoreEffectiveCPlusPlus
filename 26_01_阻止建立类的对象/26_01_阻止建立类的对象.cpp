// 26_01_��ֹ������Ķ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;


class Widget {

private:
	Widget() {};
	Widget(const Widget& rhs) {};
};


class SpecialWidget :public Widget {

};


class Widget1 {

private:
	~Widget1();
};


int main()
{
	//SpecialWidget sw;

	//Widget1 w; //���������������ܷ��ʣ���˲���ջ�Ϲ�������
	Widget1 *pw = new Widget1; //�����ڶ��ϴ���
	system("pause");
	return 0;
}


// 20_����ֵ�����ʱ������Ż�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;


class Widget
{

public:
	Widget(int i) :m(i) { cout << "����" << endl; };
	~Widget() { cout << "����" << endl; }
	int m;
	Widget(const Widget& other) { cout << "copy ctor" << endl; }
};

Widget WidgetAdd(Widget &w)
{
	w.m += 1;

	//����һ�ι����һ������(�����ʱ�����)��Ȼ��ͻ��Ǳ߻����copy ctor
	Widget d(w.m);
	return d;

	//return Widget(w.m);//ʹ��ctor argument ֻ���ù��죬��������ֱ�Ӵ��ݸ��ͻ��Ǳߣ��ͻ��Ǳ�������ȷʵʡ����һ��copy ctor��һ��dtor
}

int main()
{
	{
		Widget w1(1);
		//w1.m = 1;
		Widget w2 = WidgetAdd(w1); 
	}



	return 0;
}


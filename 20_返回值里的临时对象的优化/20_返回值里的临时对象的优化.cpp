// 20_����ֵ�����ʱ������Ż�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;


class Widget {

public:Widget(int i):m(i) { cout << "����" << endl; };
	   ~Widget() { cout << "����" << endl; }
	   int m;
};

Widget WidgetAdd(Widget &w) {
	w.m += 1;

	//����һ�ι����һ������
	//Widget d(w.m);
	//return d;

	return Widget(w.m);//ֻ���ù��죬����������
}

int main()
{
	Widget w1(1);
	//w1.m = 1;
	Widget w2 = WidgetAdd(w1);


	
    return 0;
}


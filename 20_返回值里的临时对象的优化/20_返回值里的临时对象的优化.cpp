// 20_返回值里的临时对象的优化.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;


class Widget
{

public:
	Widget(int i) :m(i) { cout << "构造" << endl; };
	~Widget() { cout << "析沟" << endl; }
	int m;
	Widget(const Widget& other) { cout << "copy ctor" << endl; }
};

Widget WidgetAdd(Widget &w)
{
	w.m += 1;

	//会有一次构造和一次析构(这个临时对象的)，然后客户那边会调用copy ctor
	Widget d(w.m);
	return d;

	//return Widget(w.m);//使用ctor argument 只调用构造，这个对象会直接传递给客户那边，客户那边析构，确实省掉了一次copy ctor和一次dtor
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


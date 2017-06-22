// 20_返回值里的临时对象的优化.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;


class Widget {

public:Widget(int i):m(i) { cout << "构造" << endl; };
	   ~Widget() { cout << "析沟" << endl; }
	   int m;
};

Widget WidgetAdd(Widget &w) {
	w.m += 1;

	//会有一次构造和一次析构
	//Widget d(w.m);
	//return d;

	return Widget(w.m);//只调用构造，不调用析构
}

int main()
{
	Widget w1(1);
	//w1.m = 1;
	Widget w2 = WidgetAdd(w1);


	
    return 0;
}


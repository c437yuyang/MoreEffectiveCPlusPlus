// 04_默认构造函数.cpp : 定义控制台应用程序的入口点。
//



#include "stdafx.h"
#include <iostream>
using namespace std;

class Widget {

public:
	Widget(int );

};

int main()
{
	//Widget w = new Widget();

	Widget w[10] = new Widget[10](10);

	system("pause");
    return 0;
}

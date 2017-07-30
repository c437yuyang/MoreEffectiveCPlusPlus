// 26_01_阻止建立类的对象.cpp : 定义控制台应用程序的入口点。
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

	//Widget1 w; //报错，析构函数不能访问，因此不能栈上构建对象
	Widget1 *pw = new Widget1; //可以在堆上创建
	system("pause");
	return 0;
}


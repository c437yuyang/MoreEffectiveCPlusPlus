// 27_01_限制只能在堆上创建对象.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
class Widget
{
public:
	Widget() {}
	void destroy()const { delete this; }

private:
	~Widget();
};

//另一种做法是把构造函数private，然后提供一个public工厂函数，来控制产生对象的方式，但是这样的话如果有多个构造函数需要全部private,而析构函数只有一个,更方便
//

int main()
{
	//Widget w; //报错，无法析构

	Widget *w1 = new Widget;
	w1->destroy(); //这样来调用delete来调用析构函数

	system("pause");
    return 0;
}


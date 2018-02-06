// 28_01_SmartPtr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SmartPtr.h"
#include <iostream>

class Widget
{
public:
	void printiinfo() { std::cout << "Widget::printInfo" << std::endl; }
};

int main()
{
	{
		SmartPtr<Widget> sp_w(new Widget);
		SmartPtr<Widget> sp_w1(sp_w);
		SmartPtr<Widget> sp_w2;
		sp_w2 = sp_w1;
	}

    return 0;
}


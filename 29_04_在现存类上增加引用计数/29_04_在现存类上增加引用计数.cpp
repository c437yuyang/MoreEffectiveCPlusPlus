// 29_04_在现存类上增加引用计数.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "RCWidget.h"

int main()
{
	{
		RCWidget w1(10);
		RCWidget w2(w1);
		std::cout << w2.size() << std::endl;
		w2.do_something();
		std::cout << w2.size() << std::endl;
		RCWidget w3(1);
		w3 = w2;
	}
    return 0;
}


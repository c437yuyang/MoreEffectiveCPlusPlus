// 29_04_���ִ������������ü���.cpp : �������̨Ӧ�ó������ڵ㡣
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


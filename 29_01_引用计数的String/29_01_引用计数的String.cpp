// 29_01_引用计数的String.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "String.h"

int main()
{
	//版本1的问题:
	{
		//如果这样使用:
		String s1 = "Hello";
		char *p = &s1[1]; //拿到指针
		String s2 = s1; //现在s2不知道p拥有了可以修改s1的指针
		*p = 'c';
	}

    return 0;
}


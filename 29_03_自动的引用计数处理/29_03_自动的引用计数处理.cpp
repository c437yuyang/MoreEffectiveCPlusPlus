// 29_03_自动的引用计数处理.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "String.h"

int main()
{
	{
		String s1 = "123";
		String s2 = s1;
		String s3;
		s3 = s1;

		char *p = &s3[0];

		String s4 = s3;
	}


	
    return 0;
}


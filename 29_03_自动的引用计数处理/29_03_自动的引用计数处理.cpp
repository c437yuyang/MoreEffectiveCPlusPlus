// 29_03_�Զ������ü�������.cpp : �������̨Ӧ�ó������ڵ㡣
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


// 29_01_���ü�����String.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "String.h"

int main()
{
	//�汾1������:
	{
		//�������ʹ��:
		String s1 = "Hello";
		char *p = &s1[1]; //�õ�ָ��
		String s2 = s1; //����s2��֪��pӵ���˿����޸�s1��ָ��
		*p = 'c';
	}

    return 0;
}


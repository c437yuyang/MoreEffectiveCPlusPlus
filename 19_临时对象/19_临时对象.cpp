// 19_��ʱ����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{

	size_t countChar(const string & str, char ch);
	countChar("aa",'a'); //���ڳ������ã��Ὠ����ʱ����(��ʽ����ת��)����str����ʼ����ʱ����
	void uppercasify(string &str);

	char subBookPlug[] = "aaa";
	
	//uppercasify(subBookPlug); //�����ǳ������ã����Ὠ����ʱ����
	//��Ϊ�����������ʱ����Ļ����޸ĵ�Ҳ����ʱ�����ֵ��û�ã�����ֱ�Ӿͽ�ֹ�������˱�����
	uppercasify(string("aaa")); //ֱ�Ӵ����󲻻���Ӱ�죬ֻ�����ڿ��ܷ�����ʽ����ת����ʱ��

    return 0;

}


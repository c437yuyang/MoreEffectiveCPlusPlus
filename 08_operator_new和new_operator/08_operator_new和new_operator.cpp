// 08_operator_new��new_operator.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;


class Widget {

	void * operator new(size_t size);

};

int main()
{
	void *rawMemory = operator new(sizeof(string));
	system("pause");
	return 0;
}

void * Widget::operator new(size_t size)
{
	return ;
}

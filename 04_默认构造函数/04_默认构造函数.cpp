// 04_Ĭ�Ϲ��캯��.cpp : �������̨Ӧ�ó������ڵ㡣
//



#include "stdafx.h"
#include <iostream>
using namespace std;

class Widget {

public:
	Widget(int );

};

int main()
{
	//Widget w = new Widget();

	Widget w[10] = new Widget[10](10);

	system("pause");
    return 0;
}

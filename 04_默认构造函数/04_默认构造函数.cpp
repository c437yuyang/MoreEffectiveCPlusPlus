// 04_Ĭ�Ϲ��캯��.cpp : �������̨Ӧ�ó������ڵ㡣
//



#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

class Widget {

public:
	Widget(int i):id(i) {};
	int id;
};

int main()
{
	//Widget w = new Widget();

	//Widget w[10] = new Widget[10](); //����
	//Widget w[10] = new Widget[10](10); //����,new�����ǲ��ܵ����в����Ĺ��캯����

	//�Ƕ��������ֱ��ͨ��initializer list���
	Widget warr[3] = { Widget(1),Widget(2),Widget(3) };

	//�����������ָ�����������
	typedef Widget* PW;
	PW arr[3];
	PW *pw = new PW[3];
	//��ȥѭ����ֵ


	//����placement new �����

	void *rawMem = operator new[](10 * sizeof(Widget));
	Widget* pws = static_cast<Widget*>(rawMem);
	for (int i=0;i!=10;++i)
	{
		new(&pws[i])Widget(i);
	}

	//�����ֶ�����
	for (int i=9;i>=0;--i)
	{
		pws[i].~Widget();
	}
	operator delete[](rawMem);


	//vector ��������Ĭ�Ϲ��캯��,���ʵ�ʲ��Է��ֻ��Ǳ�����Ĭ�Ϲ��캯�����е�
	vector<Widget> vW(3,10); //��Ȼ�ͱ����������ã��ṩԪ�س�ʼֵ
	int i = vW[0].id;

	system("pause");
	return 0;
}

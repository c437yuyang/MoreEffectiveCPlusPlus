// 04_默认构造函数.cpp : 定义控制台应用程序的入口点。
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

	//Widget w[10] = new Widget[10](); //报错
	//Widget w[10] = new Widget[10](10); //报错,new里面是不能调用有参数的构造函数的

	//非堆数组可以直接通过initializer list解决
	Widget warr[3] = { Widget(1),Widget(2),Widget(3) };

	//堆数组可以用指针数组来解决
	typedef Widget* PW;
	PW arr[3];
	PW *pw = new PW[3];
	//再去循环赋值


	//或者placement new 来解决

	void *rawMem = operator new[](10 * sizeof(Widget));
	Widget* pws = static_cast<Widget*>(rawMem);
	for (int i=0;i!=10;++i)
	{
		new(&pws[i])Widget(i);
	}

	//必须手动析构
	for (int i=9;i>=0;--i)
	{
		pws[i].~Widget();
	}
	operator delete[](rawMem);


	//vector 不依赖于默认构造函数,结果实际测试发现还是必须有默认构造函数才行的
	vector<Widget> vW(3,10); //不然就必须这样调用，提供元素初始值
	int i = vW[0].id;

	system("pause");
	return 0;
}

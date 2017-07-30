// 27_01_判断对象在堆上.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "HeepTrack.h"
#include <iostream>
using namespace std;

class Widget :public HeapTrack {};

int main()
{
	Widget w1;
	Widget *pW = new Widget();
	Widget *pW1 = new Widget[10];

	cout << w1.isOnHeap() << endl;//0

	cout << pW->isOnHeap() << endl;//1

	cout << pW1[0].isOnHeap() << endl; //0,还是不能用于operator[]的

	return 0;
}


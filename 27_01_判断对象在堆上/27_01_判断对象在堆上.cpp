// 27_01_�ж϶����ڶ���.cpp : �������̨Ӧ�ó������ڵ㡣
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

	cout << pW1[0].isOnHeap() << endl; //0,���ǲ�������operator[]��

	return 0;
}


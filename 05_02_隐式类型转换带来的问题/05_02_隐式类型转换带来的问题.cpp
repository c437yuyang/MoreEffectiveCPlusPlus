// 05_02_��ʽ����ת������������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

//��������˵��operator << ���ܻ�������벻������ʽ����ת��֮�⣬���ﻹ������:

template<class T>
class Array
{
public:
	Array(int lowBound, highBound) {}; //���ﶼ��дʵ���ˣ�ֻ����ʾ
	Array(int size) {};
	T &operator[](int index) {};
};

bool operator==(const Array<int>&lhs, const Array<int>&rhs)
{

}

int main()
{
	Array<int> a(10);
	Array<int> b(10);

	for (int i = 0; i < 10; ++i) //����Ƚ�ÿ��Ԫ���Ƿ����
	{
		if (a == b[i]) //�����������±���������a��b[i]���Ƚϣ����Ǳ��������������!,��Ϊb[i]ÿ�ζ���ת����һ����СΪb[i]��Array<int>����
		{
		}
		//�൱��
		if (a == static_cast<Array<int>>(b[i])) //Ϊ�˱��⣬�����ڵ��������캯������explicit�ؼ��ֻ���ʹ��Proxy class
		{

		}
	}

	return 0;
}

template<class T>
class Widget
{
public:
	class ArraySize
	{
	public:
		ArraySize(int num) :size_(num) {}
		int size()const { return size_; }
	private:
		int size_;
	};

	Widget(int lowBound, highBound) {}; //���ﶼ��дʵ���ˣ�ֻ����ʾ
	Widget(ArraySize size) {}; //���ڶ������ͨ������ArraySize��ʵ�֣��ͱ������Ǹ�����(��ΪC++��������������ʽת��)
	T &operator[](int index) {};
};
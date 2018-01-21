// 03_01_对数组使用多态.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>


class A
{
public:
	long a;
};
class B : public A
{
public:
	long b;
};
void seta(A* data, int idx) //这里传入A类型的参数，因此把这些对象都当成是A的大小，所以后面赋值会赋值到data[].b的成员上去
{
	data[idx].a = 2;
}
int main(int argc, char *argv[])
{
	B data[4];
	for (int i = 0; i < 4; ++i)
	{
		data[i].a = 1;
		data[i].b = 1;
		seta(data, i); 
	}
	for (int i = 0; i < 4; ++i)
	{
		std::cout << data[i].a << data[i].b;
	}
	//22221111
	system("pause");
	return 0;
}


//这道题应该注意 指针类型加减 时步长的问题。
//A 大小为 4
//B 大小为 8
//那么：
//void seta(A* data, int idx) {
//    data[idx].a = 2;
//}
//由于传入的实参为B类型，大小为8，而形参为A类型，大小为4
//data[idx] 取 data + idx 处的元素，这时指针 data加1 的长度不是一个B长度，而是一个A长度，或者说是1/2个B长度。这时该函数中 data[0~3] 指向的是原 data[0].a,data[0].b,data[1].a,data[1].b, 
//由于隐式类型转换的缘故，data[0].a, data[0].b,data[1].a,data[1].b 处的值全部由于 data[idx].a = 2; 操作变为 2。
//这道题如果改为void seta(B* data, int idx)，那么形参中data指针加1步长为8，结果就是21212121。但是由于步长为4，所以结果就是 22221111。


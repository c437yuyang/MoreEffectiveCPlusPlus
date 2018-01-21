// 05_02_隐式类型转换带来的问题.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

//除了上面说的operator << 可能会调用意想不到的隐式类型转换之外，这里还有例子:

template<class T>
class Array
{
public:
	Array(int lowBound, highBound) {}; //这里都不写实现了，只是演示
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

	for (int i = 0; i < 10; ++i) //本想比较每个元素是否相等
	{
		if (a == b[i]) //这里忘记了下标结果，成了a和b[i]作比较，但是编译器不会给警告!,因为b[i]每次都被转换成一个大小为b[i]的Array<int>对象。
		{
		}
		//相当于
		if (a == static_cast<Array<int>>(b[i])) //为了避免，就是在单参数构造函数加上explicit关键字或者使用Proxy class
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

	Widget(int lowBound, highBound) {}; //这里都不写实现了，只是演示
	Widget(ArraySize size) {}; //现在定义必须通过传入ArraySize来实现，就避免了那个问题(因为C++不允许两步的隐式转换)
	T &operator[](int index) {};
};
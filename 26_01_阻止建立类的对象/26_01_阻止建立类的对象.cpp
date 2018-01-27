// 26_01_阻止建立类的对象.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#pragma region 版本1
//第一种方法最简单，构造函数private,用一个友元函数创建一个static对象，每次返回这个对象即可。
//class PrintJob;
//class Printer
//{
//public:
//	void submitJob(const PrintJob& job) {};
//	void reset() {};
//	void performSelfTest() {};
//	friend Printer& thePrinter();
//private:
//	Printer(); //private构造函数
//	Printer(const Printer&rhs);
//};
//
//Printer & thePrinter()
//{
//	static Printer p;
//	return p;
//}
#pragma endregion


#pragma region 其实不需要使用全局命名空间的友元函数,换成类内的静态函数即可
//class PrintJob;
//class Printer
//{
//public:
//	void submitJob(const PrintJob& job) {};friend
//	void reset() {};
//	void performSelfTest() {};
//	static Printer& thePrinter()
//	{
//		static Printer p;
//		return p;
//	}
//private:
//	Printer(); //private构造函数
//	Printer(const Printer&rhs);
//};
#pragma endregion

#pragma region 第三种方法，还是使用友元，只是不用全局命名空间
//这样的好处是，相较于类内的静态成员(始终会生成)，只有用到时候才会生成对象
namespace PrintingStuff
{
	class PrintJob;
	class Printer
	{
	public:
		void submitJob(const PrintJob& job) {};
		void reset() {};
		void performSelfTest() {};
		friend Printer& thePrinter();
	private:
		Printer(); //private构造函数
		Printer(const Printer&rhs);
	};

	Printer& thePrinter()
	{
		static Printer p;
		return p;
	}
}


#pragma endregion


#pragma region 对象引用计数的实现,版本1，最简单的做法
class Printer
{
public:
	class TooManyObjects {};
	Printer();
	~Printer();
private:
	static size_t numObjects;

	Printer(const Printer&rhs); //简单起见，不让拷贝

};

size_t Printer::numObjects = 0;

Printer::Printer()
{
	if (numObjects >= 1)
	{
		throw TooManyObjects();

	}
	++numObjects;
}

Printer::~Printer()
{
	--numObjects;
}


#pragma endregion



int main()
{
	//版本3使用:
	PrintingStuff::thePrinter().reset();

	system("pause");
	return 0;
}


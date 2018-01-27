// 26_01_��ֹ������Ķ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#pragma region �汾1
//��һ�ַ�����򵥣����캯��private,��һ����Ԫ��������һ��static����ÿ�η���������󼴿ɡ�
//class PrintJob;
//class Printer
//{
//public:
//	void submitJob(const PrintJob& job) {};
//	void reset() {};
//	void performSelfTest() {};
//	friend Printer& thePrinter();
//private:
//	Printer(); //private���캯��
//	Printer(const Printer&rhs);
//};
//
//Printer & thePrinter()
//{
//	static Printer p;
//	return p;
//}
#pragma endregion


#pragma region ��ʵ����Ҫʹ��ȫ�������ռ����Ԫ����,�������ڵľ�̬��������
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
//	Printer(); //private���캯��
//	Printer(const Printer&rhs);
//};
#pragma endregion

#pragma region �����ַ���������ʹ����Ԫ��ֻ�ǲ���ȫ�������ռ�
//�����ĺô��ǣ���������ڵľ�̬��Ա(ʼ�ջ�����)��ֻ���õ�ʱ��Ż����ɶ���
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
		Printer(); //private���캯��
		Printer(const Printer&rhs);
	};

	Printer& thePrinter()
	{
		static Printer p;
		return p;
	}
}


#pragma endregion


#pragma region �������ü�����ʵ��,�汾1����򵥵�����
class Printer
{
public:
	class TooManyObjects {};
	Printer();
	~Printer();
private:
	static size_t numObjects;

	Printer(const Printer&rhs); //����������ÿ���

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
	//�汾3ʹ��:
	PrintingStuff::thePrinter().reset();

	system("pause");
	return 0;
}


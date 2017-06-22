// 05_01_类型转换函数.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
using namespace std;


class Rational {
public:
	Rational(int numerator = 0, int denominator = 1);
	operator double() const; //定义一个隐式转换到double类的成员函数
	//解决隐式转换:声明一个这种函数，但是用着不方便，以及把单成员的构造函数声明为explicit
	double asDouble() const;
private:
	int m_numerator;
	int m_denominator;
};



int main()
{


	Rational r(1, 2);

	cout << r * 2 << endl; //使用隐式类型转换函数

	cout << r << endl; //因为没有定义<<,所以寻找到了隐式转换成double的方法，打印成了一个浮点数，而不是真实的有理数
	system("pause");
	return 0;
}

Rational::Rational(int numerator, int denominator)
{
	m_numerator = numerator;
	m_denominator = denominator;

}

Rational::operator double() const
{
	return m_numerator*1.0 / m_denominator;
}

double Rational::asDouble() const
{

	return m_numerator*1.0 / m_denominator;
}

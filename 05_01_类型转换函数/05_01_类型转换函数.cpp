// 05_01_����ת������.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <iostream>
using namespace std;


class Rational {
public:
	Rational(int numerator = 0, int denominator = 1);
	operator double() const; //����һ����ʽת����double��ĳ�Ա����
	//�����ʽת��:����һ�����ֺ������������Ų����㣬�Լ��ѵ���Ա�Ĺ��캯������Ϊexplicit
	double asDouble() const;
private:
	int m_numerator;
	int m_denominator;
};



int main()
{


	Rational r(1, 2);

	cout << r * 2 << endl; //ʹ����ʽ����ת������

	cout << r << endl; //��Ϊû�ж���<<,����Ѱ�ҵ�����ʽת����double�ķ�������ӡ����һ������������������ʵ��������
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

// 03_01_������ʹ�ö�̬.cpp : �������̨Ӧ�ó������ڵ㡣
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
void seta(A* data, int idx) //���ﴫ��A���͵Ĳ�������˰���Щ���󶼵�����A�Ĵ�С�����Ժ��渳ֵ�ḳֵ��data[].b�ĳ�Ա��ȥ
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


//�����Ӧ��ע�� ָ�����ͼӼ� ʱ���������⡣
//A ��СΪ 4
//B ��СΪ 8
//��ô��
//void seta(A* data, int idx) {
//    data[idx].a = 2;
//}
//���ڴ����ʵ��ΪB���ͣ���СΪ8�����β�ΪA���ͣ���СΪ4
//data[idx] ȡ data + idx ����Ԫ�أ���ʱָ�� data��1 �ĳ��Ȳ���һ��B���ȣ�����һ��A���ȣ�����˵��1/2��B���ȡ���ʱ�ú����� data[0~3] ָ�����ԭ data[0].a,data[0].b,data[1].a,data[1].b, 
//������ʽ����ת����Ե�ʣ�data[0].a, data[0].b,data[1].a,data[1].b ����ֵȫ������ data[idx].a = 2; ������Ϊ 2��
//����������Ϊvoid seta(B* data, int idx)����ô�β���dataָ���1����Ϊ8���������21212121���������ڲ���Ϊ4�����Խ������ 22221111��


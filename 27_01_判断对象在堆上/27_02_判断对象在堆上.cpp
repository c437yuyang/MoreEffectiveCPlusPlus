// 27_01_�ж϶����ڶ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "HeepTrack.h"
#include <iostream>
using namespace std;

#pragma region ��һ�ְ취����operator new ���ֽ�
class UPNumber
{
public:
	class HeapConstraintVoilation {};
	static void *operator new(size_t size);
	UPNumber();
private:
	static bool onTheHeap;
};

bool UPNumber::onTheHeap = false;

void *UPNumber::operator new(size_t size)
{
	onTheHeap = true;
	return ::operator new(size);
}

UPNumber::UPNumber()
{
	if (!onTheHeap)
		throw HeapConstraintVoilation();
	onTheHeap = false;
}
//����취���������ڣ��������UPNumber *arr=  new UPNumber[100];
//��ʱ���õ���operator new [],��ȻҲ������д��������ǻ����100�ι��캯������ֻ�����һ��operator new����[]
//���ֻ�е�һ�����캯�����⵽onTheHeap = true; ����99�����ᱨ�쳣��
//�����������:
//UPNumber* p = new UPNumber(*new UPNumber);
//�ڴ�������˳����:
//(1)operator new(2)����(3)operator new(4)����
// ����C++����֤˳�����Ի�����
#pragma endregion

#pragma region �ڶ��ַ���������ջ�ռ��ǴӴ�С���ѿռ��Ǵ�С����
bool onHeap(const void *addr)
{
	char onTheStack;
	return addr < &onTheStack; //��Ϊonthestack����������ģ�����κ�ջ�ϵı����ĵ�ַ��������������������С���Ƕ�����
}
//�����������ڣ�������Ա������������ط������˶Ѻ�ջ�����о�̬���󣬼Ȳ���ջ��Ҳ���ڶ��ϡ�
//��̬�����λ�������ھ����ʵ�֣��������λ�ڶѵĵͶˡ�
//������������ܱ��Ѷ���;�̬���󣬵����������ΪonStack��ʵ���ǶԵ�(onHeap�ʹ��ˣ������Ǿ�̬����)
#pragma endregion


#pragma region �����ַ�������HeapTrack.h

#pragma endregion




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


// 02_01_Cpp���Cast.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class Widget {
	virtual void printInfo() { cout << "Widget!" << endl; };
};
class SpecialWidget :public Widget {
	virtual void printInfo() { cout << "SpecialWidget!" << endl; };
};

void update(SpecialWidget *psw);
void updateViaRef(SpecialWidget &rsw);

int main()
{
	SpecialWidget sw;
	const SpecialWidget & csw = sw;
	//update(&csw); //����
	update(const_cast<SpecialWidget*>(&csw)); //��ȷ��ʹ��const_cast
	update((SpecialWidget*)&csw); //C���Ҳ��������

	Widget *pw = new SpecialWidget;
	//update(pw); //����������
	//update(const_cast<SpecialWidget*>(pw));//����const_castֻ�����ڴ���constness��volatileness

	//dynamic_cast���ڰ�ȫ��������ļ̳й�ϵ���½�������ת�������ѻ����ָ�������ת����ָ������������ֵ����ָ�������
	update(dynamic_cast<SpecialWidget*>(pw));//dynamic_cast�����������Ƿ���ж�̬����(�麯��),���û�лᱨ��
	update((SpecialWidget*)pw); //C��񣬲�����
	update(static_cast<SpecialWidget*>(pw));//ֱ��static_castҲ����

	//updateViaRef(*pw); //����������
	updateViaRef(dynamic_cast<SpecialWidget&>(*pw)); //


	//reinterpret_cast���ں���ָ���ת��
	typedef void(*FuncPtr)();
	FuncPtr funcPtrArray[10];
	int doSomething();
	//funcPtrArray[0] = &doSomething; //�������ʹ���
	funcPtrArray[0] = reinterpret_cast<FuncPtr>(&doSomething);

	funcPtrArray[0] = (void(*)())&doSomething; //C���

	system("pause");
	return 0;
}

// 27_03_��ֹ�����Ѷ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
//�������,ֱ��ʵ��������Ϊ���౻ʵ����������ϵ���������
//��һ�����:

#pragma region ���ֱ��ʵ�����Ľ��
class UPNumber
{
private: //������������private��
	static void *operator new(size_t size);
	static void operator delete(void *ptr);
};

UPNumber n1;
static UPNumber n2;
//UPNumber *p = new UPNumber; //����Ҳ���԰�operator new[]��delete[]��Ϊprivate

#pragma endregion

#pragma region ��Ա��̳е����
//��Ϊoperator new�ᱻ�̳�,�������Ҳ�ǾͲ���ʹ��new�����Ѷ�����
class NoNegtiveUPNumber:public UPNumber
{
};

//NoNegtiveUPNumber *p = new NoNegtiveUPNumber; //����û���Լ�����operator new�Ļ��ͻ�̳и����

#pragma endregion

#pragma region ��Ա���ϵ����
//���������û�õģ���Ϊ���õ����ⲿ���operator new
#pragma endregion



int main()
{
	//
	{

	}

	
    return 0;
}


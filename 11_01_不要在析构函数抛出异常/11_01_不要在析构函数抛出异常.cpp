// 11_01_��Ҫ�����������׳��쳣.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#pragma region ԭʼ�汾
class Session
{
public:
	Session();
	~Session();


private:
	static void logCreation(Session *objAddr);
	static void logDestruction(Session *objAddr);
};

Session::~Session()
{
	logDestruction(this); 
	//���logDestruction�������׳��쳣����Session����������û�б���׽ס����ô�ᱻ���ݵ����������
	//���������������������þ���Դ�������쳣���׳�(������ʲô�����ʱ�������쳣Ȼ��catch�����͹ر�������ӣ�������������ִ��)����ôterminate�����������ã�������ֹ����
}
#pragma endregion

#pragma region �汾2��ʹ��try catch
Session::~Session()
{
	try
	{
		logDestruction(this);
	}
	catch (...)
	{
		std::cerr << "error" << std::endl; //�����ܹ���ֹlogDestruction���쳣�׳����������operator<<�������׳��쳣���쳣�ͻᱻ���ݵ����档����ͨ������try�����񣬵������û���޶ȵĻ��ͻ�����ѭ����
	}
}
#pragma endregion
#pragma region �汾3�����Ե������쳣
Session::~Session()
{
	try
	{
		logDestruction(this);
	}
	catch (...) //ֱ�Ӻ��Ե������쳣���Ͳ�������������Щ�����
	{
		
	}
}
#pragma endregion


//���Ҳ������쳣���ݵ������������滹�еڶ���ԭ������쳣û�����ڲ�������ô���������������ᱻ��ȫִ��,�޷����ϣ����������
Session::Session()
{
	logCreation(this);
	startTransaction(); //����һ������
}

Session::~Session()
{
	logDestruction(this); //��������׳��쳣û�б�������ôendTransaction��û��ִ�С����㽻��λ�ã���ô��һendTrasaction����Ҳ�׳��쳣�Ļ���û�취����ˡ�������ȷ�������ǲ�������쳣��
	endTransaction(); //����
}

int main()
{
    return 0;
}


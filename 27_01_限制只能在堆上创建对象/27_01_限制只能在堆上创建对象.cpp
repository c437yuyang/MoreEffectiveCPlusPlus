// 27_01_����ֻ���ڶ��ϴ�������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
class Widget
{
public:
	Widget() {}
	void destroy()const { delete this; }

private:
	~Widget();
};

//��һ�������ǰѹ��캯��private��Ȼ���ṩһ��public���������������Ʋ�������ķ�ʽ�����������Ļ�����ж�����캯����Ҫȫ��private,����������ֻ��һ��,������
//

int main()
{
	//Widget w; //�����޷�����

	Widget *w1 = new Widget;
	w1->destroy(); //����������delete��������������

	system("pause");
    return 0;
}


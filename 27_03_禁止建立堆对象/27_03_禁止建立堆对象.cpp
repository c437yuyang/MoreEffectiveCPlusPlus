// 27_03_禁止建立堆对象.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//三种情况,直接实例化，作为基类被实例化，被组合到其他类型
//第一种情况:

#pragma region 针对直接实例化的解决
class UPNumber
{
private: //把两个操作符private掉
	static void *operator new(size_t size);
	static void operator delete(void *ptr);
};

UPNumber n1;
static UPNumber n2;
//UPNumber *p = new UPNumber; //报错，也可以把operator new[]和delete[]设为private

#pragma endregion

#pragma region 针对被继承的情况
//因为operator new会被继承,因此子类也是就不能使用new建立堆对象了
class NoNegtiveUPNumber:public UPNumber
{
};

//NoNegtiveUPNumber *p = new NoNegtiveUPNumber; //报错，没有自己声明operator new的话就会继承父类的

#pragma endregion

#pragma region 针对被组合的情况
//这种情况是没用的，因为调用的是外部类的operator new
#pragma endregion



int main()
{
	//
	{

	}

	
    return 0;
}


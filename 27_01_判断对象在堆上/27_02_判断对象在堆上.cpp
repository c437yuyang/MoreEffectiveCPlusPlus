// 27_01_判断对象在堆上.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "HeepTrack.h"
#include <iostream>
using namespace std;

#pragma region 第一种办法，在operator new 做手脚
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
//这个办法的问题在于，如果调用UPNumber *arr=  new UPNumber[100];
//这时调用的是operator new [],虽然也可以重写这个，但是会调用100次构造函数，而只会调用一次operator new或者[]
//因此只有第一个构造函数会检测到onTheHeap = true; 其他99个都会报异常。
//或者这种情况:
//UPNumber* p = new UPNumber(*new UPNumber);
//期待发生的顺序是:
//(1)operator new(2)构造(3)operator new(4)构造
// 但是C++不保证顺序，所以会出会错。
#pragma endregion

#pragma region 第二种方法，利用栈空间是从大到小，堆空间是从小到大
bool onHeap(const void *addr)
{
	char onTheStack;
	return addr < &onTheStack; //因为onthestack是最新申请的，因此任何栈上的变量的地址都必须大于它，如果比它小就是堆上了
}
//但是问题在于，对象可以被分配在三个地方，除了堆和栈，还有静态对象，既不在栈上也不在堆上。
//静态对象的位置依赖于具体的实现，大多数是位于堆的低端。
//所以这个对象不能辨别堆对象和静态对象，但是如果改名为onStack其实就是对的(onHeap就错了，可能是静态对象)
#pragma endregion


#pragma region 第三种方法，见HeapTrack.h

#pragma endregion




class Widget :public HeapTrack {};

int main()
{
	Widget w1;
	Widget *pW = new Widget();
	Widget *pW1 = new Widget[10];

	cout << w1.isOnHeap() << endl;//0

	cout << pW->isOnHeap() << endl;//1

	cout << pW1[0].isOnHeap() << endl; //0,还是不能用于operator[]的

	return 0;
}


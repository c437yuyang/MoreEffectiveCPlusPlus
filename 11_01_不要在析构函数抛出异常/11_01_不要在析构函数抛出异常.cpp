// 11_01_不要在析构函数抛出异常.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#pragma region 原始版本
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
	//如果logDestruction函数内抛出异常但是Session的析构函数没有被捕捉住，那么会被传递到调用者那里。
	//但是如果析构函数本身调用就是源于其他异常的抛出(比如做什么事情的时候抛了异常然后catch到，就关闭这个连接，调用析构函数执行)，那么terminate函数将被调用，彻底终止程序。
}
#pragma endregion

#pragma region 版本2，使用try catch
Session::~Session()
{
	try
	{
		logDestruction(this);
	}
	catch (...)
	{
		std::cerr << "error" << std::endl; //这样能够防止logDestruction的异常抛出，但是如果operator<<里面又抛出异常，异常就会被传递到外面。可以通过再用try来捕获，但是如果没有限度的话就会陷入循环。
	}
}
#pragma endregion
#pragma region 版本3，忽略掉所有异常
Session::~Session()
{
	try
	{
		logDestruction(this);
	}
	catch (...) //直接忽略掉所有异常，就不会出现上面的那些情况。
	{
		
	}
}
#pragma endregion


//并且不允许异常传递到析构函数外面还有第二个原因，如果异常没有在内部捕获，那么析构函数往往不会被完全执行,无法完成希望它做的事
Session::Session()
{
	logCreation(this);
	startTransaction(); //开启一个事务
}

Session::~Session()
{
	logDestruction(this); //如果这里抛出异常没有被捕获，那么endTransaction就没被执行。就算交换位置，那么万一endTrasaction里面也抛出异常的话就没办法解决了。所以正确的做法是捕获忽略异常。
	endTransaction(); //结束
}

int main()
{
    return 0;
}


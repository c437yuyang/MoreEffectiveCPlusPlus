// 05_02_proxyclass.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//如果编译器不支持explicit的话，就可以用到proxyclass来解决
//简单的说就是，把原来单参数里面的参数，换成一个自定义的类型，
//比如对int封装成Arraysize,编译器本身只会允许一次类型转换，不会允许从a->b->c的隐式类型转换，就能避免不必要的类型转换了
template <class T>
class Array 
{
public:
	
};

int main()
{
    return 0;
}

